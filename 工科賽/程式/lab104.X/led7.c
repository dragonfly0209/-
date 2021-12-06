#include    <xc.h>
void led_scan(void);
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);
void led_light(unsigned char n);


#define D1 LATE2
#define D2 LATE1
#define D3 LATE0




static unsigned char led[10]={  0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,
                                0b10010010,0b10000010,0b11011000,0b10000000,0b10010000};
static int a=0;
static unsigned char DD1=1,DD2=0,DD3=3,dot=0,light=2;
void led_scan(void)
{
    char dd=0;
    D1=1;D2=1;D3=1;
    switch(a)
    {
        case 0:D1=0;LATD=led[DD1];
        if(dot&4){dd=1;}
        break;
        case 1:D2=0;LATD=led[DD2];
        if(dot&2){dd=1;}
        break;
        case 2:D3=0;LATD=led[DD3];
        if(dot&1){dd=1;}
        break;      
    }  
    if(dd==1)LATD7=0; 
    a++;
    if(a>light)a=0;
    
}

void led_dot(unsigned char tp)
{
    dot=tp;
}
void led_dec(unsigned int vh,unsigned int vl)
{
    DD1=vh;
    DD2=vl/10;
    DD3=vl%10;
}
void led_light(unsigned char n)
{
    switch(n)
    {        
    case 0:light=15; break;
    case 1:light=6; break;
    case 2:light=2; break;  
    }
}