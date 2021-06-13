#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "UART7.h"
#include "LCD16x2.h"
#include "tm4c123gh6pm.h"
#include "misc_functions.h"
#include "FSM_2.h"
#include "gps_calc.h"
#include "GPS_extract.h"
#include "LED.h"

char char_exp[] =
        "$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";

#define STR_SIZE 150

int main(void)

{
    int i = 0; // character counter
    char char_arr[STR_SIZE]; // to store the GPGGA string
    GPS_FSM_t curr_state = S_wait_for_init;
    extern fpu_init();
    UART7_init();
    LCD_init();
    LED_init();
    bool in_sig0 = false;
    float longitude_f0; // previous reading
    float longitude_f1; // latest reading
    float latitude_f0;
    float latitude_f1;
    char longitude_ch[11];
    char latitude_ch[10];
    float dist_incr;
    float tot_dist = 0.0;
    char tot_dist_ch[12];
    bool enough_readings = false;
    char x;
    delay_ms(500);
    while (1)
    {
        switch (curr_state)
        {
        case S_wait_for_init:
            i = 0;
            x = UART7_read();
            if (x == '$')
            {
                in_sig0 = true;
                char_arr[i] = x;
                i++;
            }
            else
                in_sig0 = false;
            break;
        case S_fill_str_frmt:
            x = UART7_read();
            char_arr[i] = x;
            i++;
            if (x == ',')
                in_sig0 = true;
            else
                in_sig0 = false;
            break;
        case S_check_frmt:
            if (char_arr[3] == 'G' && char_arr[4] == 'G' && char_arr[5] == 'A')
                in_sig0 = true;
            else
                in_sig0 = false;
            break;
        case S_fill_data:
            x = UART7_read();
            char_arr[i] = x;
            i++;
            if (x == '\n' || (i == STR_SIZE))
                in_sig0 = true;
            else
                in_sig0 = false;
            break;
        case S_parse:
            in_sig0 = extract_GPGGA(char_arr, &latitude_f1, &longitude_f1);
            if (in_sig0 == true)
            {
                if (enough_readings == true)
                {
                    calc_distance(latitude_f0, longitude_f0, latitude_f1,
                                  longitude_f1, &dist_incr);
                    tot_dist += dist_incr;
                    if (tot_dist > 100.0)
                        turn_on_LED();
                    sprintf(tot_dist_ch, "%.6f", tot_dist);
                    LCD_clear();
                    write_str_4bit(tot_dist_ch);
                }
                else
                    enough_readings = true;
                sprintf(latitude_ch, "%.6f", latitude_f1);
                sprintf(longitude_ch, "%.6f", longitude_f1);
                latitude_f0 = latitude_f1;
                longitude_f0 = longitude_f1;
            }
            break;
        case S_send:
            // UART7_write_str("Latitude: ");
            UART7_write_str(latitude_ch);
            UART7_write_str("\t");
            // UART7_write_str("Longitude: ");
            UART7_write_str(longitude_ch);
            UART7_write_str("\n");
            break;
        default:
            break;
        }
        change_state(&curr_state, in_sig0);
    }
}
