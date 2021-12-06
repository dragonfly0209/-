#include <xc.h>
void ledon(unsigned char n);
void ledoff(unsigned char n);
void ledtgl(unsigned char n);

#define led1 LATB4
#define led2 LATB5
#define led3 LATC2


void ledon(unsigned char n)
{   TRISB4=0;TRISB5=0;TRISC2=0;
    switch(n)
    {
        case 1:led1=1;break;
        case 2:led2=1;break;
        case 3:led3=1;break;
    }
}
void ledoff(unsigned char n)
{
    TRISB4=0;TRISB5=0;TRISC2=0;
    switch(n)
    {
        case 1:led1=0;break;
        case 2:led2=0;break;
        case 3:led3=0;break;
    }
    
}
void ledtgl(unsigned char n)
{
    TRISB4=0;TRISB5=0;TRISC2=0;
    switch(n)
    {
        case 1:led1^=1;break;
        case 2:led2^=1;break;
        case 3:led3^=1;break;
    }
}