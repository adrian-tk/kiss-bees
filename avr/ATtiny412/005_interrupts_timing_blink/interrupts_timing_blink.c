//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
   	//configure pin as output
	PORTA.DIR |= PIN7_bm;

	//main frequency (3333333/s) / div(64) ~13021/s 
	//so we need 13020 (incl. zero) to get 1s

	// Set compare value
	TCA0.SINGLE.PER = 13020; 
	
	// enable overflow interrupt
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	//no waveform - normal mode, deafult?
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;

	//disable event counting, default?
	TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	//Set timer with frequency divided by 256
	//and enable a timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc
						|TCA_SINGLE_ENABLE_bm;
					 
	//enable global interrupts
	sei();

	for (;;){
	}
}

ISR(TCA0_OVF_vect){
	// Toggle pin
	PORTA.OUTTGL = PIN7_bm;

	//clear flags
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
