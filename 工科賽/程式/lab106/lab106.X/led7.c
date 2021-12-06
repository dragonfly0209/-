#include <p18f4550.h>
void led_scan(void);//参苯磞
void ledscan(void); //だ秨苯磞
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);
void leddec(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4);
void led_light(unsigned char n);


#define D1 LATBbits.LATB3
#define D2 LATBbits.LATB2
#define D3 LATBbits.LATB1
#define D4 LATBbits.LATB0



static unsigned char led[11]={  0b00000011,0b10011111,0b00100101,0b00001101,0b10011001,
                                0b01001001,0b01000001,0b00011011,0b00000001,0b00001001,0b11111101};
static int a=0;
static unsigned char DD1=10,DD2=10,DD3=10,DD4=10,dot=0,light=3;
void led_scan(void)//参苯磞
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
    if(dd==1)LATDbits.LATD0=0; 
    if(light!=18){a++;}else{a=18;}
   
    if(a>light)a=0;
    
}
/*
void ledscan(void)//だ秨苯磞
{
    char dd=0;
    D1=1;D2=1;D3=1;D4=1;
    switch(a)
    {
        case 0:D1=0;
        LATD7=led[DD1]>>7;
        LATD6=led[DD1]>>6;
        LATD5=led[DD1]>>5;
        LATD4=led[DD1]>>4;
        LATD3=led[DD1]>>3;
        LATD2=led[DD1]>>2;
        LATD1=led[DD1]>>1;
        LATD0=led[DD1]>>0;
        if(dot&8){dd=1;}
        break;
        case 1:D2=0;
        LATD7=led[DD2]>>7;
        LATD6=led[DD2]>>6;
        LATD5=led[DD2]>>5;
        LATD4=led[DD2]>>4;
        LATD3=led[DD2]>>3;
        LATD2=led[DD2]>>2;
        LATD1=led[DD2]>>1;    
        LATD0=led[DD2]>>0;
        if(dot&4){dd=1;}
        break;
        case 2:D3=0;
        LATD7=led[DD3]>>7;
        LATD6=led[DD3]>>6;
        LATD5=led[DD3]>>5;
        LATD4=led[DD3]>>4;
        LATD3=led[DD3]>>3;
        LATD2=led[DD3]>>2;
        LATD1=led[DD3]>>1;    
        LATD0=led[DD3]>>0;
        if(dot&2){dd=1;}
        break;
        case 3:D4=0;
        LATD7=led[DD4]>>7;
        LATD6=led[DD4]>>6;
        LATD5=led[DD4]>>5;
        LATD4=led[DD4]>>4;
        LATD3=led[DD4]>>3;
        LATD2=led[DD4]>>2;
        LATD1=led[DD4]>>1;    
        LATD0=led[DD4]>>0;
        if(dot&1){dd=1;}
        break;       
    }  
    if(dd==1)LATD0=0; 
    if(light!=15){a++;}else{a=15;}
    if(a>light)a=0;
}*/

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
void led_light(unsigned char n)   //4计
{
    switch(n)
    {        
    case 0:light=18;break;
    case 3:light=3; break;
    case 2:light=8; break;
    case 1:light=13;break;
    }
}


/*void led_light(unsigned char n)  //3计
{
    switch(n)
    {        
    case 0:light=15; break;
    case 1:light=6; break;
    case 2:light=2; break;  
    }
}*/
void leddec(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4)
{
    DD1=v1;
    DD2=v2;
    DD3=v3;
    DD4=v4;
}