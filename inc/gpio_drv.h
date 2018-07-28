#ifndef GPIO_DRV_H
#define GPIO_DRV_H

#include <stdint.h>

typedef enum {
  RPIO_OUTPUT,
  RPIO_INPUT
} _rpio_cfg_e;

typedef enum {
  LO, HI
} _rpio_val_e;

typedef struct {
  uint8_t     pin;
  _rpio_cfg_e cfg;
  _rpio_val_e val;
} rpio_pin_s;

extern int rpioGpioDriverInit();
extern int rpioInit(rpio_pin_s *p, int pin, _rpio_cfg_e cfg);
extern int rpioSet (rpio_pin_s *p, _rpio_val_e val);
extern int rpioGet (rpio_pin_s *p, _rpio_val_e *val);

/* VERBOSITY LEVELS NOT IMPLEMENTED. */
typedef enum {
  RPIO_VERY_VERBOSE,
  RPIO_VERBOSE,
  RPIO_QUIET
} _rpio_verbose_e;

extern int rpioVerbosity(_rpio_verbose_e v);


#endif //GPIO_DRV_H
