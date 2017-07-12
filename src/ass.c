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

void uart_init() {
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


void uart_putchar(unsigned char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = c;
	loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
}

void uart_write(char *data, unsigned int len)
{
	PORTB = 0x20;
	int i;
	for (i=0; i < len; i++)
	{
		uart_putchar(data[i]);
//		_delay_ms(10);
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

int main()
{

	unsigned int toggle = 0, i;
	unsigned char data[8];

	unsigned char out[] = "x: XXXX y: XXXX z: XXXX t: XXXX\n";

	DDRB = 0x20; // LED is output
	DDRD = 0x00;

	uart_init();
	i2c_init();

	//turn on i2c pullup resistors
	//no need, external resistors present
//	PORTC = 0x30;
	PORTC = 0x00;

	_delay_ms(100);

	i2c_scan();

//	for (i=0; i<0xff; i++)
//		print_stat(i);


	i2c_start();
	i2c_write((0x68<<1) | 0);// 0x68 addr | 0 for write
	i2c_write(MPU_WAKEUP);
	i2c_write(0);
	i2c_stop();


	while (1)
	{

//		PORTB = toggle;
//		for (i=0;i<250;i++)
			_delay_ms(50);
//		if (PIND & 0x08)
		if (toggle)
		{
			toggle = 0;

			i2c_start();
			i2c_write(0x68<<1 | 0);
			i2c_write(MPU_XOUT_H);
//			i2c_write(6);
			i2c_start();
			i2c_write(0x68<<1 | 1);
			data[0] = i2c_read_ack();
			data[1] = i2c_read_ack();
			data[2] = i2c_read_ack();
			data[3] = i2c_read_ack();
			data[4] = i2c_read_ack();
			data[5] = i2c_read_ack();
			data[6] = i2c_read_ack();
			data[7] = i2c_read_nack();
			i2c_stop();

			signed int celcius = ((signed int)(data[6]<<8|data[7])/340) + 36;

			out[2] = (data[0] & 0x80) ? '-' : '+';
			out[3] = inttohex[data[0]>>4 & 0x0f];
			out[4] = inttohex[data[0]>>0 & 0x0f];
			out[5] = inttohex[data[1]>>4 & 0x0f];
			out[6] = inttohex[data[1]>>0 & 0x0f];

			out[10] = (data[2] & 0x80) ? '-' : '+';
			out[11] = inttohex[data[2]>>4 & 0x0f];
			out[12] = inttohex[data[2]>>0 & 0x0f];
			out[13] = inttohex[data[3]>>4 & 0x0f];
			out[14] = inttohex[data[3]>>0 & 0x0f];

			out[18] = (data[4] & 0x80) ? '-' : '+';
			out[19] = inttohex[data[4]>>4 & 0x0f];
			out[20] = inttohex[data[4]>>0 & 0x0f];
			out[21] = inttohex[data[5]>>4 & 0x0f];
			out[22] = inttohex[data[5]>>0 & 0x0f];
			
			
			out[26] = (celcius & 0x8000) ? '-' : '+';
			out[27] = inttohex[celcius>>12 & 0x000f];
			out[28] = inttohex[celcius>>8  & 0x000f];
			out[29] = inttohex[celcius>>4  & 0x000f];
			out[30] = inttohex[celcius>>0  & 0x000f];

			uart_write(out, 32);
		}
		else
		{
			toggle = 0x20;
//			uart_write("-\n", 2);
		}

//		if (sizeof(int) == 8)
//			PORTB == 0;
	}
}
