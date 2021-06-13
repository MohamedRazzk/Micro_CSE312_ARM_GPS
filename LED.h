#ifndef LED_H_
#define LED_H_

#include "tm4c123gh6pm.h"

void LED_init()
{
    SYSCTL_RCGCGPIO_R |= 1 << 5;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_AFSEL_R &= ~(0x0E);
    GPIO_PORTF_DEN_R |= 0x0E;
}

void turn_on_LED()
{
    GPIO_PORTF_DATA_R |= 0x0E;
}

#endif
