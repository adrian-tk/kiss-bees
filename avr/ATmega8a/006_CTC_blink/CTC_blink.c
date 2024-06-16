//default frequency for atmega8a
//#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
   	// configure pin as output
	DDRB |= (1 << PB1);

	// configure timer for CTC
	TCCR1B |= (1 << WGM12);

	//compare in toggle mode
	TCCR1A |= (1 << COM1A0);

	//main freqency (1 000 000/s) / div (64) = 15625/s
	//so we need to count to 15624 (zero included) to get 1 second
	//
	// set compare value for ctc mode
	OCR1A = 15624;

	// Set timer with frequency | divided by 64
	TCCR1B |= ((1<<CS10) | (1<<CS11));

	while (1){
	}
}
