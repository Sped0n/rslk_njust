#include "track.h"

#define vert_delay 350

uint8_t U1, U2, U3, U4, U5, U6, U7, U8;

void track_init() {
    GPIO_setAsInputPin(GPIO_PORT_P7,
                       GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    LED_init();
    CLK_init();
    SysTick_Init();
    MAP_FPU_enableModule();
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
    delay_us(1000);

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
    motor_forward(30);
    int i = 0;
    while (!(U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0)) {
        track_scan();
        if (U2 == 1 && (U3 == 1 || U6 == 1) && U8 == 1) {
            i = vert_delay;
            break;
        }
        i++;
        if (i >= vert_delay) {
            break;
        }
    }
    if (i < vert_delay) {
        spin_left(75);
        while (U4 != 1) {
            track_scan();
        }
        motor_forward(10);
    }
}

void vertical_right() {
    motor_forward(30);
    int i = 0;
    while (!(U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0)) {
        track_scan();
        if (U2 == 1 && (U3 == 1 || U6 == 1) && U8 == 1) {
            i = vert_delay;
            break;
        }
        i++;
        if (i >= vert_delay) {
            break;
        }
    }
    if (i < vert_delay) {
        spin_right(75);
        while (U4 != 1) {
            track_scan();
        }
        motor_forward(10);
    }
}

void track() {
    track_scan();
    // straight
    if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 1 && U5 == 1 && U6 == 0 && U7 == 0 && U8 == 0) {
        RGB_pure(2);
        motor_forward(55);
    } else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0) {
        RED_on();
        spin_right(40);
        while (U4 != 1) {
            track_scan();
        }
        motor_forward(30);
        RED_off();
    } else if (U3 == 1 && U4 == 1 && U5 == 1 && U6 == 1) {
        RGB_pure(7);
        motor_forward(35);
    } else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 1 && U5 == 0 && U6 == 0 && U7 == 0 && U8 == 0) {
        RGB_pure(5);
        motor_left(45, 1.3);
    } else if (U1 == 0 && U2 == 0 && U3 == 0 && U4 == 0 && U5 == 1 && U6 == 0 && U7 == 0 && U8 == 0) {
        RGB_pure(5);
        motor_right(45, 1.3);
    } else if (U1 == 0 && U2 == 0 && U3 == 1) {
        RGB_pure(6);
        motor_left(25, 2.4);
    } else if (U6 == 1 && U7 == 0 && U8 == 0) {
        RGB_pure(6);
        motor_right(25, 2.4);
    } else if (U7 == 1 && U6 == 0) {
        RGB_pure(4);
        motor_right(18, 2.7);
    } else if (U2 == 1 && U3 == 0) {
        RGB_pure(4);
        motor_left(18, 2.7);
    } else if (U1 == 1 && U3 == 1 && U6 == 0 && U7 == 0 && U8 == 0) {
        RGB_pure(3);
        vertical_left();
    } else if (U5 == 1 && U6 == 1 && U1 == 0 && U2 == 0 && U3 == 0) {
        RGB_pure(3);
        vertical_right();
    } else if (U7 == 1) {
        RGB_pure(1);
        spin_right(45);
    } else if (U2 == 1) {
        RGB_pure(1);
        spin_left(45);
    }
}

void track_test() {
    track_scan();
    if (U1 == 1) {
        RGB_pure(1);
    }
    if (U2 == 1) {
        RGB_pure(2);
    }
    if (U3 == 1) {
        RGB_pure(3);
    }
    if (U4 == 1) {
        RGB_pure(4);
    }
    if (U5 == 1) {
        RGB_pure(5);
    }
    if (U6 == 1) {
        RGB_pure(6);
    }
    if (U7 == 1) {
        RGB_pure(7);
    }
    if (U8 == 1) {
        RGB_clear();
    }
}
