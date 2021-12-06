#include <xc.h>
void pwm0(unsigned int n);
void pwm0off(void);
void pwm1(void);
void pwm1off(void);
void pwmalloff(void);


void pwm0(unsigned int n)
{
    TRISC2=0;
    T2CON=0x07;
    CCP1CON=0x0c;
    CCPR1L=83*n/1000;
    PR2=83-1;    //T=(PR2+1)*4*¹w¤ÀÀW­È/16M  ex:3kHZ  1/3k=PR2+1*4*16/16M=>PR2+1=83=>PR2=82
}

void pwm1(void)
{
    TRISC1=0;
    T2CON=0x07;
    CCP2CON=0x0f;
    CCPR2L=42;
    PR2=83-1;
}

void pwm0off(void)
{
    TRISC2=1;
    LATC2=0;
    CCP1CON=0;
}
void pwm1off(void)
{
    TRISC1=1;
    LATC1=0;
    CCP2CON=0;
}
void pwmalloff(void)
{
    T2CON=0x00;
    TRISC2=1;    
    TRISC1=1;
    LATC2=0;
    LATC1=0;
    CCP1CON=0;
    CCP2CON=0;
}