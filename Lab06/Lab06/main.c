#include <msp430fr6989.h>
#define redLED BIT0 // Red at P1.0
#define greenLED BIT7 // Green at P9.7

void config_ACLK_to_32KHz_crystal();
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &=  ~LOCKLPM5;

    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT &=  ~redLED;
    P9OUT &=  ~greenLED;

    config_ACLK_to_32KHz_crystal();

    // Configure Channel 0
    TA0CCR0 = 3277-1;
    TA0CCTL0 |= CCIE;
    TA0CCTL0 &=  ~CCIFG;

    // Configure Channel 1
    TA0CCR1 = 16384;
    TA0CCTL1 |= CCIE;
    TA0CCTL1 &=  ~CCIFG;

    // Configure timer
    TA0CTL = TASSEL_1 | ID_0 | MC_2 | TACLR;

    // Engage a low-power mode
    _low_power_mode_3();
    return;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR()
{
    P1OUT ^= redLED;
    TA0CCR0 += 3277;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void T0A1_ISR()
{
    P9OUT ^= greenLED;
    TA0CCR1 += 16384;
    TA0CCTL1 &=  ~CCIFG;
}

void config_ACLK_to_32KHz_crystal()
{
    PJSEL1 &=  ~BIT4;
    PJSEL0 |= BIT4;

    CSCTL0 = CSKEY;
    do
    {
      CSCTL5 &= ~LFXTOFFG;
      SFRIFG1 &= ~OFIFG;

    }while((CSCTL5 & LFXTOFFG) != 0);

    CSCTL0_H = 0;

return;
}

/*
#include <msp430fr6989.h>
#define redLED BIT0
#define greenLED BIT7

void config_ACLK_to_32KHz_crystal();
volatile unsigned int status = 0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &=  ~LOCKLPM5;

    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT &=  ~redLED;
    P9OUT &=  ~greenLED;

    config_ACLK_to_32KHz_crystal();

    //configure channel 0
    TA0CCR0 = 819 -1;
    TA0CCTL0 |= CCIE;
    TA0CCTL0 &= ~CCIFG;

    // Configure Channel 1
    TA0CCR1 = 4096 - 1;
    TA0CCTL1 |= CCIE;
    TA0CCTL1 &= ~CCIFG;

    TA0CCR2 = 32768 - 1;
    TA0CCTL2 |= CCIE;
    TA0CCTL2 &= ~CCIFG;

    // Configure timer
    TA0CTL = TASSEL_1 | ID_2 | MC_2 | TACLR;
    TA0CTL &= ~TAIFG;


    // Engage a low-power mode
    _low_power_mode_3();
    return;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR()
{
    if (status == 0)
    {
        P1OUT ^= redLED;
    }
    TA0CCR0 += 819;

}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void T0A1_ISR()
{
    if((TA0CCTL1 & CCIFG) != 0)
    {
        if (status ==0)
        {
            P9OUT ^= greenLED;
        }

        TA0CCR1 += 4096;
        TA0CCTL1 &= ~TAIFG;
    }

    if((TA0CCTL2 & CCIFG) != 0)
    {
        if (status == 0)
        {
            P1OUT &= ~redLED;
            P9OUT &= ~greenLED;
            status = 1;
        }

        else if (status == 1)
        {
            status = 0;
        }

        TA0CCR2 += 32768;
        TA0CCTL2 &= ~CCIFG;
    }

}

void config_ACLK_to_32KHz_crystal()
{
    PJSEL1 &=  ~BIT4;
    PJSEL0 |= BIT4;

    CSCTL0 = CSKEY;
    do
    {
      CSCTL5 &= ~LFXTOFFG;
      SFRIFG1 &= ~OFIFG;

    }while((CSCTL5 & LFXTOFFG) != 0);

    CSCTL0_H = 0;
    return;
}
*/
/*
#include <msp430fr6989.h>
#define PWM_PIN BIT0

void config_ACLK_to_32KHz_crystal();

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= PWM_PIN;
    P1SEL1 &= ~PWM_PIN;
    P1SEL0 |= PWM_PIN;

    config_ACLK_to_32KHz_crystal();

    TA0CCR0 = 33-1;


    TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    TA0CCTL1 |= OUTMOD_7;
    TA0CCR1 = 2;
    //TA0CCR1 = 20;

    for(;;) {}

    return;
}

void config_ACLK_to_32KHz_crystal()
{
    PJSEL1 &= ~BIT4;
    PJSEL0 |= BIT4;


    CSCTL0 = CSKEY;

    do
    {
        CSCTL5 &= ~LFXTOFFG;
        SFRIFG1 &= ~OFIFG;
    }while((CSCTL5 & LFXTOFFG) != 0);

    CSCTL0_H = 0;
    return;
}
*/
/*
#include <msp430fr6989.h>
#define PWM_PIN BIT0

void config_ACLK_to_32KHz_crystal();
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= PWM_PIN;
    P1SEL1 &= ~PWM_PIN;
    P1SEL0 |= PWM_PIN;

    config_ACLK_to_32KHz_crystal();

    // Configure Channel 0
    TA0CCR0 = 33 - 1;


    // Configure timer
    TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    TA0CCTL1 |= OUTMOD_7;
    TA0CCR1 = 0;

    TA1CCR0 = 32768 - 1;
    TA1CCTL0 |= CCIE;
    TA1CCTL0 &= ~CCIFG;

    TA1CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;
    TA1CTL &= ~TAIFG;

    _low_power_mode_3();
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void T1A0_ISR()
{
    if (TA0CCR1 >= 30)
        TA0CCR1 = 0;
    else
        TA0CCR1 += 5;

    TA1CCR0 += 32768;
}

void config_ACLK_to_32KHz_crystal()
{
    PJSEL1 &= ~BIT4;
    PJSEL0 |= BIT4;

    CSCTL0 = CSKEY;

    do
    {
        CSCTL5 &= ~LFXTOFFG;
        SFRIFG1 &= ~OFIFG;
    }   while((CSCTL5 & LFXTOFFG) != 0);

    CSCTL0_H = 0;
    return;
}
*/
