#ifndef RSLK_BUTTON_H
#define RSLK_BUTTON_H
#define LEFT 1
#define RIGHT 2

#include <driverlib.h>

void button_basic_init(void);
uint8_t get_button_state(uint8_t position);
void button_interrupt_init(void);

#endif //RSLK_BUTTON_H
