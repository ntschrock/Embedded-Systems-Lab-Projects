/*#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF

void Initialize_ADC(void);
void Initialize_UART(void);
void uart_write_uint16(unsigned int);
void uart_write_char(unsigned char);
void uart_newline(void);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= redLED;
    P1OUT &= ~redLED;

    Initialize_UART();
    Initialize_ADC();

    for(;;)
    {
        ADC12CTL0|=ADC12SC;
        while ((ADC12CTL1 &ADC12BUSY)!=0);
        uart_write_uint16(ADC12MEM0);
        uart_write_char('\n');
        uart_write_char('\r');
        P1OUT^=redLED;
    }
}

void Initialize_ADC(void)
{
    P9SEL1 |= BIT2;
    P9SEL0 |= BIT2;

    ADC12CTL0 |= ADC12ON;
    ADC12CTL0 &= ~ADC12ENC;
    ADC12CTL0|=ADC12ON|ADC12SHT1_10;
    ADC12CTL1= ADC12SHS_0|ADC12SHP|ADC12DIV_7|ADC12SSEL_0;
    ADC12CTL2|= ADC12ENC;
    ADC12MCTL0|= ADC12INCH_10|ADC12VRSEL_0;
    ADC12CTL0 |= ADC12ENC;

    return;
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRF3|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}

void uart_write_uint16(unsigned int n)
{
    int x;
    if(n >= 10000)
    {
        x = (n/10000) % 10;
        uart_write_char('0'+ x);
    }

    if(n >= 1000)
    {
        x = (n/1000) % 10;
        uart_write_char('0' + x);
    }

    if(n >= 100)
    {
        x = (n/100) % 10;
        uart_write_char('0' + x);
    }

    if(n >= 10)
    {
        x = (n/10) % 10;
        uart_write_char('0' + x);
    }

    x = (n % 10);
    uart_write_char('0' + x);
    return;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG)==0) {}
    TXBUFFER = ch;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if( (FLAGS & RXFLAG) == 0)
        return 0;
    else
        temp = RXBUFFER;
    return temp;
}*/


#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG
#define RXFLAG UCRXIFG
#define TXFLAG UCTXIFG
#define TXBUFFER UCA1TXBUF
#define RXBUFFER UCA1RXBUF

void Initialize_ADC(void);
void Initialize_UART(void);
void uart_write_uint16(unsigned int);
void uart_write_char(unsigned char);
void uart_newline(void);

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= redLED;
    P1OUT &= ~redLED;

    Initialize_UART();
    Initialize_ADC();

    for(;;)
    {
        ADC12CTL0|=ADC12SC;
        while ((ADC12CTL1 &ADC12BUSY)!=0);
        uart_write_uint16(ADC12MEM0);
        uart_write_char(' ');
        uart_write_uint16(ADC12MEM1);
        uart_write_char('\n');
        uart_write_char('\r');
        P1OUT^=redLED;
    }
}

void Initialize_ADC(void)
{
    P9SEL1 |= BIT2;
    P9SEL0 |= BIT2;

    P8SEL1 |= BIT7;
    P8SEL0 |= BIT7;

    ADC12CTL0 |= ADC12ON;
    ADC12CTL0 &= ~ADC12ENC;

    ADC12CTL0 |= ADC12SHT0_3 | ADC12MSC;

    ADC12CTL1 = ADC12SHS_0 | ADC12SHP | ADC12DIV_0 | ADC12SSEL_0;
    ADC12CTL1 |= ADC12CONSEQ_1;

    ADC12CTL2 |= ADC12RES_2;
    ADC12CTL2 &= ~ADC12DF;

    ADC12CTL3 |= ADC12CSTARTADD_0;

    ADC12MCTL0 |= ADC12INCH_10 | ADC12VRSEL_0;

    ADC12MCTL1 |= ADC12INCH_4 | ADC12VRSEL_0 | ADC12EOS;

    ADC12CTL0 |= ADC12ENC;
    return;
}

void Initialize_UART(void)
{
    P3SEL1 &= ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);

    UCA1CTLW0 |= UCSSEL_2;

    UCA1BRW = 6;
    UCA1MCTLW = UCBRS5|UCBRF3|UCOS16;
    UCA1CTLW0 &= ~UCSWRST;
}

void uart_write_uint16(unsigned int n)
{
    int x;
    if(n >= 10000)
    {
        x = (n/10000) % 10;
        uart_write_char('0'+ x);
    }

    if(n >= 1000)
    {
        x = (n/1000) % 10;
        uart_write_char('0' + x);
    }

    if(n >= 100)
    {
        x = (n/100) % 10;
        uart_write_char('0' + x);
    }

    if(n >= 10)
    {
        x = (n/10) % 10;
        uart_write_char('0' + x);
    }

    x = (n % 10);
    uart_write_char('0' + x);
    return;
}

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG)==0) {}
    TXBUFFER = ch;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if( (FLAGS & RXFLAG) == 0)
        return 0;
    else
        temp = RXBUFFER;
    return temp;
}
