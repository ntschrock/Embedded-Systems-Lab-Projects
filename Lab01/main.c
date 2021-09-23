#include <msp430fr6989.h>
#include <stdint.h>
#define redLED BIT0
#define greenLED BIT7


/**
 * main.c
 */
void main(void)
{
    volatile uint32_t i;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= redLED;
	P1OUT &= ~redLED;

	P9DIR |= greenLED;
	P9OUT &= ~greenLED;



	for(;;)
	{
	    for(i=0; i<30000; i++) {}
	    P9OUT ^= greenLED;
	    P1OUT ^= redLED;

	    for(i=0; i<30000; i++) {}
	    P1OUT ^= redLED;

        for(i=0; i<30000; i++) {}
        P1OUT ^= redLED;

	}
	
}
