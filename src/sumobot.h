#pragma once

#include <stdint.h>

//! \section Constants
#define NUM_ULTRASONIC_SENSORS              8

//! \section Thread priorities
#define THD_PRIO_ULTRASONIC_SENSORS         NORMALPRIO + 1

//! \section LED port/pad definitions
#define LED1_PORT                           GPIOA
#define LED1_PAD                            4
#define LED2_PORT                           GPIOA
#define LED2_PAD                            5
#define LED3_PORT                           GPIOA
#define LED3_PAD                            6
#define LED4_PORT                           GPIOA
#define LED4_PAD                            7

//! \section Debug port/pad definitions
#define DEBUG_SWDIO_PORT                    GPIOA
#define DEBUG_SWDIO_PAD                     13
#define DEBUG_SWDIO_AF                      0
#define DEBUG_SWCLK_PORT                    GPIOA
#define DEBUG_SWCLK_PAD                     14
#define DEBUG_SWCLK_AF                      0
#define DEBUG_SWO_PORT                      GPIOB
#define DEBUG_SWO_PAD                       3
#define DEBUG_SWO_AF                        0

//! \section Ultrasonic sensor port/pad definitions
#define ULTRASONIC_SENSORS_ECHO_PORT        GPIOG
#define ULTRASONIC_SENSOR_1_ECHO_PAD        0
#define ULTRASONIC_SENSOR_2_ECHO_PAD        1
#define ULTRASONIC_SENSOR_3_ECHO_PAD        2
#define ULTRASONIC_SENSOR_4_ECHO_PAD        3
#define ULTRASONIC_SENSOR_5_ECHO_PAD        4
#define ULTRASONIC_SENSOR_6_ECHO_PAD        5
#define ULTRASONIC_SENSOR_7_ECHO_PAD        6
#define ULTRASONIC_SENSOR_8_ECHO_PAD        7
#define ULTRASONIC_SENSORS_TRIGGER_PORT     GPIOG
#define ULTRASONIC_SENSOR_1_TRIGGER_PAD     8
#define ULTRASONIC_SENSOR_2_TRIGGER_PAD     9
#define ULTRASONIC_SENSOR_3_TRIGGER_PAD     10
#define ULTRASONIC_SENSOR_4_TRIGGER_PAD     11
#define ULTRASONIC_SENSOR_5_TRIGGER_PAD     12
#define ULTRASONIC_SENSOR_6_TRIGGER_PAD     13
#define ULTRASONIC_SENSOR_7_TRIGGER_PAD     14
#define ULTRASONIC_SENSOR_8_TRIGGER_PAD     15
