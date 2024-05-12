//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

#include <avr/io.h>

int main(){

	// for counting seconds
	unsigned char sec_count = 0;

   	//configure pin as output
	PORTA.DIR |= PIN7_bm;

	//Set timer with frequency divided by 256
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV256_gc
						|TCA_SINGLE_ENABLE_bm;
					 
	//main frequency (3333333/s) / div(64) ~13021/s 
	//so we need 13020 (incl. zero) to get 1 second

	for (;;){
		//checking value of our timer
		if (TCA0.SINGLE.CNT >= 13020){

			//reset timer
			TCA0.SINGLE.CNT = 0;

			sec_count++;

			//check if 60 seconds has elapsed
			if (sec_count == 60){
				sec_count = 0;

				// Toggle pin
				PORTA.OUTTGL = PIN7_bm;
			}
		}
	}
}
