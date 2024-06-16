//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

#include <avr/io.h>

int main(){

	//set alternate port (PIN7)
	PORTMUX.CTRLC = PORTMUX_TCA00_ALTERNATE_gc;
   	//configure pin as output
	PORTA.DIR |= PIN7_bm;

	//main frequency (3333333/s) / div(64) ~13021/s 
	//so we need 13020 (incl. zero) to get 1s

	// Set compare value
	TCA0.SINGLE.CMP0 = 13020; 
	
	//FRQ mode
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_FRQ_gc
						|TCA_SINGLE_CMP0EN_bm;

	//disable event counting, default
	//TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	//Set timer with frequency divided by 256
	//and enable a timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc
						|TCA_SINGLE_ENABLE_bm;
					 
	while (1){
	}
}
