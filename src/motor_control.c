#include <motor_control.h>
#include <sumobot.h>
#include <hal.h>
#include <runtime_data.h>
#include <math.h>

static THD_FUNCTION(sumoMotorControlThread, p)
{
    (void)p;
    chRegSetThreadName("Motor control thread");

    while (true) {
        for (uint8_t motor = 0; motor < NUM_MOTORS; motor++) {
            SumoMotorRuntimeData_t* motorData = &(sumoRuntimeData.dcMotors[motor]);
            uint8_t padIN1 = MOTOR_1_IN1_PAD + (motor * 2);
            uint8_t padIN2 = MOTOR_1_IN2_PAD + (motor * 2);
            pwmchannel_t pwmChannel = MOTOR_1_PWR_PWM_CH + motor;

            // perform a hard stop if needed
            if (motorData->hardStopRequest) {
                palClearPad(MOTORS_INx_PORT, padIN1);
                palClearPad(MOTORS_INx_PORT, padIN2);
                sumoRuntimeDataLock();
                motorData->hardStopRequest = false;
                motorData->targetSpeed_100thsPct = 0;
                motorData->currentSpeed_100thsPct = 0;
                sumoRuntimeDataUnlock();
                continue;
            }

            // if current speed is the same as the target speed, do nothing
            if (motorData->currentSpeed_100thsPct == motorData->targetSpeed_100thsPct) {
                continue;
            }

            // lock the data
            sumoRuntimeDataLock();

            // calculate new speed
            int32_t newSpeed = 0;
            int32_t speedDelta = MOTOR_ACCELERATION_PER_MS * MOTOR_UPDATE_PERIOD_MS;
            if (motorData->targetSpeed_100thsPct > motorData->currentSpeed_100thsPct) {
                newSpeed = min(motorData->targetSpeed_100thsPct,
                               motorData->currentSpeed_100thsPct + speedDelta);
            } else {
                newSpeed = max(motorData->targetSpeed_100thsPct,
                               motorData->currentSpeed_100thsPct - speedDelta);
            }

            // update speed
            palWritePad(MOTORS_INx_PORT, padIN1, newSpeed > 0);
            palWritePad(MOTORS_INx_PORT, padIN2, newSpeed < 0);
            pwmEnableChannel(MOTORS_PWR_PERIPH, pwmChannel,
                             PWM_PERCENTAGE_TO_WIDTH(MOTORS_PWR_PERIPH, abs(newSpeed)));
            motorData->currentSpeed_100thsPct = newSpeed;

            // unlock the data
            sumoRuntimeDataUnlock();
        }

        // wait
        chThdSleepMilliseconds(MOTOR_UPDATE_PERIOD_MS);
    }
}

static THD_WORKING_AREA(sumoMotorControlThreadWA, 256);

void sumoMotorControlInit(void)
{
    // sanity checks
    chDbgCheck(MOTOR_1_IN1_PAD == 0);
    chDbgCheck(MOTOR_1_IN2_PAD == MOTOR_1_IN1_PAD + 1);
    chDbgCheck(MOTOR_2_IN1_PAD == MOTOR_1_IN2_PAD + 1);
    chDbgCheck(MOTOR_2_IN2_PAD == MOTOR_2_IN1_PAD + 1);
    chDbgCheck(MOTOR_3_IN1_PAD == MOTOR_2_IN2_PAD + 1);
    chDbgCheck(MOTOR_3_IN2_PAD == MOTOR_3_IN1_PAD + 1);
    chDbgCheck(MOTOR_4_IN1_PAD == MOTOR_3_IN2_PAD + 1);
    chDbgCheck(MOTOR_4_IN2_PAD == MOTOR_4_IN1_PAD + 1);
    chDbgCheck(MOTOR_1_PWR_PWM_CH == 0);
    chDbgCheck(MOTOR_2_PWR_PWM_CH == MOTOR_1_PWR_PWM_CH + 1);
    chDbgCheck(MOTOR_3_PWR_PWM_CH == MOTOR_2_PWR_PWM_CH + 1);
    chDbgCheck(MOTOR_4_PWR_PWM_CH == MOTOR_3_PWR_PWM_CH + 1);

    // initialise motor data
    sumoRuntimeDataLock();
    for (uint32_t i = 0; i < NUM_MOTORS; i++) {
        sumoRuntimeData.dcMotors[i].currentSpeed_100thsPct = 0;
        sumoRuntimeData.dcMotors[i].targetSpeed_100thsPct = 0;
        sumoRuntimeData.dcMotors[i].hardStopRequest = false;
    }
    sumoRuntimeDataUnlock();

    // setup and start a 1kHz PWM generator on TIM1
    static PWMConfig pwmcfg = {
        1000000,
        1000,
        NULL,
        {
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL},
            {PWM_OUTPUT_ACTIVE_HIGH, NULL}
        },
        0,
        0
    };
    pwmStart(MOTORS_PWR_PERIPH, &pwmcfg);

    // create and start thread
    chThdCreateStatic(sumoMotorControlThreadWA, sizeof(sumoMotorControlThreadWA),
                      THD_PRIO_MOTOR_CONTROL, sumoMotorControlThread, NULL);
}

void sumoMotorRequestHardStop(uint32_t motor)
{
    chDbgCheck(motor < NUM_MOTORS);

    sumoRuntimeDataLock();
    sumoRuntimeData.dcMotors[motor].hardStopRequest = true;
    sumoRuntimeDataUnlock();
}

void sumoMotorSetTargetSpeed(uint32_t motor, int32_t speed_100thsPct)
{
    chDbgCheck(motor < NUM_MOTORS);
    chDbgCheck(speed_100thsPct >= MOTOR_MIN_SPEED);
    chDbgCheck(speed_100thsPct <= MOTOR_MAX_SPEED);

    sumoRuntimeDataLock();
    sumoRuntimeData.dcMotors[motor].hardStopRequest = false;
    sumoRuntimeData.dcMotors[motor].targetSpeed_100thsPct = speed_100thsPct;
    sumoRuntimeDataUnlock();
}
