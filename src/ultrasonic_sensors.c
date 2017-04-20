#include <ultrasonic_sensors.h>
#include <sumobot.h>
#include <hal.h>
#include <sensor_data.h>
#include <math.h>

uint32_t current_sensor = 0;
ultrasonic_sensor_data_t* current_sensor_data = NULL;

void ultrasonic_sensor_trigger_isr(EXTDriver *extp, expchannel_t channel)
{
    (void)extp;

    // get counter value
    rtcnt_t counter = chSysGetRealtimeCounterX();

    // check if echo pulse is for the correct sensor
    if (channel != ULTRASONIC_SENSOR_1_ECHO_PAD + current_sensor) {
        return;
    }

    // get edge state
    bool state = palReadPad(ULTRASONIC_SENSORS_ECHO_PORT,
                            ULTRASONIC_SENSOR_1_ECHO_PAD + current_sensor);
    if (state) {
        current_sensor_data->rising_edge = true;
        current_sensor_data->rising_edge_cnt = counter;
    } else {
        current_sensor_data->falling_edge = true;
        current_sensor_data->falling_edge_cnt = counter;
    }
}

void ultrasonic_sensor_start(void)
{
    // reset edge flags for current sensor
    current_sensor_data->rising_edge = false;
    current_sensor_data->falling_edge = false;

    // enable edge-triggered interrupts on echo pin
    extChannelEnable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD + current_sensor);

    // raise the trigger pulse for 10us
    palSetPad(ULTRASONIC_SENSORS_TRIGGER_PORT,
              ULTRASONIC_SENSOR_1_TRIGGER_PAD + current_sensor);
    chThdSleepMicroseconds(10);
    palClearPad(ULTRASONIC_SENSORS_TRIGGER_PORT,
                ULTRASONIC_SENSOR_1_TRIGGER_PAD + current_sensor);
}

void ultrasonic_sensor_finish(void)
{
    // disable edge-triggered interrupts on echo pin
    extChannelDisable(&EXTD1, ULTRASONIC_SENSOR_1_ECHO_PAD + current_sensor);

    // calculate delay and distance for current sensor
    sensor_data_lock();
    if (current_sensor_data->rising_edge && current_sensor_data->falling_edge) {
        current_sensor_data->delay_us = (current_sensor_data->falling_edge_cnt -
                                         current_sensor_data->rising_edge_cnt) /
                                        (STM32_SYSCLK / 1000000.0f);
        current_sensor_data->distance_mm = (current_sensor_data->delay_us / 2.0f) / 2.91f;
    } else {
        current_sensor_data->delay_us = NAN;
        current_sensor_data->distance_mm = NAN;
    }
    sensor_data_unlock();
}

static THD_FUNCTION(ultrasonic_sensor_thread, p)
{
    (void)p;
    chRegSetThreadName("Ultrasonic sensor thread");

    current_sensor = 0;
    current_sensor_data = &(sensor_data.ultrasonic_sensors[current_sensor]);

    while (true) {
        ultrasonic_sensor_start();
        chThdSleepMilliseconds(5);
        ultrasonic_sensor_finish();

        if (++current_sensor == NUM_ULTRASONIC_SENSORS) {
            current_sensor = 0;
        }
        current_sensor_data = &(sensor_data.ultrasonic_sensors[current_sensor]);
    }
}

static THD_WORKING_AREA(ultrasonic_sensor_thread_wa, 256);

void ultrasonic_sensor_thread_start(void)
{
    // sanity checks
    chDbgCheck(ULTRASONIC_SENSOR_1_ECHO_PAD == 0);
    chDbgCheck(ULTRASONIC_SENSOR_2_ECHO_PAD == ULTRASONIC_SENSOR_1_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_3_ECHO_PAD == ULTRASONIC_SENSOR_2_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_4_ECHO_PAD == ULTRASONIC_SENSOR_3_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_5_ECHO_PAD == ULTRASONIC_SENSOR_4_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_6_ECHO_PAD == ULTRASONIC_SENSOR_5_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_7_ECHO_PAD == ULTRASONIC_SENSOR_6_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_8_ECHO_PAD == ULTRASONIC_SENSOR_7_ECHO_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_1_TRIGGER_PAD == 8);
    chDbgCheck(ULTRASONIC_SENSOR_2_TRIGGER_PAD == ULTRASONIC_SENSOR_1_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_3_TRIGGER_PAD == ULTRASONIC_SENSOR_2_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_4_TRIGGER_PAD == ULTRASONIC_SENSOR_3_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_5_TRIGGER_PAD == ULTRASONIC_SENSOR_4_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_6_TRIGGER_PAD == ULTRASONIC_SENSOR_5_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_7_TRIGGER_PAD == ULTRASONIC_SENSOR_6_TRIGGER_PAD + 1);
    chDbgCheck(ULTRASONIC_SENSOR_8_TRIGGER_PAD == ULTRASONIC_SENSOR_7_TRIGGER_PAD + 1);

    // create and start thread
    chThdCreateStatic(ultrasonic_sensor_thread_wa, sizeof(ultrasonic_sensor_thread_wa),
                      THD_PRIO_ULTRASONIC_SENSORS, ultrasonic_sensor_thread, NULL);
}
