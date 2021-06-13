#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


char* stringcpy(const char* original) {

    int size = strlen(original) ;
    char* copy = malloc(size + 1);

    int i;
    for(i = 0; original[i] != '\0'; i++) {
        copy[i] = original[i];
    }
    copy[i]=0;
    return copy;
}
float degtorad(float deg){
    return deg* (M_PI/180);
} //calculate the rad form degree
char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    int i;
    for (i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    *dest = '\0';

    return dest - len;
} //extract GPGGA line from data
bool get_lat_long (const char *gps_data , float *_lat_float , float *_long_float,char **b_lat , char **b_long)

{

    int semi_pos[10];
    char* _lat=NULL; char* _long=NULL;
    char* dummy_degree=NULL; 
    if (gps_data[3]=='G'&& gps_data[4]=='G'&& gps_data[5]=='A') {
        int counter = 0;
        int i;
        for (i = 0; i < strlen(gps_data);) {
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

        if (strcmp(_lat,"") == 0|| strcmp(_long,"") == 0) {return false;}

        dummy_degree = substr(_lat ,2,9); _lat = substr(_lat ,0,2);
        *_lat_float=atof(_lat)+(atof(dummy_degree)/60);

        dummy_degree = substr(_long ,3,10); _long = substr(_long ,0,3);
        *_long_float=atof(_long)+(atof(dummy_degree)/60);

        sprintf(dummy_degree,"%f",*_lat_float);
        strcat(*b_lat = stringcpy(dummy_degree),"\\");
        sprintf(dummy_degree,"%f",*_long_float);
        strcat(*b_long = stringcpy(dummy_degree),"\\");

      //  *b_lat= stringcpy(_lat) ; *b_long = stringcpy(_long);
      //  printf("Lat Long %f %f\n",*_lat_float,*_long_float);
      //printf("Bluetooh %s  %s\n",*b_lat,*b_long);
      //sprintf(dummy_degree,"%f",(atof(dummy_degree)/60));
       // *b_lat= stringcpy(_lat) ; *b_long = stringcpy(_long);
       // strcat(*b_lat,"\\");
        //strcat(*b_long,"\\");


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
