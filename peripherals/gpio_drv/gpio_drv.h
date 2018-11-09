#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include <stdint.h>

typedef enum {
  GPIO_OUTPUT,
  GPIO_INPUT
} gpio_cfg_e;

typedef enum {
  GPIO_LOW, 
  GPIO_HIGH
} gpio_val_e;

// Device needs to be opened & closed to use methods.
extern int rpio_gpio_open();
extern int rpio_gpio_close();

/* Stand-alone methods */
extern int rpio_gpio_set_cfg(uint32_t pin, gpio_cfg_e cfg);
extern int rpio_gpio_set_val(uint32_t pin, gpio_val_e val);
extern int rpio_gpio_get_val(uint32_t pin, gpio_val_e* val);

#endif //GPIO_DRV_H
