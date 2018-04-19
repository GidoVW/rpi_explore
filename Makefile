SRCS=src/*.c
INCLUDES=inc/

CC=gcc

all:: $(SRCS)
	$(CC) -g -I$(INCLUDES) $(SRCS)


