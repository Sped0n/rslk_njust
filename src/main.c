#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "module/track.h"
#include "module/LED.h"
#include <driverlib.h>
#include <stdint.h>
#include <msp432p401r.h>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main(void) {
    motor_init();
    track_init();
    motor_start();
    while (1) {
        track();
    }
}

#pragma clang diagnostic pop
#pragma clang diagnostic pop

