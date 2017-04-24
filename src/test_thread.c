#include <test_thread.h>
#include <sumobot.h>
#include <ch.h>
#include <motor_control.h>

void sumoTestThread_MotorControl(void)
{
    while (true) {
        sumoMotorSetTargetSpeed(0, 5000);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, 10000);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, -10000);
        chThdSleepMilliseconds(2000);
        sumoMotorRequestHardStop(0);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, 10000);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, 0);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, -10000);
        chThdSleepMilliseconds(2000);
        sumoMotorSetTargetSpeed(0, 0);
        chThdSleepMilliseconds(2000);
    }
}

static THD_FUNCTION(sumoTestThread, p)
{
    (void)p;
    chRegSetThreadName("Test thread");

    sumoTestThread_MotorControl();
}

static THD_WORKING_AREA(sumoTestThreadWA, 1024);

void sumoTestThreadInit(void)
{
    // create and start thread
    chThdCreateStatic(sumoTestThreadWA, sizeof(sumoTestThreadWA),
                      THD_PRIO_TEST_THREAD, sumoTestThread, NULL);
}
