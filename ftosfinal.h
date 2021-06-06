#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#include "LCD16x2"

void reverse(char arr[],int length)
{
    
 //temp arr
 char* temparr = (char*) malloc(length*sizeof(char));

   int i=0 ; 
while(i<length)
{
    temparr[i] = arr[length-1-i];
    i++;
}
   i=0;  
while(i<length)
{
   arr[i] = temparr[i];
    i++;
}
 

}
//flag 1 ->int part 
//flag 0 ->fractional part
int int_to_string(int x, char intpart[],int numfloats,int flag)
{ 
    int i=0;
    while(x){
    intpart[i++] = (x%10)+'0';
     x = x/10; 
    }
    //reverse array
    if(!flag){
     while (i < numfloats)
        intpart[i++] = '0';
        
    }
      reverse(intpart, i);
    return i;
}

void float_to_string(float x,char intparts[],char fractparts[],int numfloats)
{
    int intpart = x/1;
    float fpart = x - (float)intpart;
    fpart = fpart * pow(10, numfloats);
    
    //convert int part -> string and put '.' at the end
   int i = int_to_string(intpart,intparts,numfloats,1);
   
      intparts[i] = '.';
 
   
    //convert the fractional part
   i =  int_to_string((int)fpart,fractparts,numfloats,0);
   
   
   
}

void stringarrayfinal(char intparts[],char fractparts[],char finalchararr[])
{
      // printf("%zu",strlen(intparts));
   //conacatinate both int and fractional part

   strcpy(finalchararr, intparts); /* copy int part into final */
   strcat(finalchararr, fractparts); /*concat with fract */
   
    
}

//fn to dispaly string in LCD
void LCD_Display_String(float x)
{

  char* intparts;
  char* fractparts;
  intparts  = (char*) malloc(10*sizeof(char));
  fractparts  = (char*) malloc(10*sizeof(char));

  float_to_string(x,intparts,fractparts,6);
 

 char* finalchararr = (char*)malloc(strlen(fractparts)+strlen(intparts));
stringarrayfinal(intparts,fractparts,finalchararr);

for(int i=0;finalchararr[i] != '\0';i++ )
{
   write_char_4bit(finalchararr[i]);
}
}
