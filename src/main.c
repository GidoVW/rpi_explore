#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpio_drv.h"
#include "servo.h"

#include "common/rpio_err.h"

#define GREEN_PIN 17
#define RED_PIN    4
#define BLUE_PIN  10
#define PWM_PIN   16

int main()
{
  int period_us = 20000;
  int uptime_us = 1500;
  int downtime_us = period_us - uptime_us;

  int ret = rpioGpioDriverInit();
  if (ret < 0) {
    printf("Error initializing gpio driver.\n");
  }

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
    rpioSet(&green_led, LO);
    usleep(200000);
    rpioSet(&green_led, HI);
    rpioSet(&red_led, LO);
    usleep(200000);
    rpioSet(&red_led, HI);
    rpioSet(&blue_led, LO);
    usleep(200000);
    rpioSet(&blue_led, HI);
  }
  
  return 1;
}
