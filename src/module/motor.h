#ifndef RSLK_MOTOR_H
#define RSLK_MOTOR_H

#include "../../../../.platformio/packages/framework-energiamsp432r/system/source/ti/devices/msp432p4xx/driverlib/driverlib.h"
#include <math.h>

void motor_init();
void motor_start();
void motor_stop();
void motor_forward(uint8_t speed);
void motor_backward(uint8_t speed);
void motor_right(uint8_t speed, double_t ratio);
void motor_left(uint8_t speed, double_t ratio);
void spin_right(uint8_t speed);
void spin_left(uint8_t speed);

#endif //RSLK_MOTOR_H
