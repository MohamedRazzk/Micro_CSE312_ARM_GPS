#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>

float degtorad(float deg){
    return deg* (M_PI/180);
} //calculate the rad form degree
char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    *dest = '\0';

    return dest - len;
} //extract GPGGA line from data
void get_lat_long (const char *gps_data , float *_lat_float , float *_long_float)

{
    int semi_pos[10];
    char* _lat; char* _long;
    if (gps_data[3]=='G'&& gps_data[4]=='G'&& gps_data[5]=='A')
    {
        int counter =0;

        for (int i =0 ; i < strlen(gps_data);)

        {
            if (gps_data[i]==','){semi_pos[counter]=i; counter+=1; }
            i +=1;
        }

        // printf("we are in the loop\n");
        char *result = strstr(gps_data, "$GPGGA");
        int position = result - gps_data;
        // int substringLength = strlen(str) - position;

        //printf("%d\n",position);
        //  printf("%d\n",substringLength);

        _lat = substr(gps_data,position+semi_pos[1]+1,position+semi_pos[2]);
        _long = substr(gps_data,position+semi_pos[3]+1,position+semi_pos[4]);
/*

        printf("%s\n",_lat);
        printf("%s\n",_long);
*/

        *_lat_float= atof(_lat);
        *_long_float = atof(_long);

    }
} //get long and lat degrees from the data

int main() {
    
  /* float _lat_float ;float _long_float ;
   char *gps_data = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,05,2.68,129.0,M,50.1,M,,*42";

   get_lat_long(gps_data,&_lat_float,&_long_float);



  printf("%f\n",_lat_float); //float
  printf("%f\n",_long_float); //float


  float distance ,total_distance ;

   calc_distance(40.689202777778,74.044219444444,38.889069444444,77.034502777778,&distance);

   total_distance +=distance;

    printf("%f\n",distance);
    printf("The total distance = %f KM",total_distance);*/
    return 0;
}





