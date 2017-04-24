#include <ultrasonic_sensors.h>
#include <sumobot.h>
#include <hal.h>
#include <runtime_data.h>
#include <math.h>

uint32_t currentSensorIndex = 0;
SumoUltrasonicSensorRuntimeData_t* currentRuntimeData = NULL;

void sumoUltrasonicSensorTriggerISR(EXTDriver *extp, expchannel_t channel)
{
    (void)extp;

    // get counter value
    rtcnt_t counter = chSysGetRealtimeCounterX();

    // check if echo pulse is for the correct sensor
    if (channel != ULTRASONIC_SENSOR_1_ECHO_PAD + currentSensorIndex) {
        return;
    }

    // set edge flag and counter
    currentRuntimeData->edgeDetected = true;
    currentRuntimeData->edgeTime_cnts = counter;
}

void sumoUltrasonicSensorStart(void)
{
    // enable edge-triggered interrupts on echo pin
    extChannelEnable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD + currentSensorIndex);

    // raise the trigger pulse for 10us
    palSetPad(ULTRASONIC_SENSORS_TRIGGER_PORT,
              ULTRASONIC_SENSOR_1_TRIGGER_PAD + currentSensorIndex);
    chThdSleepMicroseconds(10);
    palClearPad(ULTRASONIC_SENSORS_TRIGGER_PORT,
                ULTRASONIC_SENSOR_1_TRIGGER_PAD + currentSensorIndex);

    // set/clear data values
    currentRuntimeData->startTime_cnts = chSysGetRealtimeCounterX();
    currentRuntimeData->edgeDetected = false;
}

void sumoUltrasonicSensorFinish(void)
{
    // disable edge-triggered interrupts on echo pin
    extChannelDisable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD + currentSensorIndex);

    // calculate delay and distance for current sensor
    sumoRuntimeDataLock();
    if (currentRuntimeData->edgeDetected) {
        currentRuntimeData->delay_us = (currentRuntimeData->edgeTime_cnts -
                                       currentRuntimeData->startTime_cnts) /
                                      (STM32_SYSCLK / 1000000.0f);
        currentRuntimeData->distance_mm = (currentRuntimeData->delay_us / 2.0f) / 2.91f;

        // apply an offset
        currentRuntimeData->distance_mm -= 85.0f;
    } else {
        currentRuntimeData->delay_us = ULTRASONIC_SENSOR_UNDEFINED;
        currentRuntimeData->distance_mm = ULTRASONIC_SENSOR_UNDEFINED;
    }
    sumoRuntimeDataUnlock();
}

static THD_FUNCTION(sumoUltrasonicSensorsThread, p)
{
    (void)p;
    chRegSetThreadName("Ultrasonic sensors thread");

    currentSensorIndex = 0;

    while (true) {
        currentRuntimeData = &(sumoRuntimeData.ultrasonicSensors[currentSensorIndex]);
        sumoUltrasonicSensorStart();
        chThdSleepMilliseconds(15);
        sumoUltrasonicSensorFinish();
        if (++currentSensorIndex == NUM_ULTRASONIC_SENSORS) {
            currentSensorIndex = 0;
        }
    }
}

static THD_WORKING_AREA(sumoUltrasonicSensorsThreadWA, 256);

void sumoUltrasonicSensorsInit(void)
{
    // sanity checks
    chDbgCheck(ULTRASONIC_SENSOR_1_ECHO_PAD == 0);
    chDbgCheck(ULTRASONIC_SENSOR_2_ECHO_PAD == ULTRASONIC_SENSOR_1_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_3_ECHO_PAD == ULTRASONIC_SENSOR_2_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_4_ECHO_PAD == ULTRASONIC_SENSOR_3_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_5_ECHO_PAD == ULTRASONIC_SENSOR_4_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_6_ECHO_PAD == ULTRASONIC_SENSOR_5_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_7_ECHO_PAD == ULTRASONIC_SENSOR_6_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_8_ECHO_PAD == ULTRASONIC_SENSOR_7_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_1_TRIGGER_PAD == 8);
    chDbgCheck(ULTRASONIC_SENSOR_2_TRIGGER_PAD == ULTRASONIC_SENSOR_1_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_3_TRIGGER_PAD == ULTRASONIC_SENSOR_2_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_4_TRIGGER_PAD == ULTRASONIC_SENSOR_3_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_5_TRIGGER_PAD == ULTRASONIC_SENSOR_4_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_6_TRIGGER_PAD == ULTRASONIC_SENSOR_5_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_7_TRIGGER_PAD == ULTRASONIC_SENSOR_6_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_8_TRIGGER_PAD == ULTRASONIC_SENSOR_7_TRIGGER_PAD + 1);

    // initialise ultrasonic sensor data
    sumoRuntimeDataLock();
    for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
        sumoRuntimeData.ultrasonicSensors[i].startTime_cnts = 0;
        sumoRuntimeData.ultrasonicSensors[i].edgeDetected = false;
        sumoRuntimeData.ultrasonicSensors[i].edgeTime_cnts = 0;
        sumoRuntimeData.ultrasonicSensors[i].delay_us = ULTRASONIC_SENSOR_UNDEFINED;
        sumoRuntimeData.ultrasonicSensors[i].distance_mm = ULTRASONIC_SENSOR_UNDEFINED;
    }
    sumoRuntimeDataUnlock();

    // create and start thread
    chThdCreateStatic(sumoUltrasonicSensorsThreadWA, sizeof(sumoUltrasonicSensorsThreadWA),
                      THD_PRIO_ULTRASONIC_SENSORS, sumoUltrasonicSensorsThread, NULL);
}
