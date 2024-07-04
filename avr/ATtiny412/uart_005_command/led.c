#include <avr/io.h>
#include <stdio.h>
#include <string.h>

void LED_init(void);
void LED_disp(char *arg);
void LED_on(void);
void LED_off(void);

void LED_init(void){

	//set pin as a output
    PORTA.DIR |= PIN3_bm;
}
void LED_disp(char *arg){
	//printf("argument for led: %s\n\r", arg);
	if (strcmp(arg, "") == 0){
		printf("argument needed, try: led help\n\r");
	}
	else if (strcmp(arg, "help") == 0){
		printf("available arguments: help, on, off\n\r");
	}
	else if (strcmp(arg, "on") == 0){
		LED_on();
	}
	else if(strcmp(arg, "off") == 0){
	   	LED_off();
	}
	else{
	   	printf("unknown argument: %s, try: led help\n\r", arg);
	}
}
void LED_on(void){
	printf("turning on led\n\r");
	PORTA.OUT |= PIN3_bm;
}
void LED_off(void){
	printf("turning off led\n\r");
	PORTA.OUT &= ~PIN3_bm;
}
