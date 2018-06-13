SRCS=src/*.c
INCLUDES=inc/

CC=gcc

OUTPUT=rpio

all: $(SRCS)
	$(CC) -g -I$(INCLUDES) $(SRCS) -Wall -o $(OUTPUT)


