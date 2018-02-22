SRCS=src/*.c
INCLUDES=inc/

CC=gcc

all:: $(SRCS)
	gcc -I$(INCLUDES) $(SRCS)


