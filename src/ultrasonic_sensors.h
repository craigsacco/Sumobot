#pragma once

#include <hal.h>

void ultrasonic_sensor_trigger_isr(EXTDriver *extp, expchannel_t channel);
void ultrasonic_sensor_thread_start(void);
