#include <msp430.h> 
#define redLED BIT0
#define greenLED BIT7
#define BUT1 BIT1
#define BUT2 BIT2

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
    P9OUT &= ~greenLED;

    //config_ACLK_to_32KHz_crystal();

    //Configure Channel 0
    //TA0CCR0 = 32767;
    //TA0CCTL0 |= CCIE;
    //TA0CCTL0 &= ~CCIFG;

    //configure buttons with interrupts
    P1DIR &= ~(BUT1 | BUT2);
    P1REN |= (BUT1 | BUT2);
    P1OUT |= (BUT1 | BUT2);
    P1IE |= (BUT1 | BUT2);
    P1IES |= (BUT1 | BUT2);
    P1IFG &= ~(BUT1 | BUT2);

    //TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;

    _enable_interrupts();

    for(;;){}
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR()
{
    if((P1IFG & BUT1) == BUT1)
    {
        P1OUT ^= redLED;
        P1IFG &= ~BUT1;
    }
    if((P1IFG & BUT2) == BUT2)
    {
        P9OUT ^= greenLED;
        P1IFG &= ~BUT2;
    }
}
