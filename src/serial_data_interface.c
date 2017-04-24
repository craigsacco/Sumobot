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
        for (uint32_t i = 0; i < NUM_ULTRASONIC_SENSORS; i++) {
            SumoUltrasonicSensorRuntimeData_t* data = &(sumoRuntimeData.ultrasonicSensors[i]);
            chprintf(stream, "US%u:%.1f,%.1f\r\n", i + 1, data->delay_us, data->distance_mm);
        }
        for (uint32_t i = 0; i < NUM_MOTORS; i++) {
            SumoMotorRuntimeData_t* data = &(sumoRuntimeData.dcMotors[i]);
            chprintf(stream, "MTR%u:%d,%d,%u\r\n", i + 1, data->currentSpeed_100thsPct,
                     data->targetSpeed_100thsPct, data->hardStopRequest);
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
