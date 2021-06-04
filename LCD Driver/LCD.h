#ifndef LCD_H_
#define LCD_H_

#include "micro_config_arm.h"
#include "common_macros.h"
#include "std_types.h"

#define NO_COL 16
#define DISPLAY_LINES 2
#define DATA_BITS 4

#if (4 == DATA_BITS)
#define UPPER_PORT_PINS
#endif

//Adjustment Needed
#define LCD_CTRL_PORT_DIR ????
#define LCD_CTRL_PORT_OUT ???
#define LCD_CTRL_PORT_IN ???
//add digital enable reg, afsel reg...etc.

#define RS ???
#define RW ???
#define E ???
//choose control pins

#define LCD_DATA_PORT_DIR ???
#define LCD_DATA_PORT_OUT ???
#define LCD_DATA_PORT_IN ???
//add digital enable reg, afsel reg...etc.

//LCD Commands
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

void LCD_init ();
void LCD_sendCommand (uint8 command);
void LCD_clearScreen();
void LCD_goToRowCol (uint8 row, uint8 col);
void LCD_displayChar (uint8 data);
void LCD_displayString (uint8* string);
void LCD_displayStringRowCol (uint8* string, uint8 row, uint8 col);
void LCD_integerToString (int data);
void LCD_floatToString (float data);

#endif
