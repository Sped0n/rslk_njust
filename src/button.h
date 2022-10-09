#ifndef RSLK_BUTTON_H
#define RSLK_BUTTON_H
#define LEFT 1
#define RIGHT 2

#include <driverlib.h>

void button_init(void);
uint8_t get_button_state(uint8_t position);

#endif //RSLK_BUTTON_H
