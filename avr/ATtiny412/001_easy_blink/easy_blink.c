//default frequency is 20MHz with prescaler division factor of 6
#define F_CPU 3333333UL

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	PORTA.DIR |= PIN7_bm;

	while(1){
		PORTA.OUT |= PIN7_bm;
		_delay_ms(100);
		PORTA.OUT &= ~PIN7_bm;
		_delay_ms(100);
	}
}
