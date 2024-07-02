#include <avr/io.h>

void LED_init(void);
void LED_on(void);
void LED_off(void);

void LED_init(void){

	//set pin as a output
    PORTA.DIR |= PIN3_bm;
}
void LED_on(void){
	PORTA.OUT |= PIN3_bm;
}
void LED_off(void){
	PORTA.OUT &= ~PIN3_bm;
}
