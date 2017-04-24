#pragma once

#include <hal.h>

//! \section Sensor constants
#define ULTRASONIC_SENSOR_UNDEFINED         (-1.0f)

void sumoUltrasonicSensorTriggerISR(EXTDriver *extp, expchannel_t channel);
void sumoUltrasonicSensorsInit(void);
