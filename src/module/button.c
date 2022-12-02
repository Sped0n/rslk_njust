#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#include "button.h"

void button_basic_init(void) {
    // 设置两个按键为输入模式
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4);
    // 设置两个按键为上拉电阻模式（默认高）
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
}

uint8_t get_button_state(uint8_t position) {
    // 输入LEFT或者RIGHT
    switch (position) {
        case LEFT:
            return !GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1);
            break;
        case RIGHT:
            return !GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4);
            break;
        default:
            return 0;
    }
}

void button_interrupt_init(void) {
    // 注意，启动本初始化不需要启动上面的basic_init！！！
    // 设置两个按键为输入模式
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4);
    // 设置两个按键为上拉电阻模式（默认高）
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    // 清除先前中断状态
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    // 检测下降沿
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
    // 启用两个按键/引脚(pin)的中断功能
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    // 启动端口(port)的中断功能
    Interrupt_enableInterrupt(INT_PORT1);
    // 启动全局中断功能
    Interrupt_enableMaster();
}

#pragma clang diagnostic pop
