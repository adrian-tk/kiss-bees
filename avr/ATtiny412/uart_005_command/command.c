//#include <stdio.h>

void dispatcher(char* command, uint8_t strlen);

void dispatcher(char* command, uint8_t strlen){
	if(strcmp(command, "led on")==0){
		printf("turning on led\n\r");
		LED_on();
	}
	if(strcmp(command, "led off")==0){
		printf("turning off led\n\r");
		LED_off();
	}
}
