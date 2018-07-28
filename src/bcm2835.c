#include "bcm2835.h"

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>

#include "common/rpio_err.h"

#define _perr(msg)    _log_err(__FUNCTION__, __LINE__, msg, -1)
#define _psyserr(msg) _log_err(__FUNCTION__, __LINE__, msg, errno)

struct __bcm_periph_s {
  uint32_t          _bcm_hw_addr;
  int               _mem_fd;
  void              *_map;
  volatile uint32_t *virt_addr;
};

/**
 * @name bcmInitPeripheral
 *
 * @brief
 * Initializes the peripheral struct with a hardware address.
 *
 * @param[in] periph the peripheral structure
 * @param[in] hw_addr the hardware address the peripheral is mapped to
 *
 * @return  1  on success
 */
int bcmInitPeripheral(bcm_peripheral_t *periph, uint32_t hw_addr)
{
  *periph = malloc(sizeof(struct __bcm_periph_s));
  if (*periph == NULL) {
    return ERR_DYN_MEM_ALLOC;
  }
  (*periph)->_bcm_hw_addr = hw_addr;
  (*periph)->_mem_fd      = 0;
  (*periph)->_map         = NULL;
  (*periph)->virt_addr    = NULL;
  return 1; 
}

/**
 * @name bcmMapPeripheral
 *
 * @brief
 * Maps the peripheral address space to the process address space
 *
 * @param[in] periph the peripheral structure (needs to be initialized)
 *
 * @return  1  on success
 *          -1 on error
 */
int bcmMapPeripheral(bcm_peripheral_t p)
{
  int ret = -1;

  p->_mem_fd = open("/dev/gpiomem", O_SYNC|O_RDWR);
  if (p->_mem_fd < 0) {
    _psyserr("open /dev/gpiomem");
    return 0;
  } 
  else {
    p->_map = mmap(NULL,
                  BLOCK_SIZE,
                  PROT_READ|PROT_WRITE,
                  MAP_SHARED,
                  p->_mem_fd,
                  p->_bcm_hw_addr);

    if (p->_map != MAP_FAILED) {
      p->virt_addr = (volatile uint32_t *)p->_map;
      ret = 1;
    } 
    else {
      _psyserr("mmap");
    }
  }

  return ret;
}

/**
 * @name bcmUnmapPeripheral
 *
 * @brief
 * Unmaps and closes the address space and associated mapped files.
 *
 * @param[in] periph the peripheral structure (needs to be initialized)
 *
 * @return  void
 */
void bcmUnmapPeripheral(bcm_peripheral_t p)
{
  munmap(p->_map,
         BLOCK_SIZE);
  close(p->_mem_fd);
}


/**
 * @name bcmGetVirtualAddress
 *
 * @brief
 * Unmaps and closes the address space and associated mapped files.
 *
 * @param[in] periph the peripheral structure (needs to be initialized)
 *
 * @return  void
 */
void bcmGetVirtualAddress(bcm_peripheral_t p, uint32_t *base_virt_addr)
{
  *base_virt_addr = p->virt_addr;
}

void _log_err(const char *func, const int line, char *msg, int errnum)
{
  if (errnum < 0)
    fprintf(stderr, "%s:%d: %s\n", func, line, msg);
  else
    fprintf(stderr, "%s:%d: %s: %s\n", func, line, msg, strerror(errnum));
}
