#include <ch.h>
#include <hal.h>
#include <sumobot.h>
#include <ultrasonic_sensors.h>
#include <sensor_data.h>

int main(void)
{
    // initialise the HAL and RT
    halInit();
    chSysInit();

    // setup external interrupts
    static const EXTConfig extcfg = {
        {
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_FALLING_EDGE | ULTRASONIC_SENSORS_ECHO_EXT_MODE, sumoUltrasonicSensorTriggerISR},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL},
            {EXT_CH_MODE_DISABLED, NULL}
        }
    };
    extStart(&EXTD1, &extcfg);

    // setup USART1
    static const SerialConfig serialcfg = {
        115200,
        0,
        0,
        0
    };
    sdStart(&SD1, &serialcfg);

    // initialise the sensor data block
    sumoSensorDataInit();

    // start threads
    sumoUltrasonicSensorsThreadStart();
    sumoSensorDataOutputThreadStart();

    // continuously blink the LED
    while (true) {
        palTogglePad(LED4_PORT, LED4_PAD);
        chThdSleepMilliseconds(500);
    }
}
