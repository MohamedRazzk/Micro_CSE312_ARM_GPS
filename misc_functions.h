#include <stdint.h>
#include "tm4c123gh6pm.h"

void delay_us(int n)
{
    NVIC_ST_RELOAD_R = 16 * n; // Load the reload reg with the needed value
    NVIC_ST_CURRENT_R = 0; // reset the current value reg
    NVIC_ST_CTRL_R |= 1; // start the counter
    while (!(NVIC_ST_CTRL_R & 1 << 16));
    NVIC_ST_CTRL_R &= ~(1);
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_RELOAD_R = 0;
}

void delay_ms(int n)
{
    int i;
    n = n/4;
    for(i = 0; i < n; i++)
    {
        delay_us(1000);
    }
}
