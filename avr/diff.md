# differences between avr microcontrollers

ATmega8a
ATtiny412 - ATtiny 1-series

|what|Atmega8a|ATtiny412|
|---|---|---|
|pin as out|DDRB \|= (1<<BP0)|PORTA.DIR \|= PIN7_bm|
|toggle pin|PORTB ^= (1<<0)|PORTA.OUTGL = PIN7_bm|
