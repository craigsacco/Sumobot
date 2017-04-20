#include <ch.h>
#include <hal.h>
#include <pads.h>

static rtcnt_t start = 0;

static void extcb1(EXTDriver *extp, expchannel_t channel) {
    rtcnt_t end = chSysGetRealtimeCounterX();
    float delay_us = (end - start) / (STM32_SYSCLK / 1000000.0f);
    float distance_mm = (delay_us / 2.0f) / 2.91f;

    // applying an offset
    distance_mm -= 100.0f;

    palSetPad(LED1_PORT, LED1_PAD);
    if (distance_mm < 500.0f) {
        palSetPad(LED2_PORT, LED2_PAD);
        if (distance_mm < 200.0f) {
            palSetPad(LED3_PORT, LED3_PAD);
        }
    }
}

int main(void)
{
    // initialise the HAL and RT
    halInit();
    chSysInit();

    static const EXTConfig extcfg = {
        {
            {EXT_CH_MODE_DISABLED, NULL},
            //{EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOD, extcb1},
            {EXT_CH_MODE_FALLING_EDGE | EXT_MODE_GPIOD, extcb1},
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

    while (true) {
        palTogglePad(LED4_PORT, LED4_PAD);
        palClearPad(LED1_PORT, LED1_PAD);
        palClearPad(LED2_PORT, LED2_PAD);
        palClearPad(LED3_PORT, LED3_PAD);

        extChannelEnable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD);
        palSetPad(ULTRASONIC_SENSOR_TRIG_COMMON_PORT, ULTRASONIC_SENSOR_TRIG_COMMON_PAD);
        chThdSleepMicroseconds(10);
        palClearPad(ULTRASONIC_SENSOR_TRIG_COMMON_PORT, ULTRASONIC_SENSOR_TRIG_COMMON_PAD);
        start = chSysGetRealtimeCounterX();

        chThdSleepMilliseconds(50);

        extChannelDisable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD);
    }


//    while (true) {
//        palTogglePad(LED1_PORT, LED1_PAD);
//        chThdSleepMilliseconds(100);
//        palTogglePad(LED2_PORT, LED2_PAD);
//        chThdSleepMilliseconds(100);
//        palTogglePad(LED3_PORT, LED3_PAD);
//        chThdSleepMilliseconds(100);
//        palTogglePad(LED4_PORT, LED4_PAD);
//        chThdSleepMilliseconds(100);
//    }
}
