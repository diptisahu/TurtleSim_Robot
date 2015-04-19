#define F_CPU 14745600
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

unsigned char data; //to store received data from UDR1

//Function To Initialize UART0
// desired baud rate:9600
// actual baud rate:9600 (error 0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
	 UCSR0B = 0x00; //disable while setting baud rate
	 UCSR0A = 0x00;
	 UCSR0C = 0x06;
	 UBRR0L = 0x5F; //set baud rate lo
	 UBRR0H = 0x00; //set baud rate hi
	 UCSR0B = 0x98;
}


SIGNAL(SIG_USART0_RECV) 		// ISR for receive complete interrupt
{
	data = UDR0; 				//making copy of data from UDR0 in 'data' variable

	if(data == 0x38) //ASCII value of 8
	{
		PORTA=0x06;  //forward
	}

	if(data == 0x32) //ASCII value of 2
	{
		PORTA=0x09; //back
	}

	if(data == 0x34) //ASCII value of 4
	{
		PORTA=0x05;  //left
	}

	if(data == 0x36) //ASCII value of 6
	{
		PORTA=0x0A; //right
	}

	if(data == 0x35) //ASCII value of 5
	{
		PORTA=0x00; //stop
	}

	if(data == 0x37) //ASCII value of 7
	{
		buzzer_on(); //turns buzzer ON
	}

	if(data == 0x39) //ASCII value of 9
	{
		buzzer_off(); //turns buzzer OFF
	}
	
	if(data == 0x30) //ASCII value of 0
	{
		servo_1(60); //rotates to 60 degrees
		_delay_ms(1000); //wait for 1 second
	}
	if(data == 0x31) //ASCII value of 1
	{
		servo_1(90); // rotates to 90 degrees
		_delay_ms(1000); //wait for 1 second
	}
	if(data == 0x33) //ASCII value of 3
	{
		lcd_cursor(1,1);
		lcd_string("    ERROR....   ");	//"ERROR..." flashes on the LCD screen
	}

}