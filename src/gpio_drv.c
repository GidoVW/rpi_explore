/**
 * @filename src/gpio_drv.c
 * @author:  Gido van Wijk
 * @date:    Feb 2018
 * @brief
 *
 * @changes
 * 12/02/18 - First version
 **/

#include "gpio_drv.h"

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <unistd.h>

struct BcmPeriph gpio = {GPIO_BASE};

int MapPeripheral(struct BcmPeriph *p)
{
  int ret = 0;
  p->mem_fd = open("/dev/mem", O_SYNC|O_RDWR); 
  if (p->mem_fd < 0) {
    printf("Failed to open /dev/mem\n");
    perror("open");
  } else {
    printf("File Descriptor: %d\n", p->mem_fd); 
    p->map = (char*)mmap(NULL,
                  BLOCK_SIZE,
                  PROT_READ|PROT_WRITE,
                  MAP_SHARED,
                  p->mem_fd,
                  p->addr_ptr);

    if (p->map != MAP_FAILED) {
      p->addr = (volatile uint32_t *)p->map;
      printf("Mapped address: %d\n", *(p->addr));
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

  if(MapPeripheral(&gpio)) {
    *(gpio.addr+GPSET0) = gpio_nb << 4;
    UnmapPeripheral(&gpio);
    ret = 1; 
  } else {
    printf("Error somehow\n");
  }
  return ret;
}

