SRCS+=gpio_drv.c

MAJOR=0
MINOR=1
PATCH=0
VERSION=$(MAJOR).$(MINOR).$(PATCH)

NAME=gpio_drv
LIBNAME=lib$(NAME).so.$(VERSION)

RM=rm -f

ifndef RPIO_INSTALL_DIR
	INCLUDE_DIR+=-I../../common
	INCLUDE_DIR+=-I../
	INCLUDE_DIR+=-I../src
else
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/common
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals/src
endif

ifdef RPIO_INSTALL_DIR
	LIB_DIR=$(RPIO_INSTALL_DIR)/lib
endif

SONAME=-Wl,-soname,$(LIBNAME)

LIBS_DIRS+=-L$(LIB_DIR)
LIBS+=-lrpio_periph

LIBFLAGS=$(LIBS_DIRS) $(LIBS)

lib: clean lib$(NAME).so clean_obj

lib$(NAME).so: lib$(NAME).so.$(VERSION)

lib$(NAME).so.$(VERSION): $(NAME).o 
	$(CC) -shared $(NAME).o $(SONAME) -Wall $(LIBFLAGS) -o $(LIB_DIR)/$@
	ln -s $(LIB_DIR)/lib$(NAME).so.$(VERSION) $(LIB_DIR)/lib$(NAME).so

$(NAME).o: $(SRCS)
	$(CC) -c -fPIC $(INCLUDE_DIR) $(SRCS) -Wall -o $@

clean_obj:
	$(RM) *.o

clean:
	$(RM) *.o *.so*
	$(RM) $(LIB_DIR)/lib$(NAME).so
