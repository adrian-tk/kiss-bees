//default frequency is 20MHz with prescaler division factor of 6
//define it here for uart macros
#define F_CPU 3333333
//baud rate
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(3333333 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void USART0_init(void);
void USART0_sendChar(char c);
void USART0_sendString(char *str);

void USART0_init(void){
	//set alternate ports
	//PORTMUX.CTRLB = PORTMUX_USART0_DEFAULT_gc;
	//PORTMUX.CTRLB = PORTMUX_USART0_ALTERNATE_gc;
	//TxD
	PORTA.DIR |= PIN6_bm;
	//PORTA.DIR |= PIN6_bm;
	//RxD
	PORTA.DIR &= ~PIN7_bm;
	
	//baud rate
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
	USART0.CTRLB |= USART_TXEN_bm;
}

void USART0_sendChar(char c){
	while(!(USART0.STATUS & USART_DREIF_bm)){
		;
	}
	USART0.TXDATAL=c;
}

void USART0_sendString(char *str){
	for(size_t i = 0; i < strlen(str); i++){
		USART0_sendChar(str[i]);
		_delay_ms(10);
		//USART0_sendChar(i);
	}
}

int main(){
	USART0_init();

	while (1){
		//USART0_sendChar('H');
		USART0_sendString("jdtcpsc \r\n");
		_delay_ms(500);
	}
}
