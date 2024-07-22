//#include <stdio.h>
#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef MAX_COMMAND_LEN
#define MAX_COMMAND_LEN 20
#endif

void dispatcher(char* command);
void stripper(char* command, char* first, char* rest);

void dispatcher(char* command){
	//printf("command to dispatch: %s\n\r", command);
	char com[MAX_COMMAND_LEN];
	char arg[MAX_COMMAND_LEN];
	stripper(command, com, arg);
	//printf("com: %s\n\r", com);
	//printf("arg: %s\n\r", arg);
	
	if(strcmp(com, "")==0){
		;
	}
	else if(strcmp(com, "led")==0){
		LED_disp(arg);
	}
	else if(strcmp(com, "help") == 0){
			printf("available command: help, led\n\r");
	}
	else {
		printf("unknown command: %s, try: help\n\r", com);
	}
}

void stripper(char* command, char* first, char* rest){
	//function takes command
	//all char up to first " " is put in first
	//all char behind first " " are put in rest
    char t_first[MAX_COMMAND_LEN];
    char t_rest[MAX_COMMAND_LEN];
    int count = 0;
	char flag = 0;
    for (int i=0; command[i] != '\0'; i++){
        if (flag == 0 && command[i] != ' '){
            t_first[i] = command[i];
            t_first[i+1] = '\0';
            count = i+1;
        } else {
			flag = 1;
            t_rest[i-count] = command[i+1];
        }
		t_rest[i-count+1] = '\0';
		strcpy(first, t_first);
		strcpy(rest, t_rest);
    }
	//	printf("first: %s\n\r", first);
	//	printf("rest: %s\n\r", rest);
}
