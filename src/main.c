#include <ch.h>
#include <hal.h>

int main(void)
{
    // initialise the HAL and RT
    halInit();
    chSysInit();

    palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL);

    while (true) {
        palTogglePad(GPIOA, 4);
        chThdSleepMilliseconds(250);
    }
}
