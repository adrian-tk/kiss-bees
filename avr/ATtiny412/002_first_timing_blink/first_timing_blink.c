//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

/*
 * 2024-07-20
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

#include <avr/io.h>

int main(){
   	//configure pin as output
	PORTA.DIR |= PIN3_bm;

	//Set timer with frequency divided by 256
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc
						|TCA_SINGLE_ENABLE_bm;
					 
	//main frequency (3333333/s) / div(64) ~13021/s 
	//so we need 13020 (incl. zero) to get 1s

	for (;;){
		//checking value of our timer
		if (TCA0.SINGLE.CNT >= 13020){

			// Toggle pin
			PORTA.OUTTGL = PIN3_bm;

			//reset timer
			TCA0.SINGLE.CNT = 0;
		}
	}
}
