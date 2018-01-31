#include <stdio.h>
#include <stdlib.h>

#include "gpio_drv.h"

int main()
{
  printf("Hello\n");
  SetGpioOutput(1);
  return;
}
