#include <sensor_data.h>
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <math.h>

struct SumoSensorData_t sumoSensorData;
mutex_t sumoSensorDataMutex;

void sumoSensorDataInit(void)
{
    // initialise mutex
    chMtxObjectInit(&sumoSensorDataMutex);

    // initialise sensor data
    for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
        sumoSensorData.ultrasonicSensors[i].startTime_cnts = 0;
        sumoSensorData.ultrasonicSensors[i].edgeDetected = false;
        sumoSensorData.ultrasonicSensors[i].edgeTime_cnts = 0;
        sumoSensorData.ultrasonicSensors[i].delay_us = NAN;
        sumoSensorData.ultrasonicSensors[i].distance_mm = NAN;
    }
}

void sumoSensorDataLock(void)
{
    chMtxLock(&sumoSensorDataMutex);
}

void sumoSensorDataUnlock(void)
{
    chMtxUnlock(&sumoSensorDataMutex);
}

static THD_FUNCTION(sumoSensorDataOutputThread, p)
{
    (void)p;
    chRegSetThreadName("Sensor data output thread");

    BaseSequentialStream* stream = (BaseSequentialStream*)&SD1;
    while (true) {
        sumoSensorDataLock();
        chprintf(stream, "US:");
        for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
            float value = sumoSensorData.ultrasonicSensors[i].distance_mm;
            if (!isnan(value)) {
                chprintf(stream, "%.1f", value);
            } else {
                chprintf(stream, "NAN");
            }
            if (i < NUM_ULTRASONIC_SENSORS - 1) {
                chprintf(stream, ",");
            } else {
                chprintf(stream, "\r\n");
            }
        }
        sumoSensorDataUnlock();

        chThdSleepMilliseconds(500);
    }
}

static THD_WORKING_AREA(sumoSensorDataOutputThreadWA, 1024);

void sumoSensorDataOutputThreadStart(void)
{
    // setup and start USART1
    static const SerialConfig serialcfg = {
        115200,
        0,
        0,
        0
    };
    sdStart(&SD1, &serialcfg);

    // create and start thread
    chThdCreateStatic(sumoSensorDataOutputThreadWA, sizeof(sumoSensorDataOutputThreadWA),
                      THD_PRIO_SENSOR_DATA_OUTPUT, sumoSensorDataOutputThread, NULL);
}
