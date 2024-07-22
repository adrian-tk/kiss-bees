//default frequency is 20MHz with prescaler division factor of 6
#define F_CPU 3333333UL

/*
 * 2024-07-22
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

volatile uint8_t flag_pin1_int;

ISR(PORTA_PORT_vect){
	if(PORTA.INTFLAGS & PIN1_bm){
		//set flag to siglal input
		flag_pin1_int = 1;
		//clear interrupt flag
		PORTA.INTFLAGS &= PIN1_bm;
	}
}

int main(void){
	//set PIN3 as an output
	PORTA.DIRSET = PIN3_bm;
	//PORTA.DIR |= PIN3_bm; //(also works)

	//set PIN1 as an input
	PORTA.DIRCLR = PIN1_bm;
	//PORTA.DIR &= ~PIN1_bm; //(also works)
	//turn on internal pullup resistor
	//activate iterrupt
	PORTA.PIN1CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;

	sei();

	while(1){

		if(flag_pin1_int){
			flag_pin1_int = 0;
if(0){
			ATOMIC_BLOCK(ATOMIC_FORCEON){
				//debouncing
				_delay_ms(10);
			}
}
			if(PORTA.IN & PIN1_bm){
				PORTA.OUT |= PIN3_bm;

			}
			else{
				PORTA.OUT &= ~PIN3_bm;
			}
		}
		//flag_pin1_int = 0;
	}
}
