#include "motor.h"

void motor_init(void) {
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN7);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);

    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN7);

    Timer_A_PWMConfig TIMA0_PWMConfig;
    TIMA0_PWMConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    TIMA0_PWMConfig.clockSourceDivider = 6;
    TIMA0_PWMConfig.timerPeriod = 19999;
    TIMA0_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    TIMA0_PWMConfig.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
    TIMA0_PWMConfig.dutyCycle = 9999;

    Timer_A_generatePWM(TIMER_A0_BASE, &TIMA0_PWMConfig);
    TIMA0_PWMConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
    Timer_A_generatePWM(TIMER_A0_BASE, &TIMA0_PWMConfig);
}

void motor_start() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
}

void motor_stop() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);
}

void motor_forward(uint8_t speed) {
    // max speed = 100
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);
    if (speed > 100) {
        speed = 100;
    }
    uint32_t real_speed = floor((speed / 100.0) * 9999);
    if (real_speed > 9999) {
        real_speed = 9999;
    }
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, real_speed);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, real_speed);

}

void motor_backward(uint8_t speed) {
    // max speed = 100
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
    if (speed > 100) {
        speed = 100;
    }
    uint32_t real_speed = floor((speed / 100.0) * 9999);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, real_speed);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, real_speed);
}

void motor_right(uint8_t speed, double_t ratio) {
    // max speed = 100, ratio > 1
    // speed is the slow side speed
    // fast side speed = ratio x speed
    // 3 for right, 4 for left
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);
    if (ratio < 1.0){
        ratio = 1.0;
    }
    if (speed > 100) {
        speed = 100;
    }
    uint32_t slow_side = floor((speed / 100.0) * 9999);
    uint32_t fast_side = floor(slow_side * ratio);
    if (fast_side > 9999) {
        fast_side = 9999;
        slow_side = floor(fast_side / ratio);
    }
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, slow_side);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, fast_side);
}

void motor_left(uint8_t speed, double_t ratio) {
    // max speed = 100, ratio > 1
    // speed is the slow side speed
    // fast side speed = ratio x speed
    // 3 for right, 4 for left
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);
    if (ratio < 1.0){
        ratio = 1.0;
    }
    if (speed > 100) {
        speed = 100;
    }
    uint32_t slow_side = floor((speed / 100.0) * 9999);
    uint32_t fast_side = floor(slow_side * ratio);
    if (fast_side > 9999) {
        fast_side = 9999;
        slow_side = floor(fast_side / ratio);
    }
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, fast_side);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, slow_side);
}

void spin_right(uint8_t speed) {
    // max speed = 100, ratio > 1
    // speed is the slow side speed
    // fast side speed = ratio x speed
    // 3 for right, 4 for left
    if (speed > 100) {
        speed = 100;
    }
    uint32_t real_speed = floor((speed / 100.0) * 9999);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_3, real_speed);
    Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, real_speed);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN7);
}

void spin_left(uint8_t speed) {
    // max speed = 100, ratio > 1
    // speed is the slow side speed
    // fast side speed = ratio x speed
    // 3 for right, 4 for left
    if (speed > 100) {
        speed = 100;
    }
    uint32_t real_speed = floor((speed / 100.0) * 9999);
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6);
}
