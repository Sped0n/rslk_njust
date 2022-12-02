//
// Created by 文志彬 on 2022/10/16.
//

#ifndef RSLK_MPWM_H
#define RSLK_MPWM_H

#include "CLK.h"
#include <math.h>
#include "LED.h"
#include <stdint.h>

void mpwm_init(void);
void RGB_mpwm_output(uint8_t selectColor, uint16_t strength, uint8_t PulseWidth, uint16_t lastMul);
void breath_init(void);

#endif //RSLK_MPWM_H
