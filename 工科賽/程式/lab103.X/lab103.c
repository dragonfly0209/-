#include <delays.h>
#include <p18f4550.h>
unsigned int adc_get(unsigned char n);

void ledon(unsigned char n);
void ledoff(unsigned char n);
void ledtgl(unsigned char n);

void led_scan(void);
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);
void led_light(unsigned char n);

void pwm0(unsigned int n);
void pwm0off(void);
void pwm1(unsigned int n);
void pwm1off(void);
void pwmalloff(void);

#pragma config CPUDIV = OSC1_PLL2, FOSC = HS
#pragma config WDT = OFF, PBADEN = OFF, XINST = OFF, LVP = OFF

unsigned int r16,r1,r2,r3;
volatile unsigned int tick,t2;

void interrupt hist(void)
{
    if(INT0IF==1)
    INT0IF=0;    
}

void interrupt low_priority list(void)
{
    if(TMR0IF==1)
    {
        TMR0IF=0;
        TMR0H=(65536-20000)>>8;
        TMR0L=(65536-20000);
        led_scan();
    }
}

void delayms(unsigned int n)
{
    Delay10KTCYx(16/4*n);
}

unsigned int HH,LL,t41,t42,t43;
unsigned long i,j;
unsigned long ff;
unsigned int HZ(void)
{
    //----
    T1CON=0xa1;    
    HH=LL=t41=t42=t43=0;
    ADCON1=0x0f;
    TRISB0=1;  
    //-----
    while(RB0==1){i++;if(i>100000)break;}i=0;
    
    while(RB0==0){i++;if(i>100000)break;}i=0;
    t41=TMR1L;
    t41+=(unsigned int)TMR1H<<8;  
    
    while(RB0==1){i++;if(i>100000)break;}i=0;
    t42=TMR1L;
    t42+=(unsigned int)TMR1H<<8;
    
    while(RB0==0){i++;if(i>100000)break;}i=0;
    t43=TMR1L;
    t43+=(unsigned int)TMR1H<<8;  
    //-----
    LL=t43-t42;
    HH=t42-t41;
    LL+=HH;
    HH*=100;
    HH+=LL/2;
    ff=1000000;
    ff/=LL;
    delayms(10);
    return ff;
}

void main(void)
{
    TRISD=0;
    TRISB=0x01;
    TRISE=0x03;
    TRISC=0;    
    ADCON1=0x0f;
    r16=0;
        
    IPEN=1;
    INTCON=0b11110000;
    TMR0IP=0;
    RBIP=1;
    TMR0IF=0;
    
    T0CON=0x88;
    TMR0H=(65536-20000)>>8;
    TMR0L=(65536-20000);
    
    while(1)
    {
        r1=adc_get(1)*5;   
        if(r1<4000)
        {
            LATC2=~LATC2;
            delayms(25);
        }
        else LATC2=1;     
        
        r2=adc_get(0)*10;
        if(r2>10000)r2=10000;
        pwm1(r2/93);
        
        r3=HZ();
        
        
        if(r3>=9890)
        {
            r3=9999;
            LATB5=0;
        }
        else LATB5=1;
        
        if((RE1==0)&&(RE0==0))
        {   
            if((r3>1975)&&(r3<2025))r3=2000;
            if((r3>975)&&(r3<1025))r3=1000;
            if((r3>7500)&&(r3<8500))r3=8000;
        }
        
        if((RE1==0)&&(RE0==1))
        {      
            r3/=5;
            if((r3>185)&&(r3<215))r3=200;
            if((r3>85)&&(r3<115))r3=100;
            if((r3>780)&&(r3<820))r3=800;
        }
        
        if((RE1==1)&&((RE0==0)||(RE0==1)))
        {       
            r3/=10;
            if((r3>45)&&(r3<55))r3=50;
            if((r3>23)&&(r3<27))r3=25;
            if((r3>190)&&(r3<210))r3=200;
        }       
        
        led_dec(r3/100,r3%100);        
    }
}
