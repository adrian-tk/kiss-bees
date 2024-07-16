#include <stdio.h>

char short_message;
char message[] = "hello";
char buffer[20];
int write_position = 0;
int num = 0;
void talking(void);
void hearing(void);

void buffer_put();
void buffer_read();

void buffer_put(){
	buffer[write_position]=short_message;
	write_position++;
}

void buffer_read(){
	printf("buffered hear: %s\n\r", buffer);
	buffer[0]='\0';
	write_position = 0;
}


void talking(void){
	if (num > 4){
		num=0;
	}
	short_message = message[num];
	printf("foo speak: %c\n\r", short_message);
	num++;
	buffer_put();
}

void hearing(void){
	printf("bar hear: %c\n\r", short_message);
	short_message = ' ';
	buffer_read();
}
	
int main(void){

	printf("=====case 1======\n\r");
	num = 0;
	talking();
	hearing();
	printf("=====case 2======\n\r");
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
	talking();
	hearing();
	hearing();
	hearing();
	talking();
	hearing();
	hearing();
	hearing();
}


