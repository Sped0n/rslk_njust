#include <driverlib.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(void) {
    // disable watchdog
    MAP_WDT_A_holdTimer();
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    volatile int i;
    while (1) {
        for (i = 0; i < 100000; i++);  // Delay
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}

#pragma clang diagnostic pop