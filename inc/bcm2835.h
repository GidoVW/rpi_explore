#ifndef BCMPERIPH_H
#define BCMPERIPH_H

#include <stdint.h>

#define BCM2835_PERIPH_BASE 0x3f000000
#define GPIO_OFFSET         0x00200000

#define GPIO_BASE           (BCM2835_PERIPH_BASE + GPIO_OFFSET)

#define GPFSEL0_OFFSET      0 
#define GPSET0              7
#define GPCLR0              10
#define GPLEV0              13

#define BLOCK_SIZE          (4*1024)

typedef struct {
  uint32_t          _bcm_hw_addr;
  int               _mem_fd;
  void              *_map;
  volatile uint32_t *virt_addr;
} __bcm_periph_s;


/************************************
 *          GPIO REGISTERS          *
 ************************************/

/*

	EXAMPLE:

	Let's say you want to access GPFSEL1.
	First, as there is an OS layer, you need to mmap the
	memory region you want to access. This is done through API:

			int _MapPeripheral (__bcm_periph_s *p);

	you have to provide:	

			._bcm_hw_addr 	= GPIO_BASE,
			._mem_fd      	= open(/dev/gpiomem, ...),
			
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

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL0:3;
		uint32_t FSEL1:3;
		uint32_t FSEL2:3;
		uint32_t FSEL3:3;
		uint32_t FSEL4:3;
		uint32_t FSEL5:3;
		uint32_t FSEL6:3;
		uint32_t FSEL7:3;
		uint32_t FSEL8:3;
		uint32_t FSEL9:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL0;

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL10:3;
		uint32_t FSEL11:3;
		uint32_t FSEL12:3;
		uint32_t FSEL13:3;
		uint32_t FSEL14:3;
		uint32_t FSEL15:3;
		uint32_t FSEL16:3;
		uint32_t FSEL17:3;
		uint32_t FSEL18:3;
		uint32_t FSEL19:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL1;

typedef struct {
	
	GPFSEL0 gpfsel0_reg;
	GPFSEL1 gpfsel1_reg;

} GPIO;

extern int  _MapPeripheral  (__bcm_periph_s *p);
extern void _UnmapPeripheral(__bcm_periph_s *p);

extern void _log_err(const char *func, const int line, char *msg, int errnum);

#endif //BCMPERIPH_H
