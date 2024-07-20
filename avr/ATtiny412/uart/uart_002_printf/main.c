//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include "uart_send.c"
#include <util/delay.h>
//#include <avr/io.h>
//#include <string.h>

int main(){
	USART0_init();
	uint8_t count = 0;

	while (1){
		printf("Counter value is: %d\n\r", count++);
		//USART0_sendString("Hello World!\r\n");
		_delay_ms(50);
	}
}
