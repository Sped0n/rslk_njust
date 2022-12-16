#include "CLK.h"

static uint8_t fac_us = 0;

void CLK_init(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

    CS_setExternalClockSourceFrequency(32768, 48000000);

    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

    MAP_FlashCtl_setWaitState(FLASH_BANK0, 1);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 1);

    CS_startHFXT(false);
    CS_startLFXT(CS_LFXT_DRIVE3);

    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);  //48MHz
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4); //12MHz
}


void SysTick_Init(void)
{

    fac_us = CS_getMCLK() / 1000000;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
}

void delay_us(uint32_t us)
{
    SysTick->LOAD=us * fac_us;
    SysTick->VAL=0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    while((SysTick->CTRL & 0x00010000)==0);
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

void delay_ms(uint32_t ms)
{
    while(ms)
    {
        delay_us(1000);
        --ms;
    }
}


void delay_s(uint32_t s)
{
    while(s)
    {
        delay_ms(1000);
        --s;
    }
}