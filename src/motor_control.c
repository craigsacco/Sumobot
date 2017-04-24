#include <ultrasonic_sensors.h>
#include <sumobot.h>
#include <hal.h>
#include <sensor_data.h>
#include <math.h>

static THD_FUNCTION(sumoMotorControlThread, p)
{
    (void)p;
    chRegSetThreadName("Motor control thread");

    pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 0));
    palSetPad(MOTOR_1_IN1_PORT, MOTOR_1_IN1_PAD);
    palClearPad(MOTOR_1_IN2_PORT, MOTOR_1_IN2_PAD);

    for (uint32_t power = 0; power <= 10000; power += 500) {
        chThdSleepMilliseconds(2000);
        pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, power));
    }

    while (true) {
        chThdSleepMilliseconds(500);
    }
}

static THD_WORKING_AREA(sumoMotorControlThreadWA, 256);

void sumoMotorControlThreadStart(void)
{
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
    pwmStart(&PWMD1, &pwmcfg);

    // create and start thread
    chThdCreateStatic(sumoMotorControlThreadWA, sizeof(sumoMotorControlThreadWA),
                      THD_PRIO_MOTOR_CONTROL, sumoMotorControlThread, NULL);
}
