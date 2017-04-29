#include <test_thread.h>
#include <sumobot.h>
#include <ch.h>
#include <motor_control.h>

void sumoTestThreadMotorControlSetTargetSpeedAll(int32_t speed)
{
    for (uint32_t motor = 0; motor < NUM_MOTORS; motor++) {
        sumoMotorSetTargetSpeed(motor, speed);
    }
}

void sumoTestThreadMotorControlRequestHardStopAll(void)
{
    for (uint32_t motor = 0; motor < NUM_MOTORS; motor++) {
        sumoMotorRequestHardStop(motor);
    }
}

void sumoTestThreadMotorControl(void)
{
    while (true) {
        sumoTestThreadMotorControlSetTargetSpeedAll(5000);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(10000);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(-10000);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlRequestHardStopAll();
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(10000);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(0);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(-10000);
        chThdSleepMilliseconds(2000);
        sumoTestThreadMotorControlSetTargetSpeedAll(0);
        chThdSleepMilliseconds(2000);
    }
}

static THD_FUNCTION(sumoTestThread, p)
{
    (void)p;
    chRegSetThreadName("Test thread");

    sumoTestThreadMotorControl();
}

static THD_WORKING_AREA(sumoTestThreadWA, 1024);

void sumoTestThreadInit(void)
{
    // create and start thread
    chThdCreateStatic(sumoTestThreadWA, sizeof(sumoTestThreadWA),
                      THD_PRIO_TEST_THREAD, sumoTestThread, NULL);
}
