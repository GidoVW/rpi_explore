SUBDIRS+=peripherals

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

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

test:
	make -C sample/