//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include "uart_interrupt.c"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
	
	USART0_init();

	//turn on interrupt
	sei();

	while (1){
		;
	}
}


