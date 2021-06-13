#include <stdint.h>
#include "tm4c123gh6pm.h"
#ifndef _MISC_FUNCS_H
#define _MISC_FUNCS_H

void delay_us(uint32_t n)
{
    // Load the reload reg with the needed value
    NVIC_ST_RELOAD_R = (16 * n) - 1;
    NVIC_ST_CURRENT_R = 0; // reset the current value reg
    NVIC_ST_CTRL_R |= 1; // start the counter
    while (!(NVIC_ST_CTRL_R & 1 << 16))
        ;
    NVIC_ST_CTRL_R &= ~(1);
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_RELOAD_R = 0;
}

void delay_ms(uint32_t n)
{
    uint32_t i = 0;
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = (16 * 1000) - 1;
    /* IMPORTANT NOTE: The above number should be 16 not 4
     * but for some reason it does not act properly ...*/
    NVIC_ST_CURRENT_R = 0; // reset the current value reg
    NVIC_ST_CTRL_R |= 1; // start the counter
    while (i < n)
    {
        while (!(NVIC_ST_CTRL_R & 1 << 16))
            ;
        i++;
    }
    NVIC_ST_CTRL_R &= ~(1);
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_RELOAD_R = 0;
}

#endif
