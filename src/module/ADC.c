#include "ADC.h"

void ADC_init(void) {
    /* Initializing ADC (MCLK/1/1) */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, ADC_NOROUTE);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN0 | GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, false);

    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_INTBUF_VREFNEG_VSS, ADC_INPUT_A12, false);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_INTBUF_VREFNEG_VSS, ADC_INPUT_A16, false);
    ADC14_configureConversionMemory(ADC_MEM2, ADC_VREFPOS_INTBUF_VREFNEG_VSS, ADC_INPUT_A17, false);
    ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_32, ADC_PULSE_WIDTH_32);
    ADC14_setSampleHoldTrigger(ADC_TRIGGER_ADCSC, 0);
    /* Enabling Interrupts */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();
}

void ADC_In17_12_16(uint32_t *ch17, uint32_t *ch12, uint32_t *ch16) {
    while (ADC14_isBusy()) {};
    ADC14->CTL0 |= 0x00000001;
    while ((ADC14_getInterruptStatus() & 0x04) == 0) {};

    *ch17 = ADC14_getResult(ADC_MEM2);
    *ch12 = ADC14_getResult(ADC_MEM0);
    *ch16 = ADC14_getResult(ADC_MEM1);
}
