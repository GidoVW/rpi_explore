SRCS+=rpio_peripherals.c

ifndef RPIO_INSTALL_DIR
	INCLUDE_DIR+=-I../../common
	INCLUDE_DIR+=-I../
else
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/common
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals
endif

OUTPUT=librpio_periph.so

CFLAGS=-g -fPIC -shared

all: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(SRCS) -Wall -o $(OUTPUT)