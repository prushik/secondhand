#define __AVR_ATmega328P__ 1
#define F_CPU 16000000UL

#define BAUD 9600

#define MPU_ADDR 0x68
#define MPU_WAKEUP 0x6b
#define MPU_XOUT_H 0x3b
#define MPU_TEMP_H 0x41

#include <avr/io.h>
#include <util/delay.h>

#include <util/setbaud.h>

#include "tokenizer.h"

void uart_init()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}


void uart_putchar(unsigned char c)
{
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = c;
	loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
}

char uart_getchar()
{
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}


void uart_write(const unsigned char *data, unsigned int len)
{
	PORTB = 0x20;
	int i;
	for (i=0; i < len; i++)
	{
		uart_putchar(data[i]);
	}
	PORTB = 0x00;
}

void i2c_init()
{
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = 0x11;

	//enable TWI
	TWCR = (1<<TWEN);
}

void i2c_start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void i2c_stop()
{
	while (TWCR & (1<<TWIE)) ;
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
//	while (TWCR & (1<<TWSTO)) ;
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	_delay_ms(12);
}

uint8_t i2c_read_ack()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

//read byte with NACK
uint8_t i2c_read_nack()
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}

uint8_t i2c_get_status()
{
	return TWSR & 0xF8;
}

uint8_t i2c_get_status_()
{
	return TWSR & 0xf8;
}

static unsigned char inttohex[16] = "0123456789abcdef";

void print_stat(unsigned char c)
{
	unsigned char out[3];
	out[0] = inttohex[c >> 4];
	out[1] = inttohex[c & 0x0f];
	out[2] = '\n';

	uart_write(out, 3);
}

void i2c_scan()
{
	char i;
	for (i = 0; i < 0x7f; i++)
	{
		i2c_start();
		i2c_write((i << 1) | 0);
//		_delay_ms(12);
		char ack = i2c_get_status();
		i2c_stop();

		// 0x18 means ack
		// 0x20 means nack
		if (ack == 0x18)
		{
			uart_write("Found i2c device at: ", 21);
			uart_putchar(inttohex[i>>4]);
			uart_putchar(inttohex[i&0x0f]);
			uart_putchar('\n');
		}
	}
}

// This is our test assembly code
const static char text[] = 
"rjump main\n"
"main:\n"
"ldi	r16,0xff\n"
"out	ddrb,r16\n"
"ldi	r16,0x00\n"
"loop:\n"
"com	r16\n"
"out	portb,r16\n"
"ldi	r17,100\n"
"outer:\n"
"ldi	zh,high(40000)\n"
"ldi	zl,low(40000)\n"
"inner:\n"
"sbiw	zl,1\n"
"brne	inner\n"
"dec	r17\n"
"brne	outer\n"
"rjmp	loop\n";


int main()
{
	unsigned int toggle = 0, i;
	unsigned char data[8];

	unsigned char out[] = "\n                              \n";

	DDRB = 0x20; // LED is output
	DDRD = 0x00;

	uart_init();
	i2c_init();

	//turn on i2c pullup resistors
	//no need, external resistors present
//	PORTC = 0x30;
	PORTC = 0x00;

	_delay_ms(100);

//	i2c_scan();

//	for (i=0; i<0xff; i++)
//		print_stat(i);

	struct token toks[100];

	int tlen = count_tokens(text,100);

//	toks = (struct token *)malloc(sizeof(struct token)*(tlen+1));

	tokenize(text, 100, toks);

	while (1)
	{

		PORTB = toggle;
//		for (i=0;i<250;i++)
			_delay_ms(50);
//		if (PIND & 0x08)
		if (toggle)
		{
			toggle = 0;

			uart_write(toks[1].text, toks[1].text_len);

			uart_write(out, 32);
		}
		else
		{
			toggle = 0x20;
		}

	}
}
