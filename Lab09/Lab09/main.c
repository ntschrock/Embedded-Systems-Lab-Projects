/*
#include <msp430fr6989.h>
#include <stdio.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer

void Initialize_UART(void);
void Initialize_I2C(void);
void uart_write_uint16(unsigned int n);
void uart_write_char(unsigned char ch);
void uart_write_string(char * str);
unsigned char uart_read_char(void);
int i2c_read_word(unsigned char, unsigned char, unsigned int*);
int i2c_write_word(unsigned char, unsigned char, unsigned int);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	unsigned int data;
	unsigned int i = 0, j = 1;
	unsigned int deviceID;
	unsigned volatile int value = 0;

	Initialize_UART();
	Initialize_I2C();
	i2c_read_word(0x44, 0x7E, &data);
	i2c_read_word(0x44, 0x7F, &deviceID);
	char datastring[]= "Manufacturer ID: ";
	char IDstring[]= "Device ID: ";
	char Iterationstring[]= "Iteration: ";

	for(;;)
	{
	    for(i = 0; i < 40000; i++){}
	    uart_write_string(datastring);
        uart_write_uint16(data);
        uart_write_char('\n');
        uart_write_char('\r');

        uart_write_string(IDstring);
        uart_write_uint16(deviceID);
        uart_write_char('\n');
        uart_write_char('\r');

        uart_write_string(Iterationstring);
        uart_write_uint16(j);
        j++;
        uart_write_char('\n');
        uart_write_char('\r');

        for(i = 0; i < 40000; i++){}
        uart_write_char('\n');
        uart_write_char('\r');
	}

}

void uart_write_uint16(unsigned int n)
{
    int j = 0;
    int k = 0;
    char *array[5] = {'0', '0', '0', '0', '0'};

    if(n == 0)
    {
        uart_write_char('0');
    }

    while(n != 0)
    {
        char digit = ((n % 10) + '0');
        array[j] = digit;
        n = n / 10;
        j++;
    }

    for(k = (j - 1); k >= 0; k--)
    {
        uart_write_char(array[k]);
    }
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

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_I2C(void)
{
    UCB1CTLW0 |= UCSWRST;

    P4SEL1 |= (BIT1|BIT0);
    P4SEL0 &= ~(BIT1|BIT0);

    UCB1CTLW0 = UCMODE_3|UCMST|UCSSEL_3;
    UCB1BRW = 8;
    UCB1CTLW0 &= ~UCSWRST;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
        else temp = RXBUFFER;
    return temp;
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

int i2c_read_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int * data)
{
    unsigned char byte1, byte2;

    byte1 = 111;
    byte2 = 111;

    UCB1I2CSA = i2c_address;
    UCB1IFG &= ~UCTXIFG0;
    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    if((UCB1IFG & UCNACKIFG) != 0)
    {
        return -1;
    }

    UCB1CTLW0 &= ~UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte1 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte2 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTP) != 0){}
    *data = ((byte1 << 8) | (byte2 & 0xFF));

    return 0;
}

int i2c_write_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int data)
{
    unsigned char byte1, byte2;

    byte1 = (data >> 8) & 0xFF;
    byte2 = data & 0xFF;

    UCB1I2CSA = i2c_address;

    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1TXBUF = byte1;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = byte2;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1CTLW0 & UCTXSTP) != 0){}

    return 0;
}
*/
/*
#include <msp430fr6989.h>
#include <stdio.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer


void Initialize_UART(void);
void Initialize_I2C(void);
void uart_write_uint16(unsigned int n);
void uart_write_char(unsigned char ch);
int i2c_read_word(unsigned char, unsigned char, unsigned int*);
int i2c_write_word(unsigned char, unsigned char, unsigned int);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    unsigned int i = 0;
    unsigned int result;

    Initialize_UART();
    Initialize_I2C();

    i2c_write_word(0x44, 0x01, 0x7604);

//    i2c_write_word(0x44, 0x01, 0x7604);
  //  i2c_read_word(0x44, 0x00, &result);
    //uart_write_uint16(result);

    for(;;)
    {
        for(i = 0; i < 50000; i++){}
        i2c_read_word(0x44, 0x00, &result);
        uart_write_uint16(result * 1.28);
        uart_write_char('\n');
        uart_write_char('\r');
    }

}
void uart_write_uint16(unsigned int n)
{
    int j = 0;
    int k = 0;
    char *array[5] = {'0', '0', '0', '0', '0'};

    if(n == 0)
    {
        uart_write_char('0');
    }

    while(n != 0)
    {
        char digit = ((n % 10) + '0');
        array[j] = digit;
        n = n / 10;
        j++;
    }

    for(k = (j - 1); k >= 0; k--)
    {
        uart_write_char(array[k]);
    }
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

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_I2C(void)
{
    UCB1CTLW0 |= UCSWRST;

    P4SEL1 |= (BIT1|BIT0);
    P4SEL0 &= ~(BIT1|BIT0);

    UCB1CTLW0 = UCMODE_3|UCMST|UCSSEL_3;
    UCB1BRW = 8;
    UCB1CTLW0 &= ~UCSWRST;
}

int i2c_read_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int * data)
{
    unsigned char byte1, byte2;

    byte1 = 111;
    byte2 = 111;

    UCB1I2CSA = i2c_address;
    UCB1IFG &= ~UCTXIFG0;
    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    if((UCB1IFG & UCNACKIFG) != 0)
    {
        return -1;
    }

    UCB1CTLW0 &= ~UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte1 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte2 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTP) != 0){}
    *data = ((byte1 << 8) | (byte2 & 0xFF));

    return 0;
}

int i2c_write_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int data)
{
    unsigned char byte1, byte2;

    byte1 = (data >> 8) & 0xFF;
    byte2 = data & 0xFF;

    UCB1I2CSA = i2c_address;

    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1TXBUF = byte1;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = byte2;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1CTLW0 & UCTXSTP) != 0){}

    return 0;
}
*/

