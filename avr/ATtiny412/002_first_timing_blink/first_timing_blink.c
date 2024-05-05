//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

#include <avr/io.h>

int main(){
   	//configure pin as output
	PORTA.DIR |= PIN7_bm;

	//Set timer with frequency divided by 64
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc
						|TCA_SINGLE_ENABLE_bm;
					 

	for (;;){
		//checking value of our timer
		if (TCA0.SINGLE.CNT >= 13020){

			// Toggle pin
			PORTA.OUTTGL = PIN7_bm;

			//reset timer
			TCA0.SINGLE.CNT = 0;
		}
	}
}
