/* blinking diode with fade in and fade out
 * TCA0 takes care of PWM for diode
 * CTB0 counts time to flag change of PWM with interrupt
 * when flag is set PWM value is changed depending on direction
 * direction is changed beetween 0 and top value for PWM
 */

/*
 * 2024-06-19
 * Adrian Tomczyk
 * adrian.tk@gmail.com
 */

//default frequency is 20MHz with prescaler division factor of 6
//#define F_CPU 3333333UL

#include <avr/io.h>
#include <avr/interrupt.h>

void PORT_init(void);
void TCA0_init(void);
void TCB0_init(void);

// global variables
// flag is set on interrupt
volatile int flag;

//initialize ports
void PORT_init(void){
	
	//set alternate port (PIN7)
	PORTMUX.CTRLC = PORTMUX_TCA00_ALTERNATE_gc;

   	//configure pin as output
	PORTA.DIR |= PIN7_bm;
}

//initialize timer TCA0
void TCA0_init(void){

	//fclk/(2xTCAprescaler x fds_PWM)
	//3333333/(2x4x1000)~416
	TCA0.SINGLE.PERBUF = 416; 

	//for 50 % duty cycle half of perfbuf
	TCA0.SINGLE.CMP0BUF = 208; 
	
	//PWM mode
	TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_DSBOTTOM_gc
						|TCA_SINGLE_CMP0EN_bm;

	//disable event counting, default
	//TCA0.SINGLE.EVCTRL &= ~(TCA_SINGLE_CNTEI_bm);

	//Set timer with frequency divided 
	//and enable a timer
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV4_gc
						|TCA_SINGLE_ENABLE_bm;
}
void TCB0_init(void){

	//set compare value
	TCB0.CCMP = 65535;

	//enable interrupts
	TCB0.INTCTRL = TCB_CAPT_bm;

	//enable counter
	TCB0.CTRLA |= TCB_CLKSEL_CLKDIV2_gc
			     | TCB_ENABLE_bm;
}

int main(){
	flag = 0;
	int i = 0;
	int direction = 0;
	
	PORT_init();
	TCA0_init();
	TCB0_init();

	//enable global interrupts
	sei();

	while (1){
		if (flag){
			//value of PWM
			TCA0.SINGLE.CMP0BUF = i; 
			if (direction)
			   	i = i - 20;
			else
				i = i + 20;
			if (i >= TCA0.SINGLE.PERBUF)
				direction = 1;
			if (i <= 0)
				direction = 0;
			flag = 0;
		}
	}
}

ISR(TCB0_INT_vect){

	//set flag
	flag = 1;
	
	//clear interrupt flag
	TCB0.INTFLAGS = TCB_CAPT_bm;
}
