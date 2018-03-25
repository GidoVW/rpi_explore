#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include <stdint.h>

#define BCM2835_PERIPH_BASE 0x7e000000
#define GPIO_OFFSET         0x00200000
#define GPIO_BASE           (BCM2835_PERIPH_BASE + GPIO_OFFSET)
#define GPSET0              7
#define GPCLR0              10
#define GPLEV0              13

#define BLOCK_SIZE          (4*1024)

struct BcmPeriph {
  uint32_t          addr_ptr;
  int               mem_fd;
  void              *map;
  volatile uint32_t *addr;
};

#endif //GPIO_DRV_H
