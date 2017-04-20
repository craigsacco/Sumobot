#include <sensor_data.h>
#include <ch.h>
#include <math.h>

struct sensor_data_t sensor_data;
mutex_t sensor_data_mutex;

void sensor_data_init(void)
{
    // initialise mutex
    chMtxObjectInit(&sensor_data_mutex);

    // initialise sensor data
    for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
        sensor_data.ultrasonic_sensors[i].rising_edge = false;
        sensor_data.ultrasonic_sensors[i].rising_edge_cnt = 0;
        sensor_data.ultrasonic_sensors[i].falling_edge = false;
        sensor_data.ultrasonic_sensors[i].falling_edge_cnt = 0;
        sensor_data.ultrasonic_sensors[i].delay_us = NAN;
        sensor_data.ultrasonic_sensors[i].distance_mm = NAN;
    }
}

void sensor_data_lock(void)
{
    chMtxLock(&sensor_data_mutex);
}

void sensor_data_unlock(void)
{
    chMtxUnlock(&sensor_data_mutex);
}
