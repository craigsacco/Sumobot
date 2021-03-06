#include <ch.h>
#include <hal.h>
#include <sumobot.h>
#include <ultrasonic_sensors.h>
#include <runtime_data.h>
#include <motor_control.h>
#include <serial_data_interface.h>
#include <test_thread.h>

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

    // initialise subsystems
    sumoRuntimeDataInit();
    sumoUltrasonicSensorsInit();
    sumoMotorControlInit();
    sumoTestThreadInit();
    sumoSerialDataInterfaceInit();

    // lower the priority of this thread
    chThdSetPriority(LOWPRIO);

    // continuously blink the LED
    while (true) {
        palTogglePad(LED4_PORT, LED4_PAD);
        chThdSleepMilliseconds(500);
    }
}
