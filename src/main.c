#include <stdio.h>
#include <stdlib.h>

#include "gpio_drv.h"

int main()
{
  printf("Hello\n");
  InitGpioOutput(1);
  
  while(1) {
   SetGpioOutput(1);
   sleep(1);
   SetGpioOutput(0);
   sleep(1);
  } 
  return;
}
