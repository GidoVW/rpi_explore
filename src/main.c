#include <stdio.h>
#include <stdlib.h>

#include "gpio_drv.h"

static const int green = 17;
static const int red = 4;
static const int blue = 10;

int main()
{
  printf("Hello\n");
  int err = 0;

  rpio_pin_s blue_led;
  if (!rpioInit(&blue_led, 10, RPIO_OUTPUT)) {
    printf("Failed to initialize blue_led.\n");
    return -1;
  }




  while(1) {

  }
  return 1;
}
