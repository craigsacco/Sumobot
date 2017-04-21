#include <ultrasonic_sensors.h>
#include <sumobot.h>
#include <hal.h>
#include <sensor_data.h>
#include <math.h>

uint32_t currentSensorIndex = 0;
SumoUltrasonicSensorData_t* currentSensorData = NULL;

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
    currentSensorData->edgeDetected = true;
    currentSensorData->edgeTime_cnts = counter;
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
    currentSensorData->startTime_cnts = chSysGetRealtimeCounterX();
    currentSensorData->edgeDetected = false;
}

void sumoUltrasonicSensorFinish(void)
{
    // disable edge-triggered interrupts on echo pin
    extChannelDisable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD + currentSensorIndex);

    // calculate delay and distance for current sensor
    sumoSensorDataLock();
    if (currentSensorData->edgeDetected) {
        currentSensorData->delay_us = (currentSensorData->edgeTime_cnts -
                                       currentSensorData->startTime_cnts) /
                                      (STM32_SYSCLK / 1000000.0f);
        currentSensorData->distance_mm = (currentSensorData->delay_us / 2.0f) / 2.91f;

        // apply an offset
        currentSensorData->distance_mm -= 85.0f;
    } else {
        currentSensorData->delay_us = NAN;
        currentSensorData->distance_mm = NAN;
    }
    sumoSensorDataUnlock();
}

static THD_FUNCTION(sumoUltrasonicSensorsThread, p)
{
    (void)p;
    chRegSetThreadName("Ultrasonic sensors thread");

    currentSensorIndex = 0;

    while (true) {
        currentSensorData = &(sumoSensorData.ultrasonicSensors[currentSensorIndex]);
        sumoUltrasonicSensorStart();
        chThdSleepMilliseconds(15);
        sumoUltrasonicSensorFinish();
        if (++currentSensorIndex == NUM_ULTRASONIC_SENSORS) {
            currentSensorIndex = 0;
        }
    }
}

static THD_WORKING_AREA(sumoUltrasonicSensorsThreadWA, 256);

void sumoUltrasonicSensorsThreadStart(void)
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

    // create and start thread
    chThdCreateStatic(sumoUltrasonicSensorsThreadWA, sizeof(sumoUltrasonicSensorsThreadWA),
                      THD_PRIO_ULTRASONIC_SENSORS, sumoUltrasonicSensorsThread, NULL);
}
