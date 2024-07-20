## linear buffer v.2
Here, we have two counters - one for putting a char, and one for pop a char. We put a char at the end of actual string, and pop from begging.
So after putting 5 char in a buffer it migh look like this:
hello_______________
after putting nex 2 char:
hellohe_____________
after pop two char:
__llohe_____________
after put 3 char:
__llohello__________
after pop 5 char:
_______llo__________
(at "_" might be some trash beacuse we don't really delete anything. We just count where are data that are interest to us.)
You can see them in prevous example in case 4.
As we can see program works differently, but preserves all values.
after some additional putting and popping we could get something like this:
_________________llo
and our buffer is full - we have no place to put anything at the end, and empty spaces at the begging are useless beacue we can't write there.
We can reset buffer (problematic, when not everything is popped out), or connect end with start and create a ring buffer.

