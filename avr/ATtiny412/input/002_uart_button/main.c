//default frequency is 20MHz with prescaler division factor of 6
#define F_CPU 3333333UL

/*
 * 2024-07-20
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart_command.c"

volatile int flag_uart = 0;

int main(void){

	//initialise uart
	USART0_init();
	//set PIN3 as an output
	PORTA.DIRSET = PIN3_bm;
	//PORTA.DIR |= PIN3_bm; (also works)

	//set PIN1 as an input
	PORTA.DIRCLR = PIN1_bm;
	//turn on internal pullup resistor
	PORTA.PIN1CTRL = PORT_PULLUPEN_bm;

	while(1){
		//check the state of input
		if (~PORTA.IN & PIN1_bm){
			//turn on led
			PORTA.OUT |= PIN3_bm;
		}
		else{
			//turn of led
			PORTA.OUT &= ~PIN3_bm;
		}
	}
}
