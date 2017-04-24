#include <serial_data_interface.h>
#include <runtime_data.h>
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <math.h>

static THD_FUNCTION(sumoSerialDataInterfaceThread, p)
{
    (void)p;
    chRegSetThreadName("Sensor data output thread");

    BaseSequentialStream* stream = (BaseSequentialStream*)SERIAL_DATA_INTERFACE_PERIPH;
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

static THD_WORKING_AREA(sumoSerialDataInterfaceThreadWA, 1024);

void sumoSerialDataInterfaceInit(void)
{
    // setup and start USART1
    static const SerialConfig serialcfg = {
        115200,
        0,
        0,
        0
    };
    sdStart(SERIAL_DATA_INTERFACE_PERIPH, &serialcfg);

    // create and start thread
    chThdCreateStatic(sumoSerialDataInterfaceThreadWA, sizeof(sumoSerialDataInterfaceThreadWA),
                      THD_PRIO_SERIAL_DATA_INTERFACE, sumoSerialDataInterfaceThread, NULL);
}
