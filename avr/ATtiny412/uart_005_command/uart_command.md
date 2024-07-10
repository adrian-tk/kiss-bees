## UART command

 program takes command from uart, confirm it, and react - turn on, or turn off diode.

 ### main.c
 file for main program
 * define F_CPU needed for USART and delays
 * include all needed files (wiht local too)
 * in main(): initialize LED and UART, turn on interrupt, and forever loop
 ### uart_command.c
 all uart communication, this time received string is sent to dispatcher() in command.c.
 ### command.c
 get command from uart, and decide what to do: turn on or off diode. Proper function (LED_on(), or LED_off) defined in LED.c is raised. Dispatcher only decide what to do, and not how to do. It only dispatch command to desired functions.
 ### led.c
 initialisation of pin with LED, and function to turn on and off