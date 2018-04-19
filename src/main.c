#include <stdio.h>
#include <stdlib.h>

#include "gpio_drv.h"

static const int green_led = 17;
static const int red_led = 4;
static const int blue_led = 10;

int main()
{
  int led = 17;
  printf("Hello\n");
  InitGpioOutput(led);

  SetGpioOutput(led, 0);

  
  while(1) {
    printf("Led..\n");
    SetGpioOutput(led, 1);
    sleep(1);
    SetGpioOutput(led, 0);
    sleep(1);
  } 
  return;
}
