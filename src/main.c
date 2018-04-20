#include <stdio.h>
#include <stdlib.h>

#include "gpio_drv.h"

#define GREEN_PIN 17
#define RED_PIN    4
#define BLUE_PIN  10

int main()
{
  printf("Hello\n");
  int err = 0;

  rpio_pin_s blue_led;
  if (!rpioInit(&blue_led, BLUE_PIN, RPIO_OUTPUT)) {
    printf("Failed to initialize blue_led.\n");
    return -1;
  }

  rpio_pin_s red_led;
  if (!rpioInit(&red_led, RED_PIN, RPIO_OUTPUT)) {
    printf("Failed to initialize red_led.\n");
    return -1;
  }

  rpio_pin_s green_led;
  if (!rpioInit(&green_led, GREEN_PIN, RPIO_OUTPUT)) {
    printf("Failed to initialize green_led.\n");
    return -1;
  }

  while(1) {
    rpioSet(&red_led, HI);
  }
  return 1;
}
