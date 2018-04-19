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

#include <unistd.h>

struct BcmPeriph gpio = {GPIO_BASE, 0, NULL, NULL};

int MapPeripheral(struct BcmPeriph *p)
{
  int ret = -1;
  p->mem_fd = open("/dev/gpiomem", O_SYNC|O_RDWR); 
  if (p->mem_fd < 0) {
    printf("Failed to open /dev/gpiomem\n");
    perror("open");
  } else {
    p->map = mmap(NULL,
                  BLOCK_SIZE,
                  PROT_READ|PROT_WRITE,
                  MAP_SHARED,
                  p->mem_fd,
                  p->addr_ptr);

    if (p->map != MAP_FAILED) {
      p->addr = (volatile uint32_t *)p->map;
      printf("Mapped address: %d, value %d\n", p->addr, *(p->addr));
      ret = 1;
    } else {
      printf("MAP FAILED.\n");
      perror("mmap");
    }
  }

  return ret;
}

void UnmapPeripheral(struct BcmPeriph *p)
{
  munmap(p->map,
         BLOCK_SIZE);
  close(p->mem_fd);
}

int InitGpioOutput(int pin)
{
  if(!MapPeripheral(&gpio)) {
    return -1;
  }
  int reg_off = pin/10;
  printf("pin: %d, reg_off: %d, shift %d\n", pin, reg_off, (pin%10)*3);
  *(gpio.addr + reg_off) ^= 1 << (pin % 10)*3;
  UnmapPeripheral(&gpio);
  return 1;
}

int SetGpioOutput(int pin, int val)
{
  if(!MapPeripheral(&gpio)) {
    return -1;
  }
  int reg_off;
  if (pin >= 0  && pin < 32) reg_off = 0;
  if (pin >= 32 && pin < 64) reg_off = 1; 
  printf("pin %d, val %d\n", pin, val);
  if (val == 1) {
    *(gpio.addr+7+reg_off) = (1 << pin);
  } else {
    *(gpio.addr+10+reg_off) = (1 << pin);
  }
  UnmapPeripheral(&gpio);
  return 1;
}

