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

#define BLOCK_SIZE          (4*1024)

#define _err(msg)    _log_err(__FUNCTION__, __LINE__, msg, -1)
#define _syserr(msg) _log_err(__FUNCTION__, __LINE__, msg, errno)

/* Mapping */
static int _InitRpioIO(int pin, _rpio_cfg_e cfg);

static rpio_periph_t gpio;

int rpioGpioDriverInit() {
  return rpio_init_peripheral(&gpio, GPIO_BASE);
}

int rpioInit(rpio_pin_s *p, int pin, _rpio_cfg_e cfg)
{
  if (p == NULL) {
    _err("NULL arguments"); 
    return 0;
  }

  int ret;

  p->pin = pin;
  p->cfg = cfg;

  ret = _InitRpioIO(pin, cfg);
  if (ret == RPIOERR_WRONG_CFG) {
    _err("Available cfg options: RPIO_OUTPUT RPIO_INPUT");
    return 0;
  } else if (ret == RPIOERR_MAP_FAIL) {
    return 0;
  }

  return 1;
}

int rpioSet(rpio_pin_s *p, _rpio_val_e val)
{
  uint32_t *base_addr = NULL;
  if(p == NULL) {
    _err("NULL arguments");
    return 0;
  }
  if(p->cfg != RPIO_OUTPUT) {
    _err("cfg is not RPIO_OUTPUT");
    return 0;
  }
  if(!rpio_map_peripheral(gpio)) {
    return 0;
  }
  rpio_get_virt_addr(gpio, &base_addr);

  int reg_off, pin = p->pin;
  if (pin >= 0  && pin <= 31) reg_off = 0;
  if (pin >= 32 && pin <= 53) reg_off = 1;
  if (pin > 53) {
    _err("pin should be < 53");
    return 0;
  }
  if (val == HI) {
    *(base_addr+7+reg_off) = (1 << pin);
  } else if (val == LO) {
    *(base_addr+10+reg_off) = (1 << pin);
  }
  rpio_unmap_peripheral(gpio);
  p->val = val;
  return 1;
}

int rpioGet(rpio_pin_s *p, _rpio_val_e *val)
{
  uint32_t *base_addr = NULL;
  if(p == NULL) {
    _err("NULL arguments");
    return 0;
  }
  if(p->cfg != RPIO_INPUT) {
    _err("cfg is not RPIO_INPUT");
    return 0;
  }
  if(!rpio_map_peripheral(gpio)) {
    return 0;
  }
  rpio_get_virt_addr(gpio, &base_addr);

  int rd, reg_off, pin = p->pin;
  if (pin >= 0  && pin <= 31) reg_off = 0;
  if (pin >= 32 && pin <= 53) reg_off = 1;
  if (pin > 53) {
    _err("pin should be < 53");
    return 0;
  }

  rd = *(base_addr+13+reg_off);
  rd &= 1 << pin;
  if (rd) {
    *val   = HI;
    p->val = HI;
  } else {
    *val   = LO;
    p->val = LO;
  }
  rpio_unmap_peripheral(gpio);
  return 1;
}


/**
 * RPIO TOOLBOX
 */

 static int _InitRpioIO(int pin, _rpio_cfg_e cfg)
 {
   uint32_t *base_addr = NULL;
   if(!rpio_map_peripheral(gpio)) {
     return RPIOERR_MAP_FAIL;
   }
   rpio_get_virt_addr(gpio, &base_addr);
   int bits;
   switch(cfg) {
     case RPIO_OUTPUT:
       bits = 0b001;
       break;
     case RPIO_INPUT:
       bits = 0b000;
       break;
     default:
       return RPIOERR_WRONG_CFG;
   }
   int reg_off = pin/10;
   printf("pin: %d, reg_off: %d, shift %d\n", pin, reg_off, (pin%10)*3);
   *(base_addr + reg_off) &= ~(0b111 << (pin % 10)*3);
   *(base_addr + reg_off) |= (bits << (pin % 10)*3);
   rpio_unmap_peripheral(gpio);
   return 1;
 }


