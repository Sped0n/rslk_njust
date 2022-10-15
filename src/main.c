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

uint8_t color = 1;
uint16_t freq = 1;

// 将Port1用作按钮中断的独占方程，当然有特殊需求也可以后面自行修改方程内容
void PORT1_IRQHandler(void) {
    // 声明状态变量
    uint32_t Status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    // 左键
    if (Status & GPIO_PIN1) {
        // 松开按键灭灯
        RED_off();
        // 颜色循环
        color++;
        if (color==8){
            color=1;
        }
    }
        // 右键
    else if (Status & GPIO_PIN4) {
        // 松开按键灭灯
        RED_off();
        // 频率循环
        switch(freq){
        case 1:
            freq = 2;
            break;
        case 2:
            freq = 5;
            break;
        case 5:
            freq = 1;
        }
    }
    // 执行完程序以后清楚中断状态
    GPIO_clearInterruptFlag(GPIO_PORT_P1, Status);
}

int main(void) {
    // 关闭watchdog
    MAP_WDT_A_holdTimer();
    // 模块初始化
    breath_init();
    button_interrupt_init();
    // 主循环
    while (1) {
        uint16_t timer = 0;
        uint16_t increase = 1;
        for(int i=0;i<1000;i++){
            // 按下按键红灯
            if ((get_button_state(LEFT)) || (get_button_state(RIGHT))){
                        RED_on();
            }
            // 渐变函数
            RGB_mpwm_output(color, timer/5, 1, freq);
            if (timer > 500) {
                increase = 0;
            }
            // 渐变变亮
            if (increase==1){
                timer++;
            }
            // 渐变变暗
            else{
                timer--;
            }
        }
    }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop
