#include    <p18f4550.h>
#include    <delays.h>

//led7
void led_scan(void);
void led_dot(unsigned char tp);
void led_dec(unsigned int vh,unsigned int vl);//2
void leddec(unsigned int vh1,unsigned int vh2,unsigned int vl1,unsigned int vl2);
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
long r16=0,r100=0,get=0;
unsigned int DD1,DD2,DD3,DD4;

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

void motor1(int x)
{   
    x=90-x;
    if(x<9)x=9;
    x=x/9;
    LATC2=1;
    Delay100TCYx(16/4*4);      
    Delay100TCYx(16/4*x);
    LATC2=0;
    Delay1KTCYx(16/4*20);    
}

void motor2(int x)
{
    if(x<9)x=9;
    x=x/9;
    LATC2=1;
    Delay100TCYx(16/4*13);
    Delay100TCYx(16/4*x);
    LATC2=0;
    Delay1KTCYx(16/4*20);   
}
void motor(int x)
{   if(x<10)x=10;
    x/=10;
    LATC2=1;
    Delay100TCYx(16/4*4);
    Delay100TCYx(16/4*x);
    LATC2=0;
    Delay1KTCYx(16/4*20);
}
unsigned int HH,LL,t41,t42,t43;
unsigned long i;
unsigned long ff;
unsigned int fn111(void)
{
    //----
    T1CON=0xa1;    
    HH=LL=t41=t42=t43=0;
    ADCON1=0x0f;
    TRISC1=1;  
    //-----
    while(RC1==1){i++;if(i>10000000)break;}i=0;
    
    while(RC1==0){i++;if(i>10000000)break;}i=0;
    t41=TMR1L;
    t41+=(unsigned int)TMR1H<<8;  
    
    while(RC1==1){i++;if(i>10000000)break;}i=0;
    t42=TMR1L;
    t42+=(unsigned int)TMR1H<<8;
    
    while(RC1==0){i++;if(i>10000000)break;}i=0;
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

/*void main(void)
{   //---初始值
    TRISB=0xf0;
    TRISD=0;
    TRISE=0;
    TRISC=0;
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
    unsigned int x1,x2,y;
    while(1)
    {
        switch(0xf0&PORTB)
        {
            case 0x00:led_dot(0);get=adc_get(1)/9;if(get>90)get=90;leddec(10,10,get/10,get%10);motor1(get);break;//
            
            case 0x10:led_dot(0);get=adc_get(2)/9;if(get>90)get=90;leddec(10,10,get/10,get%10);motor2(get);break;//
            
            case 0x20:led_dot(0);x1=adc_get(1)/9;x2=get=adc_get(2)/9;if(x1>90)x1=90;if(x2>90)x2=90;motor_stop();
                if(x1<10){leddec(10,x1%10,x2/10,x2%10);}
                if(x2<10){leddec(x1/10,x1%10,10,x2%10);}
                if((1<10)&&(x2<10)){leddec(10,x1%10,10,x2%10);}
                led_dec(x1,x2);
                break;//
            
            case 0x30:led_dot(0);x1=adc_get(1)/9;x2=get=adc_get(2)/9;
                if(x1>x2){y=x1-x2;leddec(11,10,y/10,y%10);motor1(y);}
                if(x1<x2){y=x2-x1;leddec(10,10,y/10,y%10);motor2(y);}
                break;//
            
            
            
            case 0x40:led_dot(0);get=adc_get(1);x1=get/100;x2=get%100;led_dec(x1,x2);break;
            
            
            case 0x50:break;
            case 0x60:break;
            case 0x70:break;
            
            
            
            case 0x80:led_dot(0);get=adc_get(0);x1=get/100;x2=get%100;led_dec(x1,x2);motor_stop();break;//
            case 0x90:
            if(RA3==1){y++;if(y<1)y=0;}
            if(y==1)get=adc_get(0);
            if(get<235)r16=0;
            if((get>235)&&(get<340))r16=100;
            if((get>340)&&(get<455))r16=200;
            if((get>455)&&(get<570))r16=300;
            if((get>570)&&(get<670))r16=400;
            if((get>670)&&(get<760))r16=500;
            x1=r16/100;x2=r16%100;
            leddec(x1/10,x1%10,x2/10,x2%10);led_dot(2);
            break;
            
            case 0xc0:get=fn111()/100;x1=get/100;x2=get%100;led_dot(2);
            if(get<10)leddec(0,0,x2/10,x2%10);
            if(get<100)leddec(0,x1%10,x2/10,x2%10);
            leddec(x1/10,x1%10,x2/10,x2%10);
            delay_ms(250);break;//
        }
    }    
}*/



void main(void)
{
    TRISB=0xf0;
    TRISD=0;
    TRISE=0;
    TRISC=0;
    TRISA3=1;
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
    unsigned int x1=0,x2=0,y=0,x1y=0,x2y=0,i=100;
    while(1)
    {
        switch(0xf0&PORTB)
        {
            case 0x00:
                led_dot(0);get=adc_get(1);
                if(adc_get(1)<=660)get=0;
                else get-=660;  
                if(get>90)get=90;leddec(10,10,get/10,get%10);
                if(get<10)leddec(10,10,10,get);
                motor1(get);break;//
            
            case 0x10:
                led_dot(0);get=adc_get(2);
                if(adc_get(2)<=680)get=0;
                else get-=680;  
                if(get>90)get=90;leddec(10,10,get/10,get%10);
                if(get<10)leddec(10,10,10,get);
                motor2(get);break;//
            
            case 0x20:
                led_dot(0);x1=adc_get(1);
                if(adc_get(1)<=660)x1=0;
                else x1-=660;
                x2=adc_get(2);
                if(adc_get(2)<=680)x2=0;
                else x2-=680;
                if(x1>90)x1=90;if(x2>90)x2=90;
                if(x1<10)leddec(10,x1,x2/10,x2%10);
                if(x2<10)leddec(x1/10,x1%10,10,x2);
                if((x1<10)&&(x2<10))leddec(10,x1,10,x2);
                leddec(x1/10,x1%10,x2/10,x2%10);
                motor(90);break;//
            
            case 0x30:
                led_dot(0);            
                x1=adc_get(1);
                if(adc_get(1)<=660)x1=0;
                else x1-=660;
                x2=adc_get(2);
                if(adc_get(2)<=680)x2=0;
                else x2-=680;
                if(x1>90)x1=90;if(x2>90)x2=90;
                if(x1>x2){get=x1-x2;leddec(11,10,get/10,get%10);motor1(get);}
                else if(x1<x2){get=x2-x1;leddec(10,10,get/10,get%10);motor2(get);}
                else if(x1=x2){leddec(10,10,0,0);motor(90);}break;
                       
            
            case 0x40:
                led_dot(0);x1=adc_get(1);
                if(RA3==1)
                {
                    delay_ms(1000);
                    if(RA3==1)
                    {
                        delay_ms(1000);
                        if(RA3==1)
                        {
                            delay_ms(1000);
                            if(RA3==1)
                            {
                                x1y=0;                          
                                led_dec(0,x1y);
                            }
                        }
                    }
                }
                if(x1>700)
                {   
                    x1y++;if(x1y>99)x1y=0;
                    led_dec(0,x1y);
                    delay_ms(200);
                    a:get=adc_get(1);delay_ms(50);if(get>700){led_dec(0,x1y);goto a;}
                }
                led_dec(0,x1y);
                motor1(90);
                break;
            
            
            case 0x50:
                led_dot(0);x2=adc_get(2);
                if(RA3==1)
                {
                    delay_ms(1000);
                    if(RA3==1)
                    {
                        delay_ms(1000);
                        if(RA3==1)
                        {
                            delay_ms(1000);
                            if(RA3==1)
                            {
                                x2y=0;                          
                                led_dec(0,x2y);
                            }
                        }
                    }
                }
                if(x2>700)
                {   
                    x2y++;if(x2y>99)x2y=0;
                    led_dec(0,x2y);
                    delay_ms(200);
                    b:get=adc_get(2);delay_ms(50);if(get>700){led_dec(0,x2y);goto b;}
                }
                led_dec(0,x2y);
                motor2(90);
                break;
                
            case 0x60:
                led_dot(0);x1=adc_get(1);x2=adc_get(2);
                if(RA3==1)
                {
                    delay_ms(1000);
                    if(RA3==1)
                    {
                        delay_ms(1000);
                        if(RA3==1)
                        {
                            delay_ms(1000);
                            if(RA3==1)
                            {
                                x1y=x2y=0;                          
                                led_dec(x1y,x2y);
                            }
                        }
                    }
                }
                if(x1>700)
                {   
                    x1y++;if(x1y>99)x1y=0;
                    led_dec(x1y,x2y);
                    delay_ms(200);
                    a1:get=adc_get(1);delay_ms(50);if(get>700){led_dec(x1y,x2y);goto a1;}
                }
                if(x2>700)
                {   
                    x2y++;if(x2y>99)x2y=0;
                    led_dec(x1y,x2y);
                    delay_ms(200);
                    b1:get=adc_get(2);delay_ms(50);if(get>700){led_dec(x1y,x2y);goto b1;}
                }
                led_dec(x1y,x2y);
                motor(90);
                break;
            
            case 0x70:
                led_dot(0);x1=adc_get(1);x2=adc_get(2);
                if(RA3==1)
                {
                    delay_ms(1000);
                    if(RA3==1)
                    {
                        delay_ms(1000);
                        if(RA3==1)
                        {
                            delay_ms(1000);
                            if(RA3==1)
                            {
                                i=100;
                                leddec(10,10,(i-100)/10,(i-100)%10);
                                motor(i);
                            }
                        }
                    }
                }
                if(x1>700)
                {   
                    i+=10;if(i>=190)i=190;
                    if(i>=100)leddec(10,10,(i-100)/10,(i-100)%10);
                    else if(i<100)leddec(11,10,(100-i)/10,(100-i)%10);
                    delay_ms(200);
                    a2:get=adc_get(1);delay_ms(50);if(get>700)
                    {
                        if(i>=100)leddec(10,10,(i-100)/10,(i-100)%10);
                        else if(i<100)leddec(11,10,(100-i)/10,(100-i)%10);
                        goto a2;
                    }
                }
                if(x2>700)
                {   
                    i-=10;if(i<10)i=10;
                    if(i>=100)leddec(10,10,(i-100)/10,(i-100)%10);
                    else if(i<100)leddec(11,10,(100-i)/10,(100-i)%10);
                    delay_ms(200);
                    b2:get=adc_get(2);delay_ms(50);if(get>700)
                    {
                        if(i>=100)leddec(10,10,(i-100)/10,(i-100)%10);
                        else if(i<100)leddec(11,10,(100-i)/10,(100-i)%10);
                        goto b2;
                    }
                }
                if(i>=100)leddec(10,10,(i-100)/10,(i-100)%10);
                else if(i<100)leddec(11,10,(100-i)/10,(100-i)%10);
                motor(i);
                break;
            
            case 0x80:
                led_dot(0);get=adc_get(0);led_dec(get/100,get%100);motor(90);break;//
            
            case 0x90:
            if(RA3==1){y++;if(y<1)y=0;}
            if(y==1)get=adc_get(0);
            if(get<235)r16=0;
            if((get>235)&&(get<340))r16=100;
            if((get>340)&&(get<455))r16=200;
            if((get>455)&&(get<570))r16=300;
            if((get>570)&&(get<670))r16=400;
            if((get>670)&&(get<760))r16=500;
            x1=r16/100;x2=r16%100;
            leddec(x1/10,x1%10,x2/10,x2%10);led_dot(2);
            break;
            
            
            case 0xc0:get=fn111()/100;x1=get/100;x2=get%100;led_dot(2);
            if(get<10)leddec(0,0,x2/10,x2%10);
            if(get<100)leddec(0,x1%10,x2/10,x2%10);
            leddec(x1/10,x1%10,x2/10,x2%10);
            delay_ms(250);break;//
            
            case 0xe0:get=adc_get(1);led_dec(get/100,get%100);
            case 0xf0:get=adc_get(2);led_dec(get/100,get%100);
        }
    }
}