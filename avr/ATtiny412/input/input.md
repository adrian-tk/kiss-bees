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

## uart button
Getting info about what happening using diode is very easy and fast, but don't give us much info, more we can get with uart, we use uart from our uart examples (uart_007_separation TODO link).

After minor changes we can get information on uart:

```c
while(1){

  USART0_flag();

  //check the state of input
  if (~PORTA.IN & PIN1_bm){
   //turn on led
   PORTA.OUT |= PIN3_bm;
   printf("led on");
  }
  else{
   //turn of led
   PORTA.OUT &= ~PIN3_bm;
   printf("led off");
  }
 }
```

on uart we can see that, microcontroller all the time check state of the port, and react with changing pin state, of course better solution will be using interrupts

## interrupt button
In previous example we check the state of pin in every loop, now it is time to use interupts for that.  
On PIN1 we have to turn on interrupts

```c
PORTA.PIN1CTRL = PORT_ISC_BOTHEDGES_gc;
```

BOTHEREDGES start interrupts on either raising up signal, and fall down. Other possibilities might be found in uc documentation.
Now ISR, as usual it shall be as short as possible:

```c
ISR(PORTA_PORT_vect)
{
 if (PORTA.INTFLAGS & PIN1_bm)
 {
  // set flag to signal some input
  pin1_change = 1;
  // clear interrupt flag
  PORTA.INTFLAGS &= PIN1_bm;
 }
}
```

interrupt is triggered by PORTA_PORT_vect, as You see there is only a port and not a pin, so first we have to check if flag was changed on PIN1. In our example we have only one pin so, we might not check it and assume that any change on port is for pin1 - if we comment this if statment program will work this same.  
Next we set our flag and clear flag from interrupt.
in main TODO
When we run a program and swith a button few times, we get something like this on uart:

```bash
off
on 
off
on 
off
off
on 
off
on 
off
on 
on
off
off
on 
off
off
on 
off
on 
off
```

We had those info about changing state only when pin state was changed, so interrupt works as expect. However we might notice, that there is sometimes twice time on, or off - it shall be alternately. The problem is with our switch - it needs some time to get stable - after changing state it "bounce" a little changing state very fast.
