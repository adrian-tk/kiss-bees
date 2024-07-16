#include <stdio.h>
#define BUFSIZE 20

char short_message;
char message[] = "hello";
char buffer[BUFSIZE];
int put_position = 0;
int pop_position = 0;
int num = 0;
void talking(void);
void hearing(void);

void buffer_put(char c);
char buffer_pop(void);

void buffer_put(char c){
	//check if not full
	if (put_position < BUFSIZE){
		buffer[put_position++]=c;
	}
}

char buffer_pop(void){
	//check if not empty
	if (pop_position < put_position){
		return buffer[pop_position++];
	}
	else {
		return '\0';
	}
}


void talking(void){
	if (num > 4){
		num=0;
	}
	short_message = message[num];
	printf("foo speak: %c\n\r", short_message);
	num++;
	buffer_put(short_message);
}

void hearing(void){
	char element;
	element = buffer_pop();
	printf("bar hear: %c\n\r", element);
}
	
int main(void){

	printf("=====case 1======\n\r");
	num = 0;
	put_position = 0;
	pop_position = 0;
	talking();
	hearing();
	printf("=====case 2======\n\r");
	put_position = 0;
	pop_position = 0;
	num = 0;
	talking();
	hearing();
	talking();
	hearing();
	talking();
	hearing();
	talking();
	hearing();
	printf("=====case 3======\n\r");
	num = 0;
	put_position = 0;
	pop_position = 0;
	talking();
	talking();
	talking();
	hearing();
	talking();
	talking();
	talking();
	hearing();
	printf("=====case 4======\n\r");
	num = 0;
	put_position = 0;
	pop_position = 0;
	talking();
	hearing();
	hearing();
	hearing();
	talking();
	hearing();
	hearing();
	hearing();
}


