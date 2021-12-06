#include <xc.h>
void led_scan(void);
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);
void led_light(unsigned char n);


#define D1 LATB3
#define D2 LATB2
#define D3 LATB1
#define D4 LATB0



static unsigned char led[10]={  0b00000011,0b10011111,0b00100101,0b00001101,0b10011001,
                                0b01001001,0b01000001,0b00011011,0b00000001,0b00001001};
static int a=0;
static unsigned char DD1=1,DD2=0,DD3=3,DD4=4,dot=0,light=3;
void led_scan(void)
{
    char dd=0;
    D1=1;D2=1;D3=1;D4=1;
    switch(a)
    {
        case 0:D1=0;LATD=led[DD1];
        if(dot&8){dd=1;}
        break;
        case 1:D2=0;LATD=led[DD2];
        if(dot&4){dd=1;}
        break;
        case 2:D3=0;LATD=led[DD3];
        if(dot&2){dd=1;}
        break;
        case 3:D4=0;LATD=led[DD4];
        if(dot&1){dd=1;}
        break;       
    }  
    if(dd==1)LATD0=0; 
    if(light!=15){a++;}else{a=15;}
   
    if(a>light)a=0;
    
}

void led_dot(unsigned char tp)
{
    dot=tp;
}
void led_dec(unsigned int vh,unsigned int vl)
{
    DD1=vh/10;
    DD2=vh%10;
    DD3=vl/10;
    DD4=vl%10;
}
void led_light(unsigned char n)
{
    switch(n)
    {        
    case 0:light=15;break;
    case 3:light=3; break;
    case 2:light=7; break;
    case 1:light=11;break;
    }
}