/**
 * Brown:  GND
 * Red:    VDD
 * Orange: PWM
 *
 * Period 20ms / 50Hz
 * VDD = 5V
 *
 * Duty Cycle & Position:
 * 1ms pulse   : position -90
 * 1.5ms pulse : position   0
 * 2ms pulse   : position  90 
 */

/*
 * BCM Pin 16
 */


#ifndef SERVO_H
#define SERVO_H

#include "gpio_drv.h"

int ServoInit(rpio_pin_s *pwm_pin, int pin_nb);
uint32_t AngleToUptime(int angle);

#endif //SERVO_H
