#include <msp430.h> 
#define redLED BIT0
#define greenLED BIT7
#define BUT1 BIT1
#define BUT2 BIT2


void main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    //direct pin as output
    P1DIR |= redLED;
    P9DIR |= greenLED;

    //turn the LEDs off
    P1OUT &= ~redLED;
    P9OUT &= ~greenLED;

    //configure the buttons
    P1DIR &= ~(BUT1 | BUT2);
    P1REN |= (BUT1 | BUT2);
    P1OUT |= (BUT1 | BUT2);

    for(;;)
    {
           if ((P1IN & BUT1) == 0)
           {
           //H
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<40000; i++) {}

           //E
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<40000; i++) {}

           //L
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<40000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<40000; i++) {}    //space

           //L
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<40000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<40000; i++) {}    //space

           //O
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<40000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<40000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<20000; i++) {}
               P1OUT ^= redLED;     //TOGGLE ON
           for(i=0; i<40000; i++) {}
               P1OUT ^= redLED;     //TOGGLE OFF
           for(i=0; i<120000; i++) {}

           }
           else P1OUT &= ~redLED;
    }

}
