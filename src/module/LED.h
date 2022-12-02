#ifndef RSLK_LED_H
#define RSLK_LED_H

# define RED 1
# define GREEN 2
# define BLUE 3
#define PURPLE 4
#define YELLOW 5
#define CYAN 6
#define WHITE 7

#include <driverlib.h>

void LED_init(void);

void RED_on(void);

void RED_off(void);

void RGB_on(uint8_t color);

void RGB_pure(uint8_t color);

void RGB_off(uint8_t color);

void RGB_clear(void);

#endif //RSLK_LED_H
