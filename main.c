#include <stdio.h>
#include "headers/gps_calc.h"

int main() {

    float _lat_float , _long_float, distance ,p_lat_float,p_long_float ;
    float  total_distance = 0 ;
    //this main for dummy try that code is calculating the distance in the right way
    char *gps_data[6];
    gps_data[0]="$GPGGA,002153.000,30.065381,N,31.276990,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[1]="$GPGGA,002153.000,30.065632,N,31.277625,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[2]="$GPGGA,002153.000,30.065827,N,31.278272,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[3]="$GPGGA,002153.000,30.065988,N,31.278778,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[4]="$GPGGA,002153.000,30.066205,N,31.279398,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[5]="$GPGGA,002153.000,30.066322,N,31.279786,W,1,05,2.68,129.0,M,50.1,M,,*42";

   // char *gps_data = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,05,2.68,129.0,M,50.1,M,,*42";

   for (int i =0 ; i<6;)
   {

       get_lat_long(gps_data[i],&_lat_float,&_long_float);
       if (i>=1)
       {
           calc_distance(p_lat_float,p_long_float,_lat_float,_long_float,&distance);
           total_distance +=distance;
           printf("Moved Distance : %f\n",distance);

       }
       p_lat_float = _lat_float;
       p_long_float = _long_float;
       i+=1;
   }


    printf("Totall distance That We Moved %f\n",total_distance);

    /*get_lat_long(gps_data,&_lat_float,&_long_float);

*//*

  printf("%f\n",_lat_float); //float
  printf("%f\n",_long_float); //float
*//*



    calc_distance(40.689202777778,74.044219444444,38.889069444444,77.034502777778,&distance);
    total_distance +=distance;
    printf("%f\n",distance);
    printf("The total distance = %f M",total_distance);*/
    return 0;
}