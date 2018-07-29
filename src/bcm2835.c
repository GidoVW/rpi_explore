#include "bcm2835.h"

#include <stdio.h>
#include <stdlib.h>
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
 * Allocates memory accordingly.
 *
 * @param[in] p the peripheral structure
 * @param[in] hw_addr the hardware address the peripheral is mapped to
 *
 * @return  RPIOERR_OK          success
 *          RPIOERR_DYN_ALLOC   memory allocation fault
 */
int bcmInitPeripheral(bcm_peripheral_t *p, uint32_t hw_addr)
{
  *p = malloc(sizeof(struct __bcm_periph_s));
  if (*p == NULL) {
    return RPIOERR_DYN_ALLOC;
  }

  (*p)->_bcm_hw_addr = hw_addr;
  (*p)->_mem_fd      = 0;
  (*p)->_map         = NULL;
  (*p)->virt_addr    = NULL;

  return RPIOERR_OK; 
}

/**
 * @name bcmMapPeripheral
 *
 * @brief
 * Maps the peripheral address space to the process address space
 *
 * @param[in] p the peripheral structure (needs to be initialized)
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
 * @param[in] p the peripheral structure (needs to be initialized)
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
 * @param[in]  p the peripheral structure (needs to be initialized)
 * @param[out] base_virt_addr the virtual base address of the peripheral p
 *
 * @return  RPIOERR_OK      success
 *          RPIOERR_NINIT   peripheral structure not initialized
 */
int bcmGetVirtualAddress(bcm_peripheral_t p, uint32_t **base_virt_addr)
{
  if (p != NULL)
  {
    *base_virt_addr = (uint32_t *)p->virt_addr;
    return RPIOERR_OK;
  }
  return RPIOERR_NINIT;
}

void _log_err(const char *func, const int line, char *msg, int errnum)
{
  if (errnum < 0)
    fprintf(stderr, "%s:%d: %s\n", func, line, msg);
  else
    fprintf(stderr, "%s:%d: %s: %s\n", func, line, msg, strerror(errnum));
}
