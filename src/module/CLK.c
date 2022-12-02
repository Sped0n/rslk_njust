#include "CLK.h"

static uint8_t fac_us = 0;

void CLK_init(void)
{
    //关闭看门狗
    WDTCTL = WDTPW | WDTHOLD;

    //配置引脚复用
    // High
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    // Low
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

    //配置外部低速和高速时钟源
    CS_setExternalClockSourceFrequency(32768, 48000000);

    //配置驱动等级
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);


    //配置FLASH
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 1);

    CS_startHFXT(false);
    CS_startLFXT(CS_LFXT_DRIVE3);

    //配置时钟
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);  //48MHz
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4); //12MHz
}


void SysTick_Init(void)
{

    fac_us = CS_getMCLK() / 1000000;
    //使能时钟位
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;;  //系统时钟， 使能STsTick
    // 最大时间 224*1/48MHz=349ms
}


void delay_us(uint32_t nus)
{
    SysTick->LOAD=nus * fac_us;     //配置加载值
    SysTick->VAL=0;  //清除COUNT
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   //使能计时器，开始计时
    while((SysTick->CTRL & 0x00010000)==0); //等待COUNT为1
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  //失能，停止计时
    SysTick->VAL = 0X00;    //清空寄存器
}


//由上面得到的更长时间的延时
void delay_ms(uint32_t nms)
{
    while(nms)
    {
        delay_us(1000);
        --nms;
    }
}


void delay_s(uint32_t nms)
{
    while(nms)
    {
        delay_ms(1000);
        --nms;
    }
}