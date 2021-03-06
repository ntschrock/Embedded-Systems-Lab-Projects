/*#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF


void Initialize_UART();
void uart_write_char(unsigned char);
unsigned char uart_read_char();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	
    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT &= ~redLED;
    P9OUT &= ~greenLED;

	volatile unsigned int i;
	char ch, gflag;

	Initialize_UART();
	for(;;)
	{
	    //P1OUT ^= redLED;
	    for(ch = '0'; ch <= '9'; ch++)
	    {
	        gflag = uart_read_char();
	        if(gflag == '1') P9OUT |= greenLED;
	        if(gflag == '2') P9OUT &= ~greenLED;
	        uart_write_char(ch);
	        uart_write_char('\n');
	        uart_write_char('\r');
	        for(i = 0; i < 5000; i++){}
	    }
	}
	return 0;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
    temp = RXBUFFER;
    return temp;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRS1|UCBRF3|UCBRF2|UCBRF0|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}
*/

/*
#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF

void Initialize_UART();
void uart_write_char(unsigned char);
unsigned char uart_read_char();
void uart_write_unit16(unsigned int);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    volatile unsigned int i = 0, j;

    Initialize_UART();
    for(;;)
    {
        if(i == 0)
        {
            uart_write_char('0');
            uart_write_char('\n');
            uart_write_char('\r');
        }
        else
        {
            uart_write_unit16(i);
            uart_write_char('\n');
            uart_write_char('\r');
        }
        i++;

        for(j = 0; j < 2000; j++){}
    }
    return 0;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
        else temp = RXBUFFER;
    return temp;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void uart_write_unit16(unsigned int n)
{
    int j;
    if(n == 0)return;
    uart_write_unit16(n/10);
    j = n % 10;
    uart_write_char('0' + j);
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRS1|UCBRF3|UCBRF2|UCBRF0|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}
*/
/*
#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF

void Initialize_UART();
void uart_write_char(unsigned char);
unsigned char uart_read_char();
void uart_write_string(char *);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT &= ~redLED;
    P9OUT &= ~greenLED;

    char mystring[]= "UART Transmission begins...\nHi my name is Noah";

    Initialize_UART();
    uart_write_string(mystring);

    return 0;
}
void uart_write_string(char * str)
{
    char ch = *str;
    while(ch != '\0')
    {
        uart_write_char(ch);
        ch = *(++str);
    }
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
        else temp = RXBUFFER;
    return temp;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRS1|UCBRF3|UCBRF2|UCBRF0|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}
*/

#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF

void uart_write_string(char * str);
void uart_write_unit16(unsigned int);
void uart_write_char(unsigned char);
void Initialize_UART(void);
void Initialize_UART_2(void);
void config_ACLK_to_32KHz_crystal();
void uart_write_char(unsigned char);
unsigned char uart_read_char(void);
void uart_write_string(char *);
void uart_write_unit16(unsigned int);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    volatile unsigned int i = 0, j;

    P1DIR |= redLED;
    P9DIR |= greenLED;
    P1OUT &= ~redLED;
    P9OUT &= ~greenLED;

    config_ACLK_to_32KHz_crystal();
    Initialize_UART_2();

    for(;;)
    {
        if(i == 0)
        {
            uart_write_char('0');
            uart_write_char('\n');
            uart_write_char('\r');
        }
        else
        {
            uart_write_unit16(i);
            uart_write_char('\n');
            uart_write_char('\r');
        }
        i++;

        for(j = 0; j < 5000; j++){}
    }
}

void uart_write_unit16(unsigned int n)
{
    int j;
    if(n == 0)return;
    uart_write_unit16(n/10);
    j = n % 10;
    uart_write_char('0' + j);
}

void uart_write_string(char * str)
{
    char ch = *str;
    while(ch != '\0')
    {
        uart_write_char(ch);
        ch = *(++str);
    }
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
    temp = RXBUFFER;
    return temp;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRS1|UCBRF3|UCBRF2|UCBRF0|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}

void Initialize_UART_2(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_1;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS7|UCBRS6|UCBRS5|UCBRS3|UCBRS2|UCBRS1;
    UCA1CTLW0 &= ~UCSWRST;
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




