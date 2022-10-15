#include <mpwm.h>

void mpwm_init(void) {
    CLK_init();
    SysTick_Init();
}

void RGB_mpwm_output(uint8_t selectColor, uint16_t strength, uint8_t PulseWidth, uint16_t lastMul) {
    // PulseWidth为ms
    // strength 0-100
    if (strength > 100) {
        strength = 100;
    }
    else if (strength < 0) {
        strength = 0;
    }
    for (uint16_t i = 0; i < lastMul; i++) {
        if (strength == 0) {
            RGB_clear();
            delay_us(1000 * PulseWidth);
        }
        else if (strength == 100){
            RGB_pure(selectColor);
            delay_us(1000 * PulseWidth);
        }
        else {
            RGB_pure(selectColor);
            delay_us(10 * strength * PulseWidth);
            RGB_clear();
            delay_us(10 * (100 - strength) * PulseWidth);
        }
    }
}

void breath_init(void) {
    LED_init();
    mpwm_init();
}


