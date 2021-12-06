#include <xc.h>
unsigned int adc_get(unsigned char n);


unsigned int adc_get(unsigned char n)
{
    ADCON1=0x0b;ADCON2=0xa5;
    switch(n)
    {
        case 0:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x01;break;  //an0
        case 1:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x05;break;  //an1
        case 2:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x09;break;  //an2
        case 3:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x0d;break;  //an3
    }
    
    GO=1;
        while(GO==1);
        return ADRES;
}