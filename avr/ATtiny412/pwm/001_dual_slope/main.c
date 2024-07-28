//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

/*
 * 2024-07-20
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/io.h>

void PORT_init(void);
void TCA0_init(void);

//initialize ports
void PORT_init(void){
	
	//set alternate port (PIN7) instead of PIN3
	//PORTMUX.CTRLC = PORTMUX_TCA00_ALTERNATE_gc;

   	//configure pin as output
	PORTA.DIR |= PIN3_bm;
}

//initialize timer TCA0
void TCA0_init(void){

	//fclk/(2xTCAprescaler x fds_PWM)
	//3333333/(2x4x1000)~416
	TCA0.SINGLE.PERBUF = 416; 

	//for 50 % duty cycle half of perfbuf
	//for 1 % duty cycle 1/100 of perfbuf
	TCA0.SINGLE.CMP0BUF = 4; 
	
	//PWM mode
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_DSBOTTOM_gc
						|TCA_SINGLE_CMP0EN_bm;

	//disable event counting, default
	//TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	//Set timer with frequency divided 
	//and enable a timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc
						|TCA_SINGLE_ENABLE_bm;
}


int main(){
	PORT_init();
	TCA0_init();

	while (1){
	}
}
