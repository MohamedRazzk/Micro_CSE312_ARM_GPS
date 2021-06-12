#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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
bool get_lat_long (const char *gps_data , float *_lat_float , float *_long_float,char** b_lat , char** b_long)

{
    int semi_pos[10];
    char* _lat=NULL; char* _long=NULL;
    if (gps_data[3]=='G'&& gps_data[4]=='G'&& gps_data[5]=='A') {
        int counter = 0;

        for (int i = 0; i < strlen(gps_data);) {
            if (gps_data[i] == ',') {
                semi_pos[counter] = i;
                counter += 1;
            }
            i += 1;
        }

        // printf("we are in the loop\n");
        char *result = strstr(gps_data, "$GPGGA");
        int position = result - gps_data;
        // int substringLength = strlen(str) - position;

        //printf("%d\n",position);
        //  printf("%d\n",substringLength);

        _lat = substr(gps_data, position + semi_pos[1] + 1, position + semi_pos[2]);
        _long = substr(gps_data, position + semi_pos[3] + 1, position + semi_pos[4]);

        *b_lat = strcat(_lat,'\0') ; *b_long =strcat(_long,'\0');

/*
        printf("%s  %s\n",_lat,_long);
        printf("%s  %s\n",*b_lat,*b_long);
        printf("%s\n",_lat);
        printf("%s\n",_long);
*/
        //printf(" in the funcation %s \n",_lat);
        *_lat_float = atof(_lat);
        *_long_float = atof(_long);
        return true;

    }
    if (_lat == NULL || _long ==NULL) {return false;}
    return false;
} //get long and lat degrees from the data
void calc_distance(float _lat1,float _long1,float _lat2,float _long2,float *distance)
{
    int earth_r = 6371000 ;
    float lat_dif = degtorad(_lat2-_lat1);
    float long_dif = degtorad(_long2-_long1);
    float clamtinton = sin(lat_dif/2) * sin(lat_dif/2) + cos (degtorad(_lat1))* cos(degtorad(_lat2)) * sin(long_dif/2)* sin(long_dif/2);
    float comp = 2* atan2(sqrt(clamtinton), sqrt(1-clamtinton));
    *distance = earth_r * comp ;

//printf("the value of %f\n" ,*distance);

} // calculate two distancev between two points
