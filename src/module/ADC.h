#ifndef RSLK_ADC_H
#define RSLK_ADC_H

#include <driverlib.h>

void ADC_init(void);
void ADC_In17_12_16(uint32_t *ch17, uint32_t *ch12, uint32_t *ch16);

#endif //RSLK_ADC_H
