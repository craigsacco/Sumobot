#include <runtime_data.h>
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <math.h>

struct SumoRuntimeData_t sumoRuntimeData;
mutex_t sumoRuntimeDataMutex;

static THD_FUNCTION(sumoRuntimeDataOutputThread, p)
{
    (void)p;
    chRegSetThreadName("Sensor data output thread");

    BaseSequentialStream* stream = (BaseSequentialStream*)&SD1;
    while (true) {
        sumoRuntimeDataLock();
        chprintf(stream, "US:");
        for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
            float value = sumoRuntimeData.ultrasonicSensors[i].distance_mm;
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
        sumoRuntimeDataUnlock();

        chThdSleepMilliseconds(500);
    }
}

static THD_WORKING_AREA(sumoRuntimeDataOutputThreadWA, 1024);

void sumoRuntimeDataInit(void)
{
    // initialise mutex
    chMtxObjectInit(&sumoRuntimeDataMutex);

    // setup and start USART1
    static const SerialConfig serialcfg = {
        115200,
        0,
        0,
        0
    };
    sdStart(&SD1, &serialcfg);

    // create and start thread
    chThdCreateStatic(sumoRuntimeDataOutputThreadWA, sizeof(sumoRuntimeDataOutputThreadWA),
                      THD_PRIO_RUNTIME_DATA_OUTPUT, sumoRuntimeDataOutputThread, NULL);
}

void sumoRuntimeDataLock(void)
{
    chMtxLock(&sumoRuntimeDataMutex);
}

void sumoRuntimeDataUnlock(void)
{
    chMtxUnlock(&sumoRuntimeDataMutex);
}
