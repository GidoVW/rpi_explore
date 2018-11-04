SRCS+=src/*.c
INCLUDES+=inc/
INCLUDES+=peripherals/

SUBDIRS+=peripherals

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

ARCH=$(shell arch)
RPIO_INSTALL_DIR=$(shell pwd)
export RPIO_INSTALL_DIR

ifeq ($(ARCH),x86_64)
  CC=arm-linux-gnueabi-gcc
else
  CC=gcc
endif

export CC

all: subdirs


