//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333

#include "uart_duplex.c"
//#include <util/delay.h>

int main(){
	
	USART0_init();

	while (1){
		//listen for incoming data on uart
		//it block this loop, so rest of it 
		//will be executed only if dome
		//data will be send on uart
		USART0_listen();
		}
		//_delay_ms(50);
}
