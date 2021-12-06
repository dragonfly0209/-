#include    <p18f4550.h>
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
void pwm0(unsigned int n);
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
    TMR0H=(65536-8000)>>8;  //2ms
    TMR0L=(65536-8000);
    led_scan();
    tick++;t2++;
}
void delay_ms(unsigned int ms)
{
    ms>>=1;ms+=tick;
    while(ms!=tick);       
}
//-------

//fn100
unsigned int fn100(void)
{
    if((adc_get(3)*5)<100)
            {                
                pwm1();r100=500;     
            }
            else
            {
                pwm1off();r100=0;
            }
    return r100;
}
//

//------fn101
unsigned int HH,LL,t41,t42,t43;
unsigned long i;
unsigned long ff;
unsigned int fn101(void)
{
    //----
    T1CON=0xa1;    
    HH=LL=t41=t42=t43=0;
    ADCON1=0x0f;
    TRISA0=1;    
    //-----
    while(RA0==1){i++;if(i>100000)break;}i=0;
    
    while(RA0==0){i++;if(i>100000)break;}i=0;
    t41=TMR1L;
    t41+=(unsigned int)TMR1H<<8;  
    
    while(RA0==1){i++;if(i>100000)break;}i=0;
    t42=TMR1L;
    t42+=(unsigned int)TMR1H<<8;
    
    while(RA0==0){i++;if(i>100000)break;}i=0;
    t43=TMR1L;
    t43+=(unsigned int)TMR1H<<8;  
    //-----   
    LL=t43-t42;
    HH=t42-t41;
    LL+=HH;
    HH*=100;
    HH+=LL/2;
    ff=10000000;
    ff/=LL;
    return (HH/LL);              
}
//

//fn110
void fn110(void)
{
    r16=adc_get(2)/256;
    led_dec(88,88);
    switch(r16)
    {
        case 0:led_light(0);ledoff(1);ledoff(2);break;
        case 1:led_light(1);ledoff(1);ledon(2);break;
        case 2:led_light(2);ledon(1);ledoff(2);break;
        case 3:led_light(3);ledon(1);ledon(2);break;
    }
    
}
//

//fn111

void fn111_led(void)
{
    if(t2>450)
    {
        ledtgl(1);
        LATB5=~LATB4;
        t2=0;
    }    
}

unsigned int fn111(void)
{
    //----
    T1CON=0xa1;    
    HH=LL=t41=t42=t43=0;
    ADCON1=0x0f;
    TRISA0=1;  
    //-----
    while(RA0==1){i++;fn111_led();if(i>100000)break;}i=0;
    
    while(RA0==0){i++;fn111_led();if(i>100000)break;}i=0;
    t41=TMR1L;
    t41+=(unsigned int)TMR1H<<8;  
    
    while(RA0==1){i++;fn111_led();if(i>100000)break;}i=0;
    t42=TMR1L;
    t42+=(unsigned int)TMR1H<<8;
    
    while(RA0==0){i++;fn111_led();if(i>100000)break;}i=0;
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
    return ff;
}

//

//main
void main(void)
{   //---初始值
    TRISB=0;
    TRISD=0;
    TRISE=0xf;
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
    while(1)
    {          
        switch(PORTE&0x7)
        {
            case 0: ledoff(1);ledon(2); r16=adc_get(1)*4.9;       if(r16>5000)r16=5000;
                    led_dec(r16/100,r16%100);   led_dot(8); led_light(3); pwmalloff();break;                  //000
                    
            case 4: ledon(1);ledoff(2); r16=adc_get(2)*4.9;     if(r16>5000)r16=5000;
                    led_dec(r16/100,r16%100);   led_dot(8); led_light(3); pwmalloff();break;                  //001
                    
            case 2: ledon(1);ledon(2);  r16=adc_get(3)*5;     if(r16>5000)r16=5000;
                    led_dec(r16/100,r16%100);   led_dot(8); led_light(3); pwmalloff();break;                  //010
            
            case 6: ledoff(1);ledon(2); r16=adc_get(2);         if(r16>1000)r16=1000;pwm0(r16+10);
                    led_dec(r16/100,r16%100);   led_dot(2); led_light(3); pwm1off();  break;                  //011 
            
            case 1: ledon(1);ledoff(2); r16=fn100();            
                    led_dec(r16/100,r16%100);   led_dot(2); led_light(3); pwm0off();  break;                  //100
           
            case 5: ledon(1);ledon(2);  r16=fn101()*10;         if(r16<200)r16=200;if(r16>800)r16=800;
                    led_dec(r16/100,r16%100);   led_dot(2); led_light(3); pwmalloff();break;                  //101
                            
            case 3: fn110();            led_dot(0x0a);      pwmalloff();break;                                //110
            
            case 7: r16=fn111();            if(r16>4999)r16=4999;
                    led_dec(r16/100,r16%100);   led_dot(2); led_light(3); pwmalloff();break;                  //111            
        }             
        Delay10KTCYx(16/4*10);  //10k*1us*10=10ms 
    }
}
