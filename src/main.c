#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-msc50-cpp"
#include <LED.h>
#include <button.h>
#include <driverlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(void) {
    // 关闭watchdog
    MAP_WDT_A_holdTimer();
    LED_init();
    int counter = 0;
    volatile int temp = -1;
    volatile int i;

    button_init();
    while (1) {
        for (i = 0; i < 1000; i++) {
            if (get_button_state(RIGHT)) {
                while (1) {
                    temp = rand() % 7;
                    if (temp != counter) {
                        break;
                    }
                }
                counter = temp;
                break;
            }
            if (get_button_state(LEFT)) {
                counter++;
                if (counter >= 7) {
                    counter = 0;
                }
                break;
            }
        }

        switch (counter) {
            case 0:
                RGB_pure(RED);
                break;
            case 1:
                RGB_pure(GREEN);
                break;
            case 2:
                RGB_pure(BLUE);
                break;
            case 3:
                RGB_pure(PURPLE);
                break;
            case 4:
                RGB_pure(YELLOW);
                break;
            case 5:
                RGB_pure(CYAN);
                break;
            case 6:
                RGB_pure(WHITE);
                break;
        }
    }
}



#pragma clang diagnostic pop
#pragma clang diagnostic pop