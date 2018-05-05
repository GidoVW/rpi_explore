#include "servo.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "gpio_drv.h"

#define SERVO_FAILURE -1
#define SERVO_SUCCESS  0

#define SERVO_PWM_PIN 16

#define FREQ_HZ   50
#define PERIOD_US 20000

#define RIGHT_POS_US  1000
#define MIDDLE_POS_US 1500
#define LEFT_POS_US   2000


/*
 *  -90         0         90
 *   1ms       1.5ms      2ms
 */
const int full_angle = 90;
const int full_angle_to_ref_us = 500;

static uint32_t uptime_us = 0;
static uint32_t downtime_us = 0;

int ServoInit(rpio_pin_s *pwm_pin, int pin_nb)
{
  int ret = 0;
  
  ret = rpioInit(pwm_pin,
                 pin_nb,
                 RPIO_OUTPUT);
  if (ret < 0) {
    fprintf(stderr, "Error initializing servo PWM pin.\n");
    return SERVO_FAILURE;
  }
}

/**
 * @name AngleToUptime
 * @brief Calculates the uptime in us for the desired angle
 * @param[in] angle [-90 ; 90]
 * @return On success: uptime in microseconds based on 50Hz signal
 *         On failure: -1 
 */
uint32_t AngleToUptime(int angle)
{
  if ((angle < -90) || (angle > 90)) {
    fprintf(stderr, "Angle should be in range [-90;90].\n");
    return -1;
  }
  return (uint32_t)(MIDDLE_POS_US+((angle)*full_angle_to_ref_us/full_angle));
}
  

