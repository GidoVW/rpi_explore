#ifndef BCMPERIPH_H
#define BCMPERIPH_H

#include <stdint.h>

#define BCM2835_PERIPH_BASE 0x3f000000

#define BLOCK_SIZE          (4*1024)

typedef struct {
  uint32_t          _bcm_hw_addr;
  int               _mem_fd;
  void              *_map;
  volatile uint32_t *virt_addr;
} __bcm_periph_s;

extern int  _MapPeripheral  (__bcm_periph_s *p);
extern void _UnmapPeripheral(__bcm_periph_s *p);

extern void _log_err(const char *func, const int line, char *msg, int errnum);

#endif //BCMPERIPH_H
