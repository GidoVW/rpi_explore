SRCS+=main.c

ifndef RPIO_INSTALL_DIR
	INCLUDE_DIR+=-I../
	INCLUDE_DIR+=-I../peripherals/gpio_drv
else
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals/gpio_drv
endif

OUTPUT=test.out

ifndef RPIO_INSTALL_DIR
	LIBS_DIRS+=-L../lib
else
	LIBS_DIRS+=-L$(RPIO_INSTALL_DIR)/lib
endif

LIB_NAME+=-lgpio_drv
LIB_NAME+=-lrpio_periph

LIBFLAGS=$(LIBS_DIRS) $(LIB_NAME)

all: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(SRCS) $(LIBFLAGS) -Wall -o $(OUTPUT)