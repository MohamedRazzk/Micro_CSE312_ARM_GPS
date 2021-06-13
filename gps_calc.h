#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

float degtorad(float deg)
{
    return deg * (M_PI / 180.0);
}

void calc_distance(float _lat1, float _long1, float _lat2, float _long2, float *distance)
{
    float earth_r = 6371 000.0;
    float lat_dif = degtorad(_lat2 - _lat1);
    float long_dif = degtorad(_long2 - _long1);
    float clamtinton = sin(lat_dif / 2.0) * sin(lat_dif / 2.0)
                    + cos(degtorad(_lat1)) * cos(degtorad(_lat2)) * sin(long_dif / 2.0)
                    * sin(long_dif / 2.0);
    float comp = 2.0 * atan2(sqrt(clamtinton), sqrt(1.0 - clamtinton));
    *distance = earth_r * comp;
}