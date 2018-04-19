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

int InitGpioOutput(int gpio_nb)
{
  int ret = 0;

  if(MapPeripheral(&gpio)) {
    printf("Current config: %d\n", *(gpio.addr));
    *(gpio.addr) = 0;
    *(gpio.addr) = 1 << 12;
    UnmapPeripheral(&gpio);
    ret = 1;
  } else {
    printf("InitGpioOutput: Error.\n");
  }
  return ret;
}

int SetGpioOutput(int gpio_nb)
{
  int ret = 0;
  int current_val = 0;

  if(MapPeripheral(&gpio)) {
    current_val = *(gpio.addr+13);
    printf("Current value of pin is:  %d\n", current_val);
    if (gpio_nb == 1) {
      printf("Setting bit, current val: %d\n", *(gpio.addr+7));
      *(gpio.addr+7) = (1 << 4);
    } else if (gpio_nb == 0) {
      printf("Clearing bit, current val: %d\n", *(gpio.addr+10));
      *(gpio.addr+10) = (1 << 4);
    }
    UnmapPeripheral(&gpio);
    ret = 1; 
  } else {
    printf("Error somehow\n");
  }
  return ret;
}

