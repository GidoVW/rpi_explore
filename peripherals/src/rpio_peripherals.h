#ifndef _RPIO_PERIPHERALS_H
#define _RPIO_PERIPHERALS_H

#include "bcm2835/bcm2835.h"
#include <stdint.h>

#define BLOCK_SIZE          (4*1024)

typedef struct __rpio_periph_s *rpio_periph_t;

/************************************
 *          GPIO REGISTERS          *
 ************************************/

/*

	EXAMPLE:

	Let's say you want to access GPFSEL1.
	First, as there is an OS layer, you need to mmap the
	memory region you want to access. This is done through API:

			int bcmMapPeripheral (bcm_peripheral_t p);

    that is initialized using 

            int bcmInitPeripheral();
			
	This will in turn give you 

			._map 		: void pointer to mapped area
			.virt_addr	: non-void pointer to mapped area

	Using the pointer to the mapped area, you can translate
	that into the struct defined below to easily access
	byte fields:

			__bcm_periph_s gpio_periph;
			GPIO *mygpio;

			mygpio = (GPIO *)gpio_periph._map;

	Finally,

			mygpio.GPFSEL1.FIELD.FSEL4 = 0b001;

*/

extern int  rpio_init_peripheral(rpio_periph_t *p, 
	                          uint32_t         hw_addr);

extern int rpio_get_virt_addr(rpio_periph_t p, 
	                            uint32_t         **base_virt_addr);

extern int  rpio_map_peripheral(rpio_periph_t p);
extern void rpio_unmap_peripheral(rpio_periph_t p);

extern void _log_err(const char *func, const int line, char *msg, int errnum);

#endif //_RPIO_PERIPHERALS_H
