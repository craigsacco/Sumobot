#pragma once

#include <ch.h>

typedef struct SumoUltrasonicSensorRuntimeData_t {
    rtcnt_t startTime_cnts;
    bool edgeDetected;
    rtcnt_t edgeTime_cnts;
    float delay_us;
    float distance_mm;
} SumoUltrasonicSensorRuntimeData_t;

typedef struct SumoMotorRuntimeData_t {
    int32_t currentSpeed_100thsPct;
    int32_t targetSpeed_100thsPct;
    bool hardStopRequest;
} SumoMotorRuntimeData_t;

typedef struct SumoRuntimeData_t {
    SumoUltrasonicSensorRuntimeData_t ultrasonicSensors[NUM_ULTRASONIC_SENSORS];
    SumoMotorRuntimeData_t dcMotors[NUM_MOTORS];
} sensor_data_t;

extern struct SumoRuntimeData_t sumoRuntimeData;

void sumoRuntimeDataInit(void);
void sumoRuntimeDataLock(void);
void sumoRuntimeDataUnlock(void);
