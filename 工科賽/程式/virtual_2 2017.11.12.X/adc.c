#include <xc.h>
unsigned int adc_get(unsigned char n);


unsigned int adc_get(unsigned char n)
{
    ADCON1=0x0c;ADCON2=0xa5;
    switch(n)
    {
        case 0: ADCON1=0x0c;ADCON2=0xa5;ADCON0=0x01;break;  //an0
        case 1: ADCON1=0x0c;ADCON2=0xa5;ADCON0=0x05;break;  //an1
        case 2: ADCON1=0x0c;ADCON2=0xa5;ADCON0=0x09;break;  //an2
        //case 3: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x0d;break;  //an3
        /*
	case 4: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x11;break;  //an4
        case 5: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x15;break;  //an5
        case 6: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x19;break;  //an6
        case 7: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x1d;break;  //an7
	case 8: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x21;break;  //an8
        case 9: ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x25;break;  //an9
        case 10:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x29;break;  //an10
        case 11:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x2d;break;  //an11
        case 12:ADCON1=0x0b;ADCON2=0xa5;ADCON0=0x31;break;  //an12
   
	*/
    }
    
    GO=1;
        while(GO==1);
        return ADRES;
}