#pragma once

#include <ch.h>

typedef struct SumoUltrasonicSensorData_t {
    rtcnt_t startTime_cnts;
    bool edgeDetected;
    rtcnt_t edgeTime_cnts;
    float delay_us;
    float distance_mm;
} SumoUltrasonicSensorData_t;

typedef struct SumoSensorData_t {
    SumoUltrasonicSensorData_t ultrasonicSensors[NUM_ULTRASONIC_SENSORS];
} sensor_data_t;

extern struct SumoSensorData_t sumoSensorData;

void sumoSensorDataInit(void);
void sumoSensorDataLock(void);
void sumoSensorDataUnlock(void);
void sumoSensorDataOutputThreadStart(void);
