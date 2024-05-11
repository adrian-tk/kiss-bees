//default frequency for atmega8a
//#define F_CPU 1000000UL

#include <avr/io.h>

int main(){

	// for counting seconds
	unsigned char sec_count = 0;

   	//configure pin as output
	DDRB |= (1<<PB0);

	//Set timer with frequency | divided by 64
	TCCR1B |= ((1<<CS10) | (1<<CS11));

	//main freqency (1 000 000/s) / div (64) = 15625/s
	//so we need to count to 15624 (zero included) to get 1 second

	for (;;){
		//checking value of our timer
		if (TCNT1 >= 15624){

			//reset timer
			TCNT1 = 0;

			sec_count++;

			//check if 60 seconds has elapsed
			if (sec_count == 60){
				sec_count = 0;	

				// Toggle pin
				PORTB ^= (1<<0);
			}
		}
	}
}
