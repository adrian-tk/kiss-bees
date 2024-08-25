## 006 flag

Interrupt looks like work very well, but there is a little problem - ISR routine is very big - we get an uart, build command, dispatch it, lighting LED ets. and at the end ending ISR. That is a lot to do, and might be even more for more complicated program.  
Interrupt functions shall be short as possible, if a lot of job has to be done we shall use a flags:

```c
//flag for input uart data
volatile int flag_uart = 0;
```

volatile is good idea, beacuse of interrupt way of changing data.
Compilers don't know when interrupt will work, and may "optimize" reading of flag value, and read it only when expect some changes.
volatile indicates, that this value shall be always directly read from memory to be shure we have actual values.

ISR only set a flag and write to buffer:

```c
ISR (USART0_RXC_vect){
  flag_uart = 1;
  USART0_to_buffer();
}
```

In main loop we check a flag, and when it's set we read buffer, react for it and clear a flag:

```c
while (1){
  // read from buffer
  if (flag_uart == 1){
    USART0_read_buffer();
    flag_uart = 0;
  }
}
```

USART0_read_buffer might take long time, when new data arrives on UART, interrupt stops USART_read_buffer, read data from UART, saves them in ring buffer, and comes back to USART_read_buffer to continue. Of course, when data arrives quicker than USART0_read_buffer can work with them, the ring buffer eventualy will be full, and will not accept new data.

## 007 separation

Uart might be used with many programs for microcontroller, It is good idea to separate it, moving possibly all needed functions to uart, all interface (definition functions used by programmer)to uart.h file

- move all uart files to one direcory (uart)
- move as much as possible to uart.c funcitons

at this time minimal main.c looks like this:

```c
#define F_CPU 3333333

#include "uart/uart.c"

int main(){
 USART0_init();

 //turn on interrupt
 sei();

 while (1){
  USART0_flag();
 }
}
```

Be aware, that You need to include F_CPU - it is used by usart module

To use module, add uart directory, and modify main.c as showed.
