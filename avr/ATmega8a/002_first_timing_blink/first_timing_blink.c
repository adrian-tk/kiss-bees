#define F_CPU 1000000UL

#include <avr/io.h>

int main(){
   	//configure pin as output
	DDRB |= (1<<PB0);

	//Set timer with frequency as main clock
	//TCCR1B |= (1<<CS10);
	//Set timer with frequency divided by 64
	TCCR1B |= ((1<<CS10) | (1<<CS11));
					 

	for (;;){
		//checking value of our timer
		if (TCNT1 >= 15624){

			// Toggle pin
			PORTB ^= (1<<0);

			//reset timer
			TCNT1 = 0;
		}
	}
}
