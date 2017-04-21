#pragma once

#include <hal.h>

void sumoUltrasonicSensorTriggerISR(EXTDriver *extp, expchannel_t channel);
void sumoUltrasonicSensorsThreadStart(void);
