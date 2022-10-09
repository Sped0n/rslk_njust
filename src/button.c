#include <button.h>

void button_init() {
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
