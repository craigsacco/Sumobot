#pragma once

#include <stdint.h>

//! \section Absolute limits
#define MOTOR_MIN_SPEED                     -10000
#define MOTOR_MAX_SPEED                     10000

//! \section Ramp settings
#define MOTOR_UPDATE_PERIOD_MS              5
#define MOTOR_ACCELERATION_PER_MS           10000

void sumoMotorControlInit(void);
void sumoMotorRequestHardStop(uint32_t motor);
void sumoMotorSetTargetSpeed(uint32_t motor, int32_t speed);
