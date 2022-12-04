# include "distance.h"
// filtered ADC sample
uint32_t center;
uint32_t right;
uint32_t left;
uint32_t raw17, raw12, raw16;

void distance_init() {
    ADC_init();
}

void read_distance(void) {
    uint8_t filter = 16;
    uint32_t sum1 = 0, sum2 = 0, sum3 = 0;
    for (uint8_t i = 0; i < filter; i++) {
        ADC_In17_12_16(&raw17, &raw12, &raw16);
        sum1 = raw17 + sum1;
        sum2 = raw12 + sum2;
        sum3 = raw16 + sum3;
        delay_ms(2);
    }
    left = sum1 / filter;
    center = sum2 / filter;
    right = sum3 / filter;
}

void distance() {
    uint32_t distance_center;
    uint32_t distance_left;
    uint32_t distance_right;
    read_distance();
    distance_center = 1195172 / (center - 1058);
    distance_right = 1195172 / (right - 1058);
    distance_left = 1195172 / (left - 1058);
    if ((distance_center <= 80) && (distance_center > 0)) {
        motor_backward(100);
        delay_ms(200);
        spin_right(100);
        delay_ms(200);
        motor_forward(40);
    } else if ((distance_right <= 70) && (distance_right > 0)) {
        motor_backward(100);
        delay_ms(150);
        spin_left(100);
        delay_ms(100);
        motor_forward(40);
    } else if ((distance_left <= 70) && (distance_left > 0)) {
        motor_backward(100);
        delay_ms(150);
        spin_right(150);
        delay_ms(150);
        motor_forward(40);
    }
}

void distance_test() {
    uint32_t distance_center;
    uint32_t distance_left;
    uint32_t distance_right;
    read_distance();
    distance_center = 1195172 / (center - 1058);
    distance_right = 1195172 / (right - 1058);
    distance_left = 1195172 / (left - 1058);
    if ((distance_center <= 90) && (distance_center > 0)) {
        RGB_pure(1);
    } else if ((distance_right <= 80) && (distance_right > 0)) {
        RGB_pure(2);
    } else if ((distance_left <= 80) && (distance_left > 0)) {
        RGB_pure(3);
    } else {
        RGB_clear();
    }
}
