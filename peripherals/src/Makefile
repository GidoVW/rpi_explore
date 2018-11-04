SRCS+=rpio_peripherals.c

MAJOR=0
MINOR=1
PATCH=0
VERSION=$(MAJOR).$(MINOR).$(PATCH)

NAME=rpio_periph
LIBNAME=lib$(NAME).so.$(VERSION)

RM=rm -f

ifndef RPIO_INSTALL_DIR
	INCLUDE_DIR+=-I../../common
	INCLUDE_DIR+=-I../
else
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/common
	INCLUDE_DIR+=-I$(RPIO_INSTALL_DIR)/peripherals
endif

ifdef RPIO_INSTALL_DIR
	LIB_DIR=$(RPIO_INSTALL_DIR)/lib
endif

SONAME=-Wl,-soname,$(LIBNAME)

lib: clean lib$(NAME).so clean_obj

lib$(NAME).so: lib$(NAME).so.$(VERSION)

lib$(NAME).so.$(VERSION): $(NAME).o 
	$(CC) -shared $(NAME).o $(SONAME) -Wall -o $(LIB_DIR)/$@
	ln -s $(LIB_DIR)/lib$(NAME).so.$(VERSION) $(LIB_DIR)/lib$(NAME).so

$(NAME).o: $(SRCS)
	$(CC) -c -fPIC $(INCLUDE_DIR) $(SRCS) $(LIBFLAGS) -Wall -o $@

clean_obj:
	$(RM) *.o

clean:
	$(RM) *.o *.so*
	$(RM) $(LIB_DIR)/lib$(NAME).so
