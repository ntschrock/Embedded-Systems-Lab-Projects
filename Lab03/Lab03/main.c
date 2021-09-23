#include <msp430fr6989.h>
#define redLED BIT0 // Red LED at P1.0
#define greenLED BIT7

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


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= redLED;
    P9DIR |= greenLED;

    P1OUT &= ~redLED;
    P9OUT |= greenLED;

    config_ACLK_to_32KHz_crystal();

    //TA0CCR0 = 16000;

    TA0CTL = TASSEL_1 | MC_2 | TACLR | ID_0;

    TA0CTL &= ~TAIFG;

    for(;;)
    {
        while((TA0CTL & TAIFG) == 0){}
        P1OUT ^= redLED;     //toggle the red LED
        P9OUT ^= greenLED;
        TA0CTL &= ~TAIFG;   //clear the flag
    }
}


