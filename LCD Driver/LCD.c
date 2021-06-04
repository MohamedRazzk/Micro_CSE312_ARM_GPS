#include "LCD.h"

void LCD_init ()
{
	LCD_CTRL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<< E);
	// ***initialize the control & data port/pins (den reg, afsel...etc.) except direction (it will be defined next line)

#if (DATA_BITS == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
#else
	LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */

#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */

#elif (DATA_BITS == 8)		//*****This section should be removed if we decided to work with 4 Bit Mode
	LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand (CURSOR_OFF);			//Cursor off
	LCD_clearScreen();
}

void LCD_sendCommand (uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW);/* write data to LCD so RW=0 */
	_delay_ms(1);/* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if (DATA_BITS == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | (command & 0xF0);
	#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | ((command & 0xF0) >> 4);
	#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT_OUT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0x0F) | ((command & 0x0F) << 4);
	#else
	LCD_DATA_PORT_OUT = (LCD_DATA_PORT_OUT & 0xF0) | (command & 0x0F);
	#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */


#elif (DATA_BITS == 8)		//*****This section should be removed if we decided to work with 4 Bit Mode
	LCD_DATA_PORT_OUT = command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_clearScreen()
{
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RS);
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT_OUT,E);
	_delay_ms(1);
	LCD_DATA_PORT_OUT = CLEAR_COMMAND;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E);
	_delay_ms(1);
}

void LCD_goToRowCol (uint8 row, uint8 col)
{
	uint8 address;
	switch (row)
	{
	case 0: address = col; break;

#if (2 == DISPLAY_LINES || 4 == DISPLAY_LINES)
	case 1: address = 0x40 + col; break;
#elif (4 == DISPLAY_LINES)
	case 2:	address = 0x10 + col; break;
	case 3: address = 0x50 + col; break;
#endif
	}

	LCD_sendCommand (address | SET_CURSOR_LOCATION);
}

void LCD_displayChar (uint8 data)
{
	SET_BIT(LCD_CTRL_PORT_OUT,RS);
	CLEAR_BIT(LCD_CTRL_PORT_OUT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT_OUT,E);
	_delay_ms(1);
	LCD_DATA_PORT_OUT = data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT_OUT,E);
	_delay_ms(1);
}

void LCD_displayString(uint8 *string)		//display string in 1 line only
{
	uint8 i = 0;
	while(string[i] != '\0')
	{
		LCD_displayChar(string[i]);
		i++;
	}
}

void LCD_displayStringRowCol (uint8* string, uint8 row, uint8 col)
{
	LCD_goToRowCol (row, col);
	LCD_displayString(string);
}

void LCD_integerToString (int data)
{
	uint8 buffer [16];
	itoa (data,buffer,10);
	LCD_displayString(buffer);
}
void LCD_floatToString (float data)	//test this function
{
	uint8 buffer [16];
	gcvt (data,6,buffer);
	LCD_displayString(buffer);
}
