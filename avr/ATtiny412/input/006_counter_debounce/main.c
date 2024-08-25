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
volatile uint8_t pin1_still;
volatile uint8_t pin1_wait;

ISR(PORTA_PORT_vect)
{
	if (PORTA.INTFLAGS & PIN1_bm)
	{
		//printf("pin1_change flag set to 1\n\r");
		printf(".");
		// set flag to signal some input
		pin1_change = 1;
		// clear interrupt flag
		PORTA.INTFLAGS = PIN1_bm;
	}
}

ISR(TCA0_OVF_vect){
	//printf("pin1_still flag set to 1\n\r");
	// set flag to signal end of waiting
	pin1_still = 1;
	// clear interrupt flag
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
int main(void)
{

	// initialise uart
	USART0_init();
	printf("uart initalised\n\r");

	// set PIN3 as an output
	PORTA.DIRSET = PIN3_bm;
	// PORTA.DIR |= PIN3_bm; (also works)

	// set PIN1 as an input
	PORTA.DIRCLR = PIN1_bm;
	// PORTA.DIR &= ~PIN1_bm; //(also works)

	//timer
	//main frequency (3333333/s) / div(256) ~13021/s 
	//so we need 13020 (incl. zero) to get 1s
	//for 10 ms we need 130
	//
	// Set compare value
	TCA0.SINGLE.PER = 130; 
	// set timer division
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV256_gc;
	// Set normal mode
	TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_NORMAL_gc;
	// enable overflow interrupt
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	// turn on internal pullup resistor
	// activate interrupt on PIN1
	PORTA.PIN1CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;

	// turn on interrupt
	sei();

	pin1_wait = 0;

	while (1){
		USART0_flag();

	}
}
