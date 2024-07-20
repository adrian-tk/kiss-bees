//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include "uart_send.c"
#include "temperature_internal.c"
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

int main(){

	USART0_init();
	ADC0_init();

	while (1){

		char str[16];
		itoa(internal_temperature(), str, 10);
		strcat(str, "*C\r\n");

		USART0_sendString(str);
		_delay_ms(1000);
	}
}
