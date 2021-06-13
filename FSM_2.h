#ifndef FSM_2_H_
#define FSM_2_H_

#include <stdbool.h>
#include <stdint.h>

#define S_wait_for_init 0
#define S_fill_str_frmt 1
#define S_check_frmt    2
#define S_fill_data     3
#define S_parse         4
#define S_send          5

typedef uint32_t GPS_FSM_t;

void change_state(GPS_FSM_t *state, bool in_sig)
{
        switch (*state) {
    case S_wait_for_init:
        if (in_sig == true)
            *state = S_fill_str_frmt;
        break;
    case S_fill_str_frmt:
        if (in_sig == true)
            *state = S_check_frmt;
        break;
    case S_check_frmt:
        if (in_sig == true)
            *state = S_fill_data;
        else
            *state = S_wait_for_init;
        break;
    case S_fill_data:
        if(in_sig == true)
            *state = S_parse;
        break;
    case S_parse:
        if (in_sig == true)
            *state = S_send;
        else
            *state = S_wait_for_init;
        break;
    case S_send:
        *state = S_wait_for_init;
        break;
    default:
        break;
    }
}

#endif
