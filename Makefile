SRCS=src/*.c
INCLUDES=inc/

ARCH=$(shell arch)

ifeq ($(ARCH),x86_64)
  CC=arm-linux-gnueabi-gcc
else
  CC=gcc
endif

OUTPUT=rpio

all: $(SRCS)
	$(CC) -g -I$(INCLUDES) $(SRCS) -Wall -o $(OUTPUT)


