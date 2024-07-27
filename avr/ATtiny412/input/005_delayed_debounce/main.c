// default frequency is 20MHz with prescaler division factor of 6
#define F_CPU 3333333UL

/*
 * 2024-07-23
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <util/atomic.h>
#include "uart/uart.c"

volatile uint8_t pin1_change;

ISR(PORTA_PORT_vect)
{
	if (PORTA.INTFLAGS & PIN1_bm)
	{
		// set flag to signal some input
		pin1_change = 1;
		// clear interrupt flag
		PORTA.INTFLAGS &= PIN1_bm;
	}
}
int main(void)
{

	// initialise uart
	USART0_init();

	// set PIN3 as an output
	PORTA.DIRSET = PIN3_bm;
	// PORTA.DIR |= PIN3_bm; (also works)

	// set PIN1 as an input
	PORTA.DIRCLR = PIN1_bm;
	// PORTA.DIR &= ~PIN1_bm; //(also works)

	// turn on internal pullup resistor
	// activate interrupt on PIN1
	PORTA.PIN1CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;

	// turn on interrupt
	sei();

	while (1)
	{

		// USART0_flag();

		if (pin1_change)
		{
			ATOMIC_BLOCK(ATOMIC_FORCEON){
				_delay_ms(20);
			}
			
			// check the state of input
			if (~PORTA.IN & PIN1_bm)
			{
				// turn on led
				PORTA.OUT |= PIN3_bm;
				printf("on, ");
			}
			else
			{
				// turn of led
				PORTA.OUT &= ~PIN3_bm;
				printf("off, ");
			}
			pin1_change = 0;
		}
	}
}
