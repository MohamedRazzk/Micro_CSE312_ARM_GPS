

void PORTF_INT(void){
    SYSCTL_RCGCGPIO_R |= 0x00000020;

    while((SYSCTL_PRGPIO_R& 0x00000020) == 0){};
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;

}
void check_distance(float  distance){

         while(distance >= 100)
         {
             GPIO_PORTF_DATA_R |= 2;
         }

}
