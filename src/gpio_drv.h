#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include <stdint.h>

#define BCM2835_PERIPH_BASE 0x20000000
#define GPIO_OFFSET         0x00200000
#define GPIO_BASE           (BCM2835_PERIPH_BASE + GPIO_OFFSET)

#define BLOCK_SIZE          (4*1024)

struct Bcm2835Peripheral {
  uint32_t addr_ptr;
  int mem_fd;
  char     *map;
  volatile uint32_t *addr;
};

#endif //GPIO_DRV_H
