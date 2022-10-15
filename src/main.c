#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include <LED.h>
#include <button.h>
#include <driverlib.h>
#include <stdint.h>
#include <mpwm.h>
#include <msp432p401r.h>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

// 将Port1用作按钮中断的独占方程，当然有特殊需求也可以后面自行修改方程内容
//void PORT1_IRQHandler(void) {
//    // 声明状态变量
//    uint32_t Status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
//    // 左键
//    if (Status & GPIO_PIN1) {
//        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
//    }
//        // 右键
//    else if (Status & GPIO_PIN4) {
//        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
//    }
//    // 执行完程序以后清楚中断状态
//    GPIO_clearInterruptFlag(GPIO_PORT_P1, Status);
//}

int main(void) {
    // 关闭watchdog
    MAP_WDT_A_holdTimer();
    volatile uint32_t k;
    // 模块初始化
    breath_init();
    uint8_t color = 1;
    while (1) {
        uint16_t timer = 0;
        uint16_t increase = 1;
        for(int i=0;i<1000;i++){
            RGB_mpwm_output(color, timer/5, 1, 10);
            if (timer > 500) {
                increase = 0;
            }
            if (increase==1){
                timer++;
            }
            else{
                timer--;
            }
        }
        color++;
        if (color == 8) {
            color = 1;
        }
    }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop