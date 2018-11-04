SRCS+=gpio_drv.c

ifndef RPIO_INSTALL_DIR
	INCLUDE_DIR+=-I../../common
	INCLUDE_DIR+=-I../
	INCLUDE_DIR+=-I../src
else
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/common
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals/src
endif

OUTPUT=libgpio_drv.so

CFLAGS=-g -fPIC -shared

LIBS_DIRS+=-L$(RPIO_INSTALL_DIR)/peripherals/src
LIBS+=-lrpio_periph

LIBFLAGS=$(LIBS_DIRS) $(LIBS)

all: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(SRCS) $(LIBFLAGS) -Wall -o $(OUTPUT)