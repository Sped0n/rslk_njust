#include "track.h"

uint8_t U1, U2, U3, U4, U5, U6, U7, U8;

void track_init() {
    GPIO_setAsInputPin(GPIO_PORT_P7,
                       GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
}

void track_scan() {
    //打开红外开关
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    //配置输出，为电容充电一段时间
    GPIO_setAsOutputPin(GPIO_PORT_P7,
                        GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7,
                            GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 |
                            GPIO_PIN7);
    delay_us(10);
    //配置为输入，等待电容放电
    GPIO_setAsInputPin(GPIO_PORT_P7,
                       GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    delay_us(500);
    //读取传感器的值
    U1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
    U2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
    U3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
    U4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
    U5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
    U6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
    U7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
    U8 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);
    //关闭红外开关
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
}

// 90 degrees turn
void vertical_left() {
    motor_forward(80);
    while (!(U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0)) {
        track_scan();
    }
    spin_left(80);
    while (U5 != 1) {
        track_scan();
    }
    motor_forward(80);
}

void vertical_right() {
    motor_forward(80);
    while (!(U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0)) {
        track_scan();
    }
    spin_right(80);
    while (U4 != 1) {
        track_scan();
    }
    motor_forward(80);
}

void track() {
    track_scan();

    if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 1 && U5 == 1 && U6 == 0 && U7 == 0 && U8 == 0) {
        motor_forward(80);
    }
    else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0) {

    }
    // crossroad
    else if (U1 == 1 && U2 == 1 && U3 == 1 && U4 == 1 && U5 == 1 && U6 == 1 && U7 == 1 && U8 == 1) {
        motor_forward(80);
    }
    else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 1 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0) {
        motor_left(65, 1.23);
    }
    else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 1 && U6 == 0 && U7 == 0 && U8 == 0) {
        motor_right(65, 1.23);
    }
    else if (U1 == 1 && U2 == 1 && U3 == 1 && U7 == 0 && U8 == 0) {
        vertical_left();
    }
    else if (U6 == 1 && U7 == 1 && U8 == 1 && U1 == 0 && U2 == 0 && U3 == 0) {
        vertical_right();
    }
    else if (U7 == 1 && U6 == 0) {
        motor_right(60, 1.33);
    }
    else if (U2 == 1 && U3 == 0) {
        motor_left(60, 1.33);
    }
    else if (U3 == 1) {
        motor_left(55, 1.45);
    }
    else if (U6 == 1) {
        motor_right(55, 1.45);
    }
    else if (U7 == 1) {
        spin_right(100);
    }
    else if (U2 == 1) {
        spin_left(100);
    }
}
