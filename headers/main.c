#include <stdio.h>
#include "gps_calc.h"

int main() {

    bool check_flag ; int s_counter=1;
    float _lat_float , _long_float, distance ,p_lat_float,p_long_float ,total_distance = 0  ;

    //this main for dummy try that code is calculating the distance in the right way
    char *gps_data[8]; char *b_lat =NULL , *b_long=NULL ;



    gps_data[0]=",,,,,,,,,,,,,,";
    gps_data[1]="$GPGGA,,,,,,,,,,,,,,";
    gps_data[2]="$GPGGA,002153.000,3006.53811,N,03127.69901,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[3]="$GPGGA,002153.000,3006.56321,N,03127.76251,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[4]="$GPGGA,002153.000,3006.58271,N,03127.82721,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[5]="$GPGGA,002153.000,3006.59881,N,03127.87781,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[6]="$GPGGA,002153.000,3006.62051,N,03127.93981,W,1,05,2.68,129.0,M,50.1,M,,*42";
    gps_data[7]="$GPGGA,002153.000,3006.63221,N,03127.97861,W,1,05,2.68,129.0,M,50.1,M,,*42";


   // char *gps_data = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,05,2.68,129.0,M,50.1,M,,*42";



   for (int i =0 ; i<8;)
   {

      check_flag =get_lat_long(gps_data[i],&_lat_float,&_long_float ,&b_lat,&b_long);
       if (check_flag==false){s_counter+=1;}
       if (i>=s_counter)
       {
           calc_distance(p_lat_float,p_long_float,_lat_float,_long_float,&distance);
           total_distance +=distance;
          // printf("Moved Distance : %f\n",distance);

       }
       p_lat_float = _lat_float;
       p_long_float = _long_float;
       i+=1;

      // printf("Float %f  %f\n",_lat_float,_long_float); //for printing float number returned
       //printf("Blue  %s  %s\n",b_lat,b_long); //for printing Bluetooth data which will be set
   }


    printf("Totall distance That We Moved %f\n",total_distance);

    return 0;
}