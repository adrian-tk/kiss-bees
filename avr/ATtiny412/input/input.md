# input methods
## easy button
connect attiny as in schema:
![input connection schema](doc/schema.svg "schema")  
Don't bother with PWR_FLAG, there are only needed for some checking in KiCad. You can power ATtiny from uart programmer, but have in mind power voltage - when You power with 5V, You might destroy some equpment for 3.3V (eg. raspberry pi GPIO). In this situation 5V or 3.3V is not important, however You might see difference in LED brightness.
As input pin we have PA1 (4th pin on ATtiny)
```c
PORTA.DIRCLR = PIN1_bm;
```
We need also a pull up internal resistor. Look at schema - when we put down a SW1 Swich we connect ATtiny pin to ground. But what is the state of this pin when switch is unpressed? It is floating pin and it's state is unknown. Input pin shall be connected to GND and has a low state or to VCC and have a high state. We can connect pin to VCC and have high state, but when we push a button we connect VCC with GND directly wchich is not a good idea, current might be very high and burn somethin (like switch or building).  
To limit current we can use a resistor. Consider following schema:
![pullup](doc/pullup.svg "schema")  
Input pin of Attiny has a very big impedance, so resistor with 1K or similar is insignificant and we have high state, when SW1 in put down, 1K resistor is very big compared to switch resistance, so we have low state at ATtiny pin.  
The good news is ATiny already has a build in a pullup resistor inside. We only need to turn it on:
```c
PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
```
Now we need only read the state of input pin, and change the state of output pin;
```c
while(1){
  //check the state of input
  if (~PORTA.IN & PIN1_bm){
   //turn on led
   PORTA.OUT |= PIN3_bm;
  }
  else{
   //turn of led
   PORTA.OUT &= ~PIN3_bm;
  }
 }
```

## interrupt button
In previous example we check the state of pin in every loop, now it is time to use interupts for that.  
