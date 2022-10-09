#include <LED.h>

void LED_init() {
    // 设置红灯为输出
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    // 设置RGB灯为输出
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
    // 将两灯设置为默认关闭
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}


void RED_on() {
    // 红灯引脚高电平
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void RED_off() {
    // 红灯关闭
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void RGB_on(uint8_t color) {
    // 请输入RED/GREEN/BLUE
    switch (color) {
        case RED:
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            break;
        case GREEN:
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            break;
        case BLUE:
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            break;
    }
}

void RGB_clear() {
    // 清空RGB
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void RGB_pure(uint8_t color) {
    // 请输入颜色
    switch (color) {
        case RED:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            break;
        case GREEN:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            break;
        case BLUE:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            break;
        case PURPLE:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            break;
        case YELLOW:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            break;
        case CYAN:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            break;
        case WHITE:
            RGB_clear();
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            break;
    }
}

void RGB_off(uint8_t color) {
    // 请输入RED/GREEN/BLUE
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, color);
}