#include <msp430fr6989.h>
#include <stdio.h>
#define redLED BIT0
#define greenLED BIT7
#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer

void Initialize_UART(void);
void Initialize_I2C(void);
void uart_write_uint16(unsigned int n);
void uart_write_char(unsigned char ch);
void uart_write_string(char * str);
unsigned char uart_read_char(void);
int i2c_read_word(unsigned char, unsigned char, unsigned int*);
int i2c_write_word(unsigned char, unsigned char, unsigned int);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    unsigned int data;
    unsigned int i = 0, j = 1;
    unsigned int deviceID;
    unsigned int result;

    Initialize_UART();
    Initialize_I2C();

    i2c_write_word(0x44, 0x01, 0x7604);

    for(;;)
    {
        for(i = 0; i < 50000; i++){}
        i2c_read_word(0x44, 0x00, &result);
        result = result * 1.28;
        uart_write_uint16(result);
        uart_write_char('\n');
        uart_write_char('\r');
        for(i = 0; i < 50000; i++){}
    }
    return 0;
}

void uart_write_uint16(unsigned int n)
{
    int j = 0;
    int k = 0;
    char *array[5] = {'0', '0', '0', '0', '0'};

    if(n == 0)
    {
        uart_write_char('0');
    }

    while(n != 0)
    {
        char digit = ((n % 10) + '0');
        array[j] = digit;
        n = n / 10;
        j++;
    }

    for(k = (j - 1); k >= 0; k--)
    {
        uart_write_char(array[k]);
    }
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

void uart_write_char(unsigned char ch)
{
    while ((FLAGS & TXFLAG) == 0){}
    TXBUFFER = ch;
}

void Initialize_I2C(void)
{
    UCB1CTLW0 |= UCSWRST;

    P4SEL1 |= (BIT1|BIT0);
    P4SEL0 &= ~(BIT1|BIT0);

    UCB1CTLW0 = UCMODE_3|UCMST|UCSSEL_3;
    UCB1BRW = 8;
    UCB1CTLW0 &= ~UCSWRST;
}

unsigned char uart_read_char(void)
{
    unsigned char temp;
    if((FLAGS & RXFLAG) == 0)
        return 0;
        else temp = RXBUFFER;
    return temp;
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

int i2c_read_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int * data)
{
    unsigned char byte1, byte2;

    byte1 = 111;
    byte2 = 111;

    UCB1I2CSA = i2c_address;
    UCB1IFG &= ~UCTXIFG0;
    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    if((UCB1IFG & UCNACKIFG) != 0)
    {
        return -1;
    }

    UCB1CTLW0 &= ~UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte1 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1IFG & UCRXIFG0) == 0){}
    byte2 = UCB1RXBUF;

    while((UCB1CTLW0 & UCTXSTP) != 0){}
    *data = ((byte1 << 8) | (byte2 & 0xFF));

    return 0;
}

int i2c_write_word(unsigned char i2c_address, unsigned char i2c_reg, unsigned int data)
{
    unsigned char byte1, byte2;

    byte1 = (data >> 8) & 0xFF;
    byte2 = data & 0xFF;

    UCB1I2CSA = i2c_address;

    UCB1CTLW0 |= UCTR;
    UCB1CTLW0 |= UCTXSTT;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = i2c_reg;

    while((UCB1CTLW0 & UCTXSTT) != 0){}
    UCB1TXBUF = byte1;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1TXBUF = byte2;

    while((UCB1IFG & UCTXIFG0) == 0){}
    UCB1CTLW0 |= UCTXSTP;

    while((UCB1CTLW0 & UCTXSTP) != 0){}

    return 0;
}
