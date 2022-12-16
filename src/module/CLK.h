#ifndef CLK_CLK_H_
#define CLK_CLK_H_

#include <driverlib.h>

void CLK_init(void);
void SysTick_Init(void);


void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);


#endif /* CLK_CLK_H_ */
