#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "module/track.h"
#include "module/LED.h"
#include "module/motor.h"
#include "module/bump.h"
#include "module/remote.h"
#include "module/CLK.h"
#include "module/distance.h"
#include <driverlib.h>
#include <stdint.h>
#include <msp432p401r.h>

#define TRACK_BUMP 0
#define MANUAL 1
#define TRACK_DIS 2
#define PARTY 3


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(void) {
    MAP_WDT_A_holdTimer();
    CLK_init();
    SysTick_Init();
    remote_init();
    LED_init();
    bump_init();
    distance_init();
    track_init();
    motor_init();
    uint8_t mode = 0;
    while (1) {
        uint8_t key = remote_scan();
        // mode select
        switch (key) {
            case 162:
                mode = TRACK_BUMP; // track + bump
                break;
            case 98:
                mode = MANUAL; // manual control
                break;
            case 226:
                mode = TRACK_DIS; // track + distance
                break;
            case 144:
                mode = PARTY; // spin free
            default:
                break;
        }
        // main
        switch (mode) {
            case MANUAL:
                if (mode != MANUAL){
                    motor_forward(0);
                }
                bump_disable();
                switch (key) {
                    case 24:
                        motor_forward(50);
                        break;
                    case 74:
                        motor_backward(50);
                        break;
                    case 16:
                        spin_left(30);
                        break;
                    case 90:
                        spin_right(30);
                        break;
                    case 56:
                        motor_forward(0);
                        break;
                    default:
                        break;
                }
                RED_on();
                RGB_on(1);
                break;
            case TRACK_BUMP:
                bump_enable();
                track();
                break;
            case TRACK_DIS:
                bump_disable();
                distance();
                track();
                break;
            case PARTY:
                bump_disable();
                spin_right(100);
                break;
            default:
                break;
        }
    }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop
