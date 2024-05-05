# Programing ATtiny412
## Hardware
ATtiny uses completly different (UDPI) programing interface than older type of AVR microcontroller. You can program UDPI You will need some UART interface - preferably USB-Uart. I use a Waveshare 21443 with USB-C and changable power (3V3 or 5V), but any other shall work. Additionaly You will need a 1kohm resistor (1/8 watt well be ok, but of course You can use bigger one).
![connection schema](connection.svg "connection schema")  
Real connection on bredboard  might look like below. ATtiny412 (and other uc in this series) don't have a convinient Dip package, so SOP8 to Dip8 adapter was used.  
![connection example](bb.jpg "connection example")
