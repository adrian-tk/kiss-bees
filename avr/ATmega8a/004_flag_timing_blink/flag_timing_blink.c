//default frequency for atmega8a
//#define F_CPU 1000000UL

#include <avr/io.h>

int main(){
   	// configure pin as output
	DDRB |= (1 << PB1);

	// configure timer for CTC
	TCCR1B |= (1 << WGM12);

	// Set timer with frequency | divided by 64
	TCCR1B |= ((1<<CS10) | (1<<CS11));

	//main freqency (1 000 000/s) / div (64) = 15625/s
	//so we need to count to 15624 (zero included) to get 1 second
	
	// set compare value for ctc mode
	OCR1A = 15624;

	for (;;){
		//checking compare flags 
		if (TIFR & (1 << OCF1A)){

			// Toggle pin
			PORTB ^= (1 << 1);

			//clear CTC flag by writing 1(!)
			TIFR = (1 << OCF1A);
		}
	}
}
