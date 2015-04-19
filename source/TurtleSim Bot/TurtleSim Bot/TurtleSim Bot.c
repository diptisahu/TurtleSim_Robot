#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.c"
#include "buzzer.c"
#include "servo.c"
#include "Xbee.c"
#include "motion.c"

//Function to Initialize PORTS
void port_init (void)
{
	motion_pin_config(); //robot motion pins config
	servo1_pin_config(); //Configure PORTB 5 pin for servo motor 1 operation
	buzzer_pin_config(); //configure PORTC 3 pin for buzzer
	lcd_port_config();	//all the LCD pins are configured
}

void init_devices (void)
{
	cli(); //Clears the global interrupts
	port_init(); //Initializes all the ports
	timer1_init(); //Initialize ports of servo motor
	uart0_init(); //Initialize UART1 for serial communication
	sei();   //Enables the global interrupts
}

//Main Function
int main(void)
{
	init_devices(); //Initializes all the devices attached to robot
	lcd_set_4bit();
	lcd_init();
	
	lcd_cursor(1,2);
	lcd_string("TurtleSim Robot"); //"TurtleSim Robot" flashes on the first row of LCD screen
	lcd_cursor(2,3);
	lcd_string("Team No.-394"); //"Team No.-394" flashes on the second row of LCD screen
	while(1);
}