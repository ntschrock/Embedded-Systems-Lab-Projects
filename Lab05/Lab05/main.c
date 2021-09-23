#include <msp430fr6989.h>
#define redLED BIT0
#define greenLED BIT7
void Initialize_LCD();

//finish this
const unsigned char LCD_Num[10] = {0xFC, 0x60, 0xDB,  0xF3, 0x67, 0xB7, 0xBF, 0xE4, 0xFF, 0xF7};

int main(void)
{
    volatile unsigned int n;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT |= redLED;
    P9OUT &= ~greenLED;

    Initialize_LCD();

    //LCDCMEMCTL = LCDCLRM;     clears all segments

    LCDM19 = LCD_Num[4];
    LCDM15 = LCD_Num[3];
    LCDM8 = LCD_Num[0];

    for(;;)
    {
        for(n=0; n<=50000; n++) {}
        P1OUT ^= redLED;
        P9OUT ^= greenLED;
    }

    return 0;
}

void Initialize_LCD()
{
    PJSEL0 = BIT4 | BIT5;

    LCDCPCTL0 = 0xFFFF;
    LCDCPCTL1 = 0xFC3F;
    LCDCPCTL2 = 0x0FFF;

    CSCTL0_H = CSKEY >> 8;
    CSCTL4 &= ~LFXTOFF;
    do
    {
        CSCTL5 &= ~LFXTOFFG;
        SFRIFG1 &= ~OFIFG;
    }while(SFRIFG1 & OFIFG);
    CSCTL0_H = 0;

    LCDCCTL0 = LCDDIV__1 | LCDPRE__16 | LCD4MUX | LCDLP;

    LCDCVCTL = VLCD_1 | VLCDREF_0 | LCDCPEN;

    LCDCCPCTL = LCDCPCLKSYNC; // Clock synchronization enabled

    LCDCMEMCTL = LCDCLRM; // Clear LCD memory

    LCDCCTL0 |= LCDON;
    return;
}
