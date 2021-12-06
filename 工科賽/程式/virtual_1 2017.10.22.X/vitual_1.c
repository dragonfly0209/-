#include    <xc.h>
#include    <delays.h>

//led7
void led_scan(void);
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);
void led_light(unsigned char n);
void ledscan(void);
//

//led
void ledon(unsigned char n);
void ledoff(unsigned char n);
void ledtgl(unsigned char n);
//

//pwm
void pwm0(unsigned int n);//1khz
void pwm0off(void);
void pwm1(void);
void pwm1off(void);
void pwmalloff(void);
//

//adc
unsigned int adc_get(unsigned char n);
//
#pragma config CPUDIV = OSC1_PLL2, FOSC = HS
#pragma config WDT = OFF, PBADEN = OFF, XINST = OFF, LVP = OFF
unsigned int r16,r100;

//interrupt
volatile unsigned int tick,t2;
void interrupt hisr(void)
{
    TMR0IF=0;
    TMR0H=(65536-4000)>>8;  //2ms
    TMR0L=(65536-4000);
    led_scan();
    tick++;t2++;
}
void delay_ms(unsigned int ms)
{
    ms+=tick;
    while(ms!=tick);       
}

void main(void)
{   //---初始值
    unsigned int x,temp,x1,x2,x3,x4;
    TRISB=0XF0;
    TRISD=0;
    TRISE=0;
    TRISA2=1;
    //adc
    ADCON1=0x0F;   
    //---timer
    T0CON=0x88;
    TMR0H=(65536-20000)>>8;
    TMR0L=(65536-20000);
    //--中斷設定
    IPEN=1;
    TMR0IE=1;
    TMR0IF=0;  
    TMR0IP=1;
    GIEL=1;
    GIEH=1;
    //---    
    ledoff(1);ledoff(2);ledoff(3);
    x1=550;x2=700;x3=670;x4=800;
    while(1)
    {
        if(RB7==0)
        {
            led_dot(0);
            r16=adc_get(0);
            led_dec(r16/100,r16%100);
                      
            if(r16<x1)
            {
                pwm0off();ledon(1);ledoff(2);ledoff(3);
            }
            
            if((r16>x1)&&(r16<x3))
            {
                pwm0(x2/10);ledoff(1);ledon(2);ledoff(3);
            }
            
            if(r16>x3)
            {
                pwm0(x4/10);ledoff(1);ledoff(2);ledon(3);
            }
        }
     
        if((RB7==1)&&(RB6==0))
        {
            ledoff(1);ledoff(2);ledoff(3);pwm0off();  
            if((RB5==0)&&(RB4==0))
            {
                led_dec(x1/100,x1%100);led_dot(0);
            }
            if((RB5==0)&&(RB4==1))
            {
                led_dec(x2/100,x2%100);led_dot(2);
            }
            if((RB5==1)&&(RB4==0))
            {
                led_dec(x3/100,x3%100);led_dot(0);
            }
            if((RB5==1)&&(RB4==1))
            {
                led_dec(x4/100,x4%100);led_dot(2);
            }
        }
        
        if((RB7==1)&&(RB6==1))
        {
            ledon(1);ledon(2);ledon(3);pwm0off();              

            if((RB5==0)&&(RB4==0))
            {
                r16=adc_get(1);if(r16>1000)r16=1000;led_dec(r16/100,r16%100);led_dot(0);
                if(RA2==1)x1=r16;
            }
            if((RB5==0)&&(RB4==1))
            {
                r16=adc_get(1);if(r16>1000)r16=1000;led_dec(r16/100,r16%100);led_dot(2);
                if(RA2==1)x2=r16;
            }
            if((RB5==1)&&(RB4==0))
            {
                r16=adc_get(1);if(r16>1000)r16=1000;led_dec(r16/100,r16%100);led_dot(0);
                if(RA2==1)x3=r16;
            }
            if((RB5==1)&&(RB4==1))
            {
                r16=adc_get(1);if(r16>1000)r16=1000;led_dec(r16/100,r16%100);led_dot(2);
                if(RA2==1)x4=r16;
            }
        }
    }  
 }
