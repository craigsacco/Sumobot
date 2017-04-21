#include <ultrasonic_sensors.h>
#include <sumobot.h>
#include <hal.h>
#include <sensor_data.h>
#include <math.h>

#define NUM_MOTOR_PHASES    8

uint32_t phaseIndex = 0;

#if NUM_MOTOR_PHASES == 4
static const uint8_t phaseValues[NUM_MOTOR_PHASES] = {
    0x3, 0x6, 0xc, 0x9
};
#elif NUM_MOTOR_PHASES == 8
static const uint8_t phaseValues[NUM_MOTOR_PHASES] = {
    0x1, 0x3, 0x2, 0x6, 0x4, 0xc, 0x8, 0x9
};
#else
#error NUM_MOTOR_PHASES is invalid
#endif

bool reverseDirection = false;
uint32_t phaseCount = 0;

void sumoMotorControlPhaseUpdateISR(GPTDriver *gptp)
{
    (void)gptp;

    // update the phase value
    palWriteGroup(MOTOR_1_PHASE_OUTPUTS_PORT, 0xf,
                  MOTOR_1_PHASE_OUTPUT_1_PAD, phaseValues[phaseIndex]);

    if (reverseDirection) {
        if (phaseIndex == 0) {
            phaseIndex = NUM_MOTOR_PHASES - 1;
        } else {
            phaseIndex--;
        }
    } else {
        if (phaseIndex == NUM_MOTOR_PHASES - 1) {
            phaseIndex = 0;
        } else {
            phaseIndex++;
        }
    }

    phaseCount++;
    if (phaseCount == 3000) {
        reverseDirection = !reverseDirection;
        phaseCount = 0;
    }
}

static THD_FUNCTION(sumoMotorControlThread, p)
{
    (void)p;
    chRegSetThreadName("Motor control thread");

    while (true) {
        chThdSleepMilliseconds(500);
    }
}

static THD_WORKING_AREA(sumoMotorControlThreadWA, 256);

void sumoMotorControlThreadStart(void)
{
    // sanity checks
    chDbgCheck(MOTOR_1_PHASE_OUTPUT_1_PAD == 0);
    chDbgCheck(MOTOR_1_PHASE_OUTPUT_2_PAD == MOTOR_1_PHASE_OUTPUT_1_PAD + 1);
    chDbgCheck(MOTOR_1_PHASE_OUTPUT_3_PAD == MOTOR_1_PHASE_OUTPUT_2_PAD + 1);
    chDbgCheck(MOTOR_1_PHASE_OUTPUT_4_PAD == MOTOR_1_PHASE_OUTPUT_3_PAD + 1);

    // setup and start TIM3 as a GPT
    static const GPTConfig gptcfg = {
        1000000,
        sumoMotorControlPhaseUpdateISR,
        0,
        0
    };
    gptStart(&GPTD3, &gptcfg);
    gptStartContinuous(&GPTD3, 1000);

    // create and start thread
    chThdCreateStatic(sumoMotorControlThreadWA, sizeof(sumoMotorControlThreadWA),
                      THD_PRIO_MOTOR_CONTROL, sumoMotorControlThread, NULL);
}
