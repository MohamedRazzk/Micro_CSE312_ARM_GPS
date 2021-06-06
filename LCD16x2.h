#include "misc_functions.h"
#include "tm4c123gh6pm.h"
/*
 * RS >> PB4
 * RW >> PB5
 * E >> PB6
 * D4 - D7 >> PB0 - PB3
 */
#define EN 6

void write_cmd_4bit(int cmd)
{
    GPIO_PORTB_DATA_R = ((cmd & 0xF0) >> 4) + ((0b0100) << 4);
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = (cmd & 0x0F) + ((0b0100) << 4);
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(80);
}

void LCD_clear()
{
    write_cmd_4bit(1);
}
void write_char_4bit(char x)
{
    GPIO_PORTB_DATA_R = ((x & 0xF0) >> 4) + ((0b0101) << 4);
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = (x & 0x0F) + ((0b0101) << 4);
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(40);
}

void LCD_init()
{
    delay_ms(50);
    SYSCTL_RCGCGPIO_R |= 1 << 1;
    GPIO_PORTB_DIR_R |= 0xFF;
    GPIO_PORTB_DEN_R |= 0xFF;

    GPIO_PORTB_DATA_R = 0b01000011;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(40);
    GPIO_PORTB_DATA_R = 0b01000010;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = 0b01001000;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(40);
    GPIO_PORTB_DATA_R = 0b01000010;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = 0b01001000;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(40);
    GPIO_PORTB_DATA_R = 0b01000000;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = 0b01001111;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(40);
    GPIO_PORTB_DATA_R = 0b01000000;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    GPIO_PORTB_DATA_R = 0b01000001;
    GPIO_PORTB_DATA_R &= ~(1 << EN);
    delay_us(2000);
}
