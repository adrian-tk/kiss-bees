//F_CPU shall be defined in main
#define USART0_BAUD_RATE(BAUD_RATE) ((float)((F_CPU) * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>

void USART0_init(void);
void USART0_sendChar(char c);
int USART0_printChar(char c, FILE *stream);
void USART0_sendString(char *str);

static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printChar, NULL, _FDEV_SETUP_WRITE);

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

	//add stream
	stdout= &USART_stream;
}

void USART0_sendChar(char c){
	while(!(USART0.STATUS & USART_DREIF_bm)){
		;
	}
	USART0.TXDATAL=c;
}

int USART0_printChar(char c, FILE *stream){
	USART0_sendChar(c);
	return 0;
}

void USART0_sendString(char *str){
	for(size_t i = 0; i < strlen(str); i++){
		USART0_sendChar(str[i]);
		_delay_ms(10);
		//USART0_sendChar(i);
	}
}
