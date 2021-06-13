#ifndef GPS_EXTRACT_H_
#define GPS_EXTRACT_H_
#include <stdbool.h>
#include <stdlib.h>

bool extract_GPGGA(char *raw_data, float *latitude_f, float *longitude_f)
{
    if (raw_data[3] == 'G' && raw_data[4] == 'G' && raw_data[5] == 'A')
    {
        int latitude_comma_pos[2];
        int longitude_comma_pos[2];
        int i;
        int comma_counter;
        comma_counter = 0;
        for (i = 0; (raw_data[i] != '\n' && raw_data[i] != '\0'); i++)
        {
            if (raw_data[i] == ',')
            {
                comma_counter++;
                switch (comma_counter)
                {
                case 2:
                    latitude_comma_pos[0] = i + 1;
                    break;
                case 3:
                    latitude_comma_pos[1] = i - 1;
                    break;
                case 4:
                    longitude_comma_pos[0] = i + 1;
                    break;
                case 5:
                    longitude_comma_pos[1] = i - 1;
                    break;
                default:
                    break;
                }
                if (comma_counter == 5)
                    break;
            }
        }
        int latitude_ch_len;
        int longitude_ch_len;
        latitude_ch_len = latitude_comma_pos[1] - latitude_comma_pos[0];
        longitude_ch_len = longitude_comma_pos[1] - longitude_comma_pos[0];
        if ((latitude_ch_len < 1) || (longitude_ch_len < 1))
            return false;
        else
        {
            // should add comments to explain the sizes
            char latitude_ch_tmp_deg[2];
            char longitude_ch_tmp_deg[3];
            char *latitude_ch_tmp_min = (char*) malloc(sizeof(char) * (latitude_ch_len + 2 - 2));
            char *longitude_ch_tmp_min = (char*) malloc(sizeof(char) * (longitude_ch_len + 2 - 3));
            for (i = 0; i < 2; i++)
                latitude_ch_tmp_deg[i] = raw_data[latitude_comma_pos[0] + i];
            for (i = 0; i < 3; i++)
                longitude_ch_tmp_deg[i] = raw_data[longitude_comma_pos[0] + i];
            for (i = 2; i < (latitude_ch_len - 1); i++)
                latitude_ch_tmp_min[i - 2] = raw_data[latitude_comma_pos[0] + i];
            latitude_ch_tmp_min[latitude_ch_len - 1] = '\0';
            for (i = 3; i < (longitude_ch_len - 2); i++)
                longitude_ch_tmp_min[i - 3] = raw_data[longitude_comma_pos[0] + i];
            longitude_ch_tmp_min[longitude_ch_len - 2] = '\0';
            float lat_deg, lon_deg, lat_min, lon_min;
            lat_deg = atof(latitude_ch_tmp_deg);
            lon_deg = atof(longitude_ch_tmp_deg);
            lat_min = atof(latitude_ch_tmp_min);
            lon_min = atof(longitude_ch_tmp_min);
            lat_deg += (lat_min/60.0);
            lon_deg += (lon_min/60.0);
            *latitude_f = lat_deg;
            *longitude_f = lon_deg;
            free(longitude_ch_tmp_min);
            free(latitude_ch_tmp_min);
            return true;
        }
    }
    else
        return false;
}

#endif
