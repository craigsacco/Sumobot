#include <ch.h>
#include <hal.h>
#include <pads.h>

int main(void)
{
    // initialise the HAL and RT
    halInit();
    chSysInit();

    palSetPadMode(LED1_PORT, LED1_PAD, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(LED2_PORT, LED2_PAD, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(LED3_PORT, LED3_PAD, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(LED4_PORT, LED4_PAD, PAL_MODE_OUTPUT_PUSHPULL);

    while (true) {
        palTogglePad(LED1_PORT, LED1_PAD);
        chThdSleepMilliseconds(100);
        palTogglePad(LED2_PORT, LED2_PAD);
        chThdSleepMilliseconds(100);
        palTogglePad(LED3_PORT, LED3_PAD);
        chThdSleepMilliseconds(100);
        palTogglePad(LED4_PORT, LED4_PAD);
        chThdSleepMilliseconds(100);
    }
}
