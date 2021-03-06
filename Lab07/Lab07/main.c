#include <msp430.h> 
#define redLED BIT0
#define BUT1 BIT1

void config_ACLK_to_32KHz_crystal();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= redLED;
	P1OUT &= ~redLED;

	P1DIR &= ~BUT1;
	P1REN |= BUT1;
	P1OUT |= BUT1;
	P1IE |= BUT1;
	P1IES |= BUT1;
	P1IFG &= ~BUT1;

	TA0CCR0 = 2000;
	TA0CCTL0 &= ~CCIFG;

	config_ACLK_to_32KHz_crystal();

	_enable_interrupts();
	
	return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR()
{
    while(P1IFG & BUT1 == 0){}

    P1OUT ^= redLED;
    TA0CCTL0 &= ~CCIE;
    P1IE |= BUT1;
    P1IFG &= ~BUT1;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR()
{
    if((P1IFG & BUT1) != 0)
    {
        P1IE &= ~BUT1;
        TA0CCTL0 &= ~CCIFG;
        TA0CCTL0 |= CCIE;

        TA0CTL = TASSEL_1 | ID_1 | MC_1 | TACLR;
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
