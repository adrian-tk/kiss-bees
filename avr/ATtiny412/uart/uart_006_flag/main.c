//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.c"
#include "uart_command.c"

//flag for input uart data
volatile int flag_uart = 0;

int main(){
	
	LED_init();
	USART0_init();

	//turn on interrupt
	sei();

	while (1){
		// read from buffer
		if (flag_uart == 1){
			USART0_read_buffer();
			flag_uart = 0;
		}
	}
}


ISR (USART0_RXC_vect){
	flag_uart = 1;
	USART0_to_buffer();
}