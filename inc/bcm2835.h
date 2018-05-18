#ifndef BCMPERIPH_H
#define BCMPERIPH_H

#define BCM2835_PERIPH_BASE 0x3f000000

#define BLOCK_SIZE          (4*1024)

typedef struct {
  uint32_t          _addr_ptr;
  int               _mem_fd;
  void              *_map;
  volatile uint32_t *addr;
} __bcm_periph_s;

extern int  _MapPeripheral  (__bcm_periph_s *p)
extern void _UnmapPeripheral(__bcm_periph_s *p);

#endif //BCMPERIPH_H
