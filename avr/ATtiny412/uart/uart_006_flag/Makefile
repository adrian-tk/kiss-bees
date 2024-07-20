#top level makefile
#
# 2024-07-20
# Adrian Tomczyk
# adrian.tk@gmail.com
#
# it is divided for many nested include files for maintance
# if You like to use one make file, just copy contents of include files
# in place of include definition

# how deep we are
# show how to get to the avr dir
DEEP = ../../../


# files to compile
# separate with blanks if more that one
# filename might be used or wildcard for all.
SRCS = main.c ring_buffer.c
#SRCS = *.c

# if needed set fuse here
# might be programed with "make fuse_set"
#
# 8 MHz
#L_FUSE = 0xe4
#H_FUSE = 0xd9

include $(DEEP)ATtiny412/attiny412_makefile
