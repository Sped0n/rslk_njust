#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <LED.h>
#include <button.h>
#include <driverlib.h>
#include <stdint.h>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// 将Port1用作按钮中断的独占方程，当然有特殊需求也可以后面自行修改方程内容
void PORT1_IRQHandler(void) {
    // 声明状态变量
    uint32_t Status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    // 左键
    if (Status & GPIO_PIN1) {
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
        // 右键
    else if (Status & GPIO_PIN4) {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    // 执行完程序以后清楚中断状态
    GPIO_clearInterruptFlag(GPIO_PORT_P1, Status);
}


int main(void) {
    // 关闭watchdog
    MAP_WDT_A_holdTimer();
    int counter = 0;
    volatile uint32_t i;
    // 模块初始化
    LED_init();
    button_interrupt_init();
    while (1) {
        for(i=0;i<15000;i++){}
        switch (counter) {
            case 0:
                RGB_pure(RED);
                break;
            case 1:
                RGB_pure(GREEN);
                break;
            case 2:
                RGB_pure(BLUE);
                break;
            case 3:
                RGB_pure(PURPLE);
                break;
            case 4:
                RGB_pure(YELLOW);
                break;
            case 5:
                RGB_pure(CYAN);
                break;
            case 6:
                RGB_pure(WHITE);
                break;
        }
        counter++;
        if (counter ==7){
            counter = 0;
        }
    }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop