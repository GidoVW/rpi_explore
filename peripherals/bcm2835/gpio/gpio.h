#ifndef _BCM2835_GPIO_H
#define _BCM2835_GPIO_H

#include <stdint.h>

#define GPIO_OFFSET         0x00200000
#define GPIO_BASE           (BCM2835_PERIPH_BASE + GPIO_OFFSET)

#define BCM2835_NB_GPIO_PINS	53

/*****************************************

	REGISTER MAPPINGS

 *****************************************/

#define GPFSEL0_OFFSET	0
#define GPFSEL0_ADDR 	GPIO_BASE + GPFSEL0_OFFSET
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
} GPFSEL0_REG;

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
} GPFSEL1_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL20:3;
		uint32_t FSEL21:3;
		uint32_t FSEL22:3;
		uint32_t FSEL23:3;
		uint32_t FSEL24:3;
		uint32_t FSEL25:3;
		uint32_t FSEL26:3;
		uint32_t FSEL27:3;
		uint32_t FSEL28:3;
		uint32_t FSEL29:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL2_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL30:3;
		uint32_t FSEL31:3;
		uint32_t FSEL32:3;
		uint32_t FSEL33:3;
		uint32_t FSEL34:3;
		uint32_t FSEL35:3;
		uint32_t FSEL36:3;
		uint32_t FSEL37:3;
		uint32_t FSEL38:3;
		uint32_t FSEL39:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL3_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL40:3;
		uint32_t FSEL41:3;
		uint32_t FSEL42:3;
		uint32_t FSEL43:3;
		uint32_t FSEL44:3;
		uint32_t FSEL45:3;
		uint32_t FSEL46:3;
		uint32_t FSEL47:3;
		uint32_t FSEL48:3;
		uint32_t FSEL49:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL4_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t FSEL50:3;
		uint32_t FSEL51:3;
		uint32_t FSEL52:3;
		uint32_t FSEL53:3;
		uint32_t FSEL54:3;
		uint32_t FSEL55:3;
		uint32_t FSEL56:3;
		uint32_t FSEL57:3;
		uint32_t FSEL58:3;
		uint32_t FSEL59:3;
		uint32_t :2;       /* reserved */
	} FIELD;
} GPFSEL5_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t SET0:1;
		uint32_t SET1:1;
		uint32_t SET2:1;
		uint32_t SET3:1;
		uint32_t SET4:1;
		uint32_t SET5:1;
		uint32_t SET6:1;
		uint32_t SET7:1;
		uint32_t SET8:1;
		uint32_t SET9:1;
		uint32_t SET10:1;
		uint32_t SET11:1;
		uint32_t SET12:1;
		uint32_t SET13:1;
		uint32_t SET14:1;
		uint32_t SET15:1;
		uint32_t SET16:1;
		uint32_t SET17:1;
		uint32_t SET18:1;
		uint32_t SET19:1;
		uint32_t SET20:1;
		uint32_t SET21:1;
		uint32_t SET22:1;
		uint32_t SET23:1;
		uint32_t SET24:1;
		uint32_t SET25:1;
		uint32_t SET26:1;
		uint32_t SET27:1;
		uint32_t SET28:1;
		uint32_t SET29:1;
		uint32_t SET30:1;
		uint32_t SET31:1;
	} FIELD;
} GPSET0_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t SET32:1;
		uint32_t SET33:1;
		uint32_t SET34:1;
		uint32_t SET35:1;
		uint32_t SET36:1;
		uint32_t SET37:1;
		uint32_t SET38:1;
		uint32_t SET39:1;
		uint32_t SET40:1;
		uint32_t SET41:1;
		uint32_t SET42:1;
		uint32_t SET43:1;
		uint32_t SET44:1;
		uint32_t SET45:1;
		uint32_t SET46:1;
		uint32_t SET47:1;
		uint32_t SET48:1;
		uint32_t SET49:1;
		uint32_t SET50:1;
		uint32_t SET51:1;
		uint32_t SET52:1;
		uint32_t SET53:1;
		uint32_t :10; /* reserved */
	} FIELD;
} GPSET1_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t CLR0:1;
		uint32_t CLR1:1;
		uint32_t CLR2:1;
		uint32_t CLR3:1;
		uint32_t CLR4:1;
		uint32_t CLR5:1;
		uint32_t CLR6:1;
		uint32_t CLR7:1;
		uint32_t CLR8:1;
		uint32_t CLR9:1;
		uint32_t CLR10:1;
		uint32_t CLR11:1;
		uint32_t CLR12:1;
		uint32_t CLR13:1;
		uint32_t CLR14:1;
		uint32_t CLR15:1;
		uint32_t CLR16:1;
		uint32_t CLR17:1;
		uint32_t CLR18:1;
		uint32_t CLR19:1;
		uint32_t CLR20:1;
		uint32_t CLR21:1;
		uint32_t CLR22:1;
		uint32_t CLR23:1;
		uint32_t CLR24:1;
		uint32_t CLR25:1;
		uint32_t CLR26:1;
		uint32_t CLR27:1;
		uint32_t CLR28:1;
		uint32_t CLR29:1;
		uint32_t CLR30:1;
		uint32_t CLR31:1;
	} FIELD;
} GPCLR0_REG;

typedef union {
	uint32_t REG;
	struct {
		uint32_t CLR32:1;
		uint32_t CLR33:1;
		uint32_t CLR34:1;
		uint32_t CLR35:1;
		uint32_t CLR36:1;
		uint32_t CLR37:1;
		uint32_t CLR38:1;
		uint32_t CLR39:1;
		uint32_t CLR40:1;
		uint32_t CLR41:1;
		uint32_t CLR42:1;
		uint32_t CLR43:1;
		uint32_t CLR44:1;
		uint32_t CLR45:1;
		uint32_t CLR46:1;
		uint32_t CLR47:1;
		uint32_t CLR48:1;
		uint32_t CLR49:1;
		uint32_t CLR50:1;
		uint32_t CLR51:1;
		uint32_t CLR52:1;
		uint32_t CLR53:1;
		uint32_t :10; /* reserved */
	} FIELD;
} GPCLR1_REG;

/*****************************************

	PERIPHERAL MAPPING

 *****************************************/

typedef struct {
	
	GPFSEL0_REG GPFSEL0;
	GPFSEL1_REG GPFSEL1;
	GPFSEL2_REG GPFSEL2;
	GPFSEL3_REG GPFSEL3;
	GPFSEL4_REG GPFSEL4;
	GPFSEL5_REG GPFSEL5;
	uint32_t;
	GPSET0_REG GPSET0;
	GPSET1_REG GPSET1;
	uint32_t;
	GPCLR0_REG GPCLR0;
	GPCLR1_REG GPCLR1;
	uint32_t;
	//GPLEV0
	//GPLEV1
	uint32_t;
	//GPEDS0
	//GPEDS1
	uint32_t;
	//GPREN0
	//GPREN1
	uint32_t;
	//GPFEN0
	//GPFEN1
	uint32_t;
	//GPHEN0
	//GPHEN1
	uint32_t;
	//GPLEN0
	//GPLEN1
	uint32_t;
	//GPAREN0
	//GPAREN1
	uint32_t;
	//GPAFEN0
	//GPAFEN1
	uint32_t;
	//GPPUD
	//GPPUDCLK0
	//GPPUDCLK1
	uint32_t;

} GPIO;



#endif //_BCM2835_GPIO_H
