/**
 * @filename src/gpio_drv.c
 * @author:  Gido van Wijk
 * @date:    Feb 2018
 * @brief
 *
 * @changes
 * 12/02/18 - First version
 * 22/02/18 - Added set/clear registers
 * 25/03/18 - Further improvements and debugging
 **/

#include "gpio_drv.h"

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>

#include "bcm2835/bcm2835.h"
#include "rpio_peripherals.h"
#include "rpio_err.h"

#define _err(msg)    _log_err(__FUNCTION__, __LINE__, msg, -1)
#define _syserr(msg) _log_err(__FUNCTION__, __LINE__, msg, errno)

typedef enum {
  GPIO_OPEN,
  GPIO_CLOSE,
  GPIO_READ,
  GPIO_WRITE
} gpio_operation_e;

static int gpio(gpio_operation_e op, uint32_t reg_offset, uint32_t *data) 
{
  static rpio_periph_s gpio = {GPIO_BASE, 0, NULL, NULL};

  if (data == NULL && (op == GPIO_READ || op == GPIO_WRITE))
    return INVAL_ARGS;

  if (op != GPIO_OPEN && gpio.map == NULL)
    return DEV_NOT_OPEN;

  int ret = 0;
  uint32_t *base_addr = NULL;

  switch (op) {

    case GPIO_OPEN:

      if (gpio.map != NULL) {
        return EOK;
      }
      return rpio_map_peripheral(&gpio);

    case GPIO_CLOSE:
    
      if (gpio.map == NULL) {
        return EOK;
      }
      rpio_unmap_peripheral(&gpio);
      return EOK;

    case GPIO_READ:
      *data = *(gpio.virt_addr + reg_offset);
      return EOK;

    case GPIO_WRITE:
      *(gpio.virt_addr + reg_offset) = *data;
      return EOK;

    default:
      printf("Fatal gpio operation\n");
      return INVAL_ARGS;
  }
}


int rpio_gpio_open()
{
  gpio(GPIO_OPEN, 0, NULL);
}

int rpio_gpio_close()
{
  gpio(GPIO_CLOSE, 0, NULL);
}

static int gpio_read(uint32_t addr, uint32_t *data) {
  int offset = addr - GPIO_BASE;
  return gpio(GPIO_READ, offset, data);
}

static int gpio_write(uint32_t addr, uint32_t data) {
  return gpio(GPIO_WRITE, addr, data);
}

int rpio_gpio_set_cfg(uint32_t pin, gpio_cfg_e cfg)
{
  int reg = 0;
  gpio_write(reg, cfg);
}

int rpio_gpio_set_val(uint32_t pin, gpio_val_e val)
{
  int reg_off;
  
  if (pin >= 0  && pin <= 31) reg_off = 0;
  if (pin >= 32 && pin <= 53) reg_off = 1;
  if (pin > 53) {
    _err("pin should be < 53");
    return INVAL_ARGS;
  }

  return EOK;
}

int rpio_gpio_get_val(uint32_t pin, gpio_val_e *val)
{
  if(val == NULL) {
    _err("NULL arguments");
    return INVAL_ARGS;
  }

  int reg_off;

  if (pin >= 0  && pin <= 31) reg_off = 0;
  if (pin >= 32 && pin <= 53) reg_off = 1;
  if (pin > 53) {
    _err("pin should be < 53");
    return INVAL_ARGS;
  }

//  int rd = *(base_addr+13+reg_off);
  return EOK;
}


/**
 * RPIO TOOLBOX
 */
//  int reg_off = pin/10;
  

//   *(base_addr + reg_off) &= ~(0b111 << (pin % 10)*3);
//   *(base_addr + reg_off) |= (bits << (pin % 10)*3);


