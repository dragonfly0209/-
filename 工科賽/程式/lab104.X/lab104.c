#include <xc.h>
#include <delays.h>
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
void pwm1(void);
void pwm1off(void);
void pwmalloff(void);

#define led LATC1

#pragma config CPUDIV = OSC1_PLL2, FOSC = HS
#pragma config WDT = OFF, PBADEN = OFF, XINST = OFF, LVP = OFF

unsigned int r16,cyn70,getv;
volatile unsigned int tick,t2,t3;
int flag=0;

void interrupt hisr(void)
{
    TMR0IF=0;
    TMR0H=(65536-4000)>>8;//1ms
    TMR0L=(65536-4000);
    led_scan();
    tick++;t2++;t3++;
    if(flag==1){if(t2==495)led=1;if(t2>=990){t2=0;led=0;}}
    if(flag==2){if(t3==49) led=1;if(t3>=99) {t3=0;led=0;}}
}
void delay_ms(unsigned int ms)
{
    ms+=tick;
    while(ms!=tick);       
}

/*
//-----·Å·Ã«×
void dht11(void)
{
    unsigned char x,z,h1,h2;
    TRISC2=0;
    LATC2=1;
    delay_ms(100);
    LATC2=0;
    delay_ms(20);
    LATC2=1;
    Delay10TCYx(1);
    TRISC2=1;
    
    while(PORTCbits.RC2==1);
    while(PORTCbits.RC2==0);    
       
    while(PORTCbits.RC2==1);
    while(PORTCbits.RC2==0);
    
    for(z=0;z<8;z++)
    {
        for(x=0;x<250;x++)
        {
            if(PORTCbits.RC2==0)break;
        }
        while(PORTCbits.RC2==0);
    
        h1<<=1; h1+=(x>20);
    }
    r16=h1;
    led_dec(r16/100,r16%100);

    
}
*/

//Åª¨ú
unsigned char getsw(void)
{
    unsigned char s0=1;
    
    getv=adc_get(0);
    if(getv<1000)delay_ms(10);
    getv=adc_get(0);
    
    
    if(getv>250){s0=2;}
    if(getv>600){s0=3;}
    if(getv>850){s0=0;}
    
    return s0;
}
//

//
void rc7clock(void)
{
    unsigned char a,b,c;
    TRISC7=0;
    for(a=150;a>0;a--)
    {
        LATC7=1;
        Delay10TCYx(8);NOP();NOP();NOP();NOP();
        LATC7=0;
        Delay10TCYx(8);NOP();NOP();NOP();
    }
}

void taska(void)
{
    int r1,r2;
    TRISC6=TRISC7=0;
    TRISB=0xff;
    led_light(2);
    while(1)
    {
        led=0;
        
        LATC6=1;
        Delay10TCYx(2);Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        LATC6=0;               //1
        
        rc7clock();          //2
        
        r1=PORTB&0x0f;
        r2=PORTB>>4;
        r16=r2*10+r1;
        led_dec(0,r16);   //3  //9--->16  25-->32
        delay_ms(50);
                
        if(getsw()==1)break;
    }
    a:while(getsw()!=0)
    goto a;
}

void taskb(void)
{
    unsigned int dt=0;
    pwm0(0);
    led_light(2);
    while(1)
    {              
        pwm0(dt);
        led_dec((dt*2)/100,(dt*2)%100);
            
        if(getsw()==3)
        {
            if(dt<=45)dt+=5;
            led_dec((dt*2)/100,(dt*2)%100);
            pwm0(dt);
            b3:while(getsw()!=0)
            goto b3;
        }
        if(getsw()==2)
        {
            if(dt>=5)dt-=5;
            led_dec((dt*2)/100,(dt*2)%100);
            pwm0(dt);
            b2:while(getsw()!=0)
            goto b2;
        }
        
        if(getsw()==1)break;
    }    
    pwm0off();
    b1:while(getsw()!=0)
    goto b1;
    
}


/*
void taskb1(void)
{
    unsigned int dt=0,ss;
    led_light(2);
    while(1)
    {
        
        pwm0(1);
        delay_ms(dt);   
        pwm0off();
        delay_ms(10-dt);
        
            led_dec(dt*10/100,dt*10%100);
            
            ss=getsw();
            if(ss==3){if(dt<=9)dt+=1;}
            if(ss==2){if(dt>=1)dt-=1;}
            if(ss==1)break;
    }
    delay_ms(500);
}
*/
void taskc(void)
{   
    led_light(2);
    while(1)
    {    
        r16=adc_get(1);
        if(r16>999)r16=999;
        
        r16=999-r16;
        led_dec(r16/100,r16%100);
            
        if(getsw()==1)break;
    }
    c:while(getsw()!=0)
    goto c;
}

void taskd(void)
{
    led_light(2); 
    while(1)
    {
        led=1;
        r16=888;
        
        cyn70=adc_get(2)/256;
        if(cyn70>=1)led_light(2);
        if(cyn70==2)led_light(1);
        if(cyn70==3)led_light(0); 
        
        led_dec(r16/100,r16%100);

        if(getsw()==1)break;
    }
    d:while(getsw()!=0)
    goto d;
}

//-----
void main(void)
{
    TRISE=0;
    TRISD=0;
    TRISC=0;
    TRISA0=1;
    ADCON1=0x0f;
    r16=0;
    
    T0CON=0x88;
    TMR0H=(65536-4000)>>8;
    TMR0L=(65536-4000);
    
    IPEN=1;
    TMR0IE=1;
    TMR0IF=0;
    TMR0IP=1;
    GIEL=1;
    GIEH=1;
    
    
   /* 
   while(1)
    {
       dht11();
        rc7clock();
        r16=getsw();
        led_dec(r16/100,r16%100);
        delay_ms(100);
    }*/
    
    
    while(1)
    {
        taska();flag=1;
        taskb();flag=2;
        taskc();flag=3;
        taskd();flag=0;
    }
}
//------