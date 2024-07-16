# buffer
## 001 introduction
This is a good time for definition of buffer, so don't hesistate to find some and back here for some practice.

Problem: sometimes we try to commucate, but the speed of speking and listening are different. Someone might speak to You one word in a week, and You never know when exactly, so You have to listen them all the time doing nothing more. Or someone speak very fast, too fast to understand - You could record them and listen it in slower speed, or speed it up to find this one word in a week.
## 002 linear buffer v.1
buffer here is only a array of chars (in general it might be other)
in buffer_put() we put a char into array and increase position of writing, so next time we put a char in next position.
as You can see, now program works much better - case 1 and 2 works this same, but in case 3 now we can get all message.
However we use here some trick - for putting a value in buffer we put only a one char, but readinf from buffer is readed all buffer at once.
after reading buffer is reset to initial state, and position to zero.
when we want to read char by char, and allow to write to buffer meantime, we need to count from where we get a char.

## 003 linear buffer v.2
Here, we have two counters - one for putting a char, and one for pop a char. We put a char at the end of actual string, and pop from begging.
So after putting 3 char in a buffer it migh look like this:  
  
| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | h | e | l | _ | _ | _ | _ | _ | 
| put_counter    |   |   |   | 3 |   |   |   |   |
| pop_counter    | 0 |   |   |   |   |   |   |   |

after putting nex 2 char:  

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | h | e | l | l | o | _ | _ | _ | 
| put_counter    |   |   |   |   |   | 5 |   |   |
| pop_counter    | 0 |   |   |   |   |   |   |   |

after pop two char:  

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | h | e | l | l | o | _ | _ | _ | 
| put_counter    |   |   |   |   |   | 5 |   |   |
| pop_counter    |   |   | 2 |   |   |   |   |   |

As You can see val 'h' stay in buffer, we don't clean it, just move
the buffer counter. Those data are useless for us, so we replace them here with "_" (only with this visualisation, not in real program)

after put 2 char:  

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | l | l | o |   | w | _ | 
| put_counter    |   |   |   |   |   |   |   | 7 |
| pop_counter    |   |   | 2 |   |   |   |   |   |

after pop 4 char:  

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | _ | _ | w | _ | 
| put_counter    |   |   |   |   |   |   |   | 7 |
| pop_counter    |   |   |   |   |   |   | 6 |   |

As we can see program works differently, but preserves all values.
after some additional put we could get something like this:  

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | _ | _ | w | o | 
| put_counter    |   |   |   |   |   |   |   | 7 |
| pop_counter    |   |   |   |   |   |   | 6 |   |

and our buffer is full - we have no place to put anything at the end, and empty spaces at the begging are useless beacue we can't write there.
We can reset buffer (problematic, when not everything is popped out), or connect end with start and create a ring buffer.

## 004 Ring buffer
Ring buffer (circular buffer, o-buffer), solves problem of cleaning linear buffer. End of buffer is connected to the start of buffer, like snake eating his tail.
We need to count input (put_ct) and output (pop_ct). 
Buffer works like this:  
Epmty buffer

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | _ | _ | _ | _ | 
| put_counter    | 0 |   |   |   |   |   |   |   |
| pop_counter    | 0 |   |   |   |   |   |   |   |

Put a data - when buffer is empty, we can't read (pop) data from it beacuse there is no data.
so we can only put a data to the buffer, we place it at put_ct counter value.
we place here 'h', after put we need to increment put_ct.


| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | h | _ | _ | _ | _ | _ | _ | _ | 
| put_counter    |   | 1 |   |   |   |   |   |   |
| pop_counter    | 0 |   |   |   |   |   |   |   |

Pop a data
when we read (pop) data we get 'h' and we need to increment pop_ct.

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | h | _ | _ | _ | _ | _ | _ | _ | 
| put_counter    |   | 1 |   |   |   |   |   |   |
| pop_counter    |   | 1 |   |   |   |   |   |   |

As You can see val 'h' stay in buffer, we don't clean it.
We might overwrite it by ' ', '0' or better '\0',
but that additional work for microcontroller or processor.
We know what to read/write beacuse of put/pop counters,
so there is no need to do extra work. Even behind 'h' there
are some data - there is no 'empty' place in memory, so for clearness, 
we will only show data we need like this:

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | _ | _ | _ | _ | 
| put_counter    |   | 1 |   |   |   |   |   |   |
| pop_counter    |   | 1 |   |   |   |   |   |   |

now we can again put some data, like 'e', we put it in put_ct value (1),
and increment put_ct.

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | e | _ | _ | _ | _ | _ | _ | 
| put_counter    |   |   | 2 |   |   |   |   |   |
| pop_counter    |   | 1 |   |   |   |   |   |   |

now we can read it, and increment pop_ct

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | _ | _ | _ | _ | 
| put_counter    |   |   | 2 |   |   |   |   |   |
| pop_counter    |   |   | 2 |   |   |   |   |   |

As we can see when put_ct and pop_ct are equal, the buffer is empty.
We can use it to test if we can read from buffer - if we don't do this
we might get some unexpected values from other buffer addresses
(we don't clean values).
put 5 values "llo w ", and increment put_cr by 5:

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | l | l | o |   | w | _ | 
| put_counter    |   |   |   |   |   |   |   | 7 |
| pop_counter    |   |   | 2 |   |   |   |   |   |

pop two values (we get "ll"), and increment pop_cr by 2:

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | _ | _ | _ | _ | o |   | w | _ | 
| put_counter    |   |   |   |   |   |   |   |  7|
| pop_counter    |   |   |   |   | 4 |   |   |   |

Now lets put 5 char in buffer - simple - when we get to the end (cell 7)
we just start from 0 - as we can see 0 till 4 are empty right now

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | r | l | d | ! | o |   | w | o | 
| put_counter    |   |   |   |   | 4 |   |   |   |
| pop_counter    |   |   |   |   | 4 |   |   |   |

and our buffer is full. But there is a problem: put_ct and pop_ct are equal,
which mean that the buffer is empty.
How can we know if buffer is full or emtpy?
We can use new values like buff_status which has the size of used
cell in buffer ie. 0 when empty, 3 when 3 char and 8 when full
(in our example).
Other popular solution is to have always last one cell empty, so in our example:

| Buffer cell    | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|----------------|---|---|---|---|---|---|---|---|
| Buffer         | r | l | d | _ | o |   | w | o | 
| put_counter    |   |   |   | 3 |   |   |   |   |
| pop_counter    |   |   |   |   | 4 |   |   |   |

and the last '!' did not fit.
We "lost" one cell which always be empty, but we don't need addtional values.
In this case, buffer is full when put_ct is one before pop_ct.
We will stick to this solution in our example.

## 005 struct
What will happen if You need two buffers? Two Uart or use them for something completly different? At our example You have only one buffer named "buffer", You can create anotrer like "buffer2" but all functions works with "buffer" so You have to change them, mayby the easiest will by copy all file and change "buffer[]" to "buffer2[]". We can send buffer as an argument, but we need also counters (integer shall be send as pointers of course), of course buffers might have different sizes. It migh be easiest to get those things together as C struct, initialize struct for everty buffer, and send struct pointer to functions.  


## To Read
[Embedded Artistry - Creating a Circular Buffer in C and C++](https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/)