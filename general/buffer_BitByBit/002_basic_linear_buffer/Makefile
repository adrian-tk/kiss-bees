# makefile for pc 
#
# 2024-07-05
# Adrian Tomczyk
# adrian.tk@gmail.com
#
# 2024-07-05 initial version

# phony don't create file
.PHONY: clean all compile-all

#name of output file
PROG = main.elf

#CC = avr-gcc
CC = gcc

#OC = avr-objcopy
OC = gcc-objcopy

CFLAGS = -Wall \
	     -c \
	     -std=gnu99

LDFLAGS = 

OCFLAGS = 

SRCS = main.c

OBJS := $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) $<

compile-all: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS)

%.i: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -E $< -o $@

%.asm: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -S $< -o $@

clean: 
	rm -f $(PROG)	\
		$(PROG:.elf=.hex)	\
		$(PROG:.elf=.map)	\
	   	$(SRCS:.c=.o) \
	   	$(SRCS:.c=.d) \
	   	$(SRCS:.c=.asm) \
	   	$(SRCS:.c=.i) 

