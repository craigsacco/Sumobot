#pragma once

#include <ch.h>

typedef struct ultrasonic_sensor_data_t {
    bool rising_edge;
    rtcnt_t rising_edge_cnt;
    bool falling_edge;
    rtcnt_t falling_edge_cnt;
    float delay_us;
    float distance_mm;
} ultrasonic_sensor_data_t;

typedef struct sensor_data_t {
    ultrasonic_sensor_data_t ultrasonic_sensors[NUM_ULTRASONIC_SENSORS];
} sensor_data_t;

extern struct sensor_data_t sensor_data;

void sensor_data_init(void);
void sensor_data_lock(void);
void sensor_data_unlock(void);
