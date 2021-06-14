#include<stdint.h>
#include "tm4c123gh6pm.h"

void UART7_init()
{
    SYSCTL_RCGCUART_R |= 1 << 7;
    SYSCTL_RCGCGPIO_R |= 1 << 4;
    GPIO_PORTE_AFSEL_R |= 0b011;
    GPIO_PORTE_DEN_R |= 0b011;
    // GPIO_PORTE_DIR_R |= 1 << 1; // Experimentation
    GPIO_PORTE_PCTL_R |= (0x01 | (0x01 << 4));
    UART7_CTL_R &= ~(1);
    // while (UART7_FR_R & (1 << 3));
    UART7_LCRH_R &= ~(1 << 4);
    UART7_IBRD_R |= 104;
    UART7_FBRD_R |= 11;
    UART7_LCRH_R = 0b01110000;
    UART7_CC_R = 0x05; // Let us look into that
    UART7_CTL_R |= (1 | (0b011 << 8));
}

void UART7_write_char(char x)
{
    while(UART7_FR_R & (1 << 5));
    UART7_DR_R = x;
}

void UART7_write_str(char* str)
{
    int i = 0;
    while(str[i] != '\0')
        {
            UART7_write_char(str[i]);
            i++;
        }
}

char UART7_read()
{
    while((UART7_FR_R & (1 << 4)) != 0);
    return (char)(UART7_DR_R);
}
/*
void UART7_init(void)
{
    SYSCTL_RCGCUART_R |= 0x80;      // activate UART 7
    SYSCTL_RCGCGPIO_R |= 0x00000010;     // activate  port E
    UART7_CTL_R &= ~0x00000001;
    UART7_IBRD_R = 104;             // use 9600
    UART7_FBRD_R = 11;
    UART7_LCRH_R = 0x00000070; // 0111 0000 FIF0 1 DATA LENGTH 11 = 8 bits
    UART7_CC_R = 0;
    UART7_CTL_R |= 0x00000301; // enable uart

    GPIO_PORTE_AFSEL_R |= 0x03; // port E pin 0,1
    GPIO_PORTE_DEN_R |= 0x03;
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFFFFFF00) + 0x00000022;
    GPIO_PORTE_AMSEL_R &= ~0x30;  // disable analog pins
}
uint8_t UART7_read(void)
{
    while ((UART7_FR_R & 0x10) != 0)
        ;
    return ((uint8_t) (UART7_DR_R & 0xFF));
}
void UART7_write(uint8_t data)
{
    while ((UART7_FR_R & 0x20) != 0)
        ;

    UART7_DR_R = data;
}
*/
