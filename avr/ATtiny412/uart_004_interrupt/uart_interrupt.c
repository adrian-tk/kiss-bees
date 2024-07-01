//F_CPU shall be defined in main
#define USART0_BAUD_RATE(BAUD_RATE) ((float)((F_CPU) * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define MAX_COMMAND_LEN 8

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

ISR (USART0_RXC_vect);
void USART0_init(void);
void USART0_sendChar(char c);
int USART0_printChar(char c, FILE *stream);
void USART0_sendString(char *str);
void USART0_listen(void);
char USART0_readChar(void);

static FILE USART_stream = FDEV_SETUP_STREAM(USART0_printChar, NULL, _FDEV_SETUP_WRITE);
char command[MAX_COMMAND_LEN];
uint8_t char_index = 0;
char c;

ISR (USART0_RXC_vect){
	USART0_listen();
}


void USART0_init(void){
	//set alternate ports
	//PORTMUX.CTRLB = PORTMUX_USART0_DEFAULT_gc;
	//PORTMUX.CTRLB = PORTMUX_USART0_ALTERNATE_gc;
	
	//TxD - transmit pin
	PORTA.DIR |= PIN6_bm;
	//RxD - receive pin
	PORTA.DIR &= ~PIN7_bm;
	
	//baud rate
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);

	//turn on interrupt
	USART0.CTRLA |= USART_RXCIE_bm; 

	//turn on transmit and receive
	USART0.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;

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
	}
}

void USART0_listen(void){
	c = USART0_readChar();
    if(c != '\n' && c != '\r'){
		//simple echo
		USART0_sendChar(c);
	    command[char_index++] = c;
        if(char_index > MAX_COMMAND_LEN){
	        char_index = 0;
        }
	} else {
		//when we have \n or \r add \0 and print it
	    command[char_index] = '\0';
        char_index = 0;
        printf("\n\rcommand: %s\n\r", command);
    }
}

char USART0_readChar(void){
	while(!(USART0.STATUS & USART_RXCIF_bm)){
		;
	}
	return USART0.RXDATAL;
}

