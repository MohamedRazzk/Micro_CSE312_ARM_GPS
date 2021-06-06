#include <stdio.h>
#include "gps_calc.h"

int main() {




    float _lat_float ;float _long_float ;
    char *gps_data = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,05,2.68,129.0,M,50.1,M,,*42";
    get_lat_long(gps_data,&_lat_float,&_long_float);

/*

  printf("%f\n",_lat_float); //float
  printf("%f\n",_long_float); //float
*/

    float distance ,total_distance ;

    calc_distance(40.689202777778,74.044219444444,38.889069444444,77.034502777778,&distance);

    total_distance +=distance;

    printf("%f\n",distance);
    printf("The total distance = %f M",total_distance);
    return 0;
}