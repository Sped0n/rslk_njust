#include "bump.h"

#define delay_param 60000



void bump_init() {
    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P4,
                                         GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

    GPIO_clearInterruptFlag(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN0, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN2, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN3, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN5, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P4, GPIO_PIN7, GPIO_LOW_TO_HIGH_TRANSITION);

    GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

    Interrupt_enableInterrupt(INT_PORT4);

    Interrupt_enableMaster();
}

void bump_control_right(uint32_t timer) {
    motor_backward(100);
    for (uint32_t i1 = 0; i1 < delay_param; i1++);
    spin_right(100);  //右转
    for (uint32_t i2 = 0; i2 < timer; i2++);
    motor_forward(40);
}

void bump_control_left(uint32_t timer) {
    motor_backward(100);
    for (uint16_t i1 = 0; i1 < delay_param; i1++);
    spin_left(100);
    for (uint32_t i2 = 0; i2 < timer; i2++);
    motor_forward(40);
}

void bump(uint8_t status) {
    //根据标志位的值做出相应的操作并且对标志位清零
    switch (status) {
        case 1:
            bump_control_left(20000);
            break;
        case 2:
            bump_control_left(30000);
            break;
        case 3:
            bump_control_left(40000);
            break;
        case 4:
            bump_control_right(40000);
            break;
        case 5:
            bump_control_right(30000);
            break;
        case 6:
            bump_control_right(20000);
            break;
        default:
            break;
    }
}

void PORT4_IRQHandler() {
    uint16_t Status;
    uint16_t i = 0;
    uint8_t bump_state = 0;
    Status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P4);
    if (Status & GPIO_PIN0) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN0) == 1) {
            bump_state = 1;
        }
    } else if (Status & GPIO_PIN2) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN2) == 1) {
            bump_state = 2;
        }
    } else if (Status & GPIO_PIN3) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN3) == 1) {
            bump_state = 3;
        }
    } else if (Status & GPIO_PIN5) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN5) == 1) {
            bump_state = 4;
        }
    } else if (Status & GPIO_PIN6) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6) == 1) {
            bump_state = 5;
        }
    } else if (Status & GPIO_PIN7) {
        for (i = 0; i < 500; i++);
        if (GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN7) == 1) {
            bump_state = 6;
        }
    }
    GPIO_clearInterruptFlag(GPIO_PORT_P4, Status);
    bump(bump_state);
}