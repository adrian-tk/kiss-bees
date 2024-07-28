//default frequency is 20MHz with prescaler division factor of 6
#define F_CPU 3333333UL

/*
 * 2024-07-20
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	PORTA.DIR |= PIN3_bm;

	while(1){
		PORTA.OUT |= PIN3_bm;
		_delay_ms(100);
		PORTA.OUT &= ~PIN3_bm;
		_delay_ms(100);
	}
}
