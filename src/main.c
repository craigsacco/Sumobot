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


    static const EXTConfig extcfg = {
        {
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
            {EXT_CH_MODE_BOTH_EDGES | EXT_MODE_GPIOG, ultrasonic_sensor_trigger_isr},
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

    // initialise the sensor data block
    sensor_data_init();

    // start the ultrasonic sensor thread
    ultrasonic_sensor_thread_start();

    // continuously blink the LED
    while (true) {
        palTogglePad(LED4_PORT, LED4_PAD);
        chThdSleepMilliseconds(500);
    }
}
