#pragma once

#include <stdint.h>

//! \section Constants
#define NUM_ULTRASONIC_SENSORS              8

//! \section Thread priorities
#define THD_PRIO_MOTOR_CONTROL              NORMALPRIO + 2
#define THD_PRIO_ULTRASONIC_SENSORS         NORMALPRIO + 1
#define THD_PRIO_SENSOR_DATA_OUTPUT         NORMALPRIO - 1

//! \section LED port/pad definitions
#define LED1_PORT                           GPIOA
#define LED1_PAD                            4
#define LED2_PORT                           GPIOA
#define LED2_PAD                            5
#define LED3_PORT                           GPIOA
#define LED3_PAD                            6
#define LED4_PORT                           GPIOA
#define LED4_PAD                            7

//! \section USART1 port/pad definitions
#define USART1_TX_PORT                      GPIOA
#define USART1_TX_PAD                       9
#define USART1_TX_AF                        7
#define USART1_RX_PORT                      GPIOA
#define USART1_RX_PAD                       10
#define USART1_RX_AF                        7

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
#define ULTRASONIC_SENSORS_ECHO_EXT_MODE    EXT_MODE_GPIOG
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

//! \section DC motor control port/pad definitions
#define MOTOR_1_IN1_PORT                    GPIOF
#define MOTOR_1_IN1_PAD                     0
#define MOTOR_1_IN2_PORT                    GPIOF
#define MOTOR_1_IN2_PAD                     1
#define MOTOR_1_PWR_PORT                    GPIOE
#define MOTOR_1_PWR_PAD                     9
#define MOTOR_1_PWR_AF                      1
#define MOTOR_2_IN1_PORT                    GPIOF
#define MOTOR_2_IN1_PAD                     2
#define MOTOR_2_IN2_PORT                    GPIOF
#define MOTOR_2_IN2_PAD                     3
#define MOTOR_2_PWR_PORT                    GPIOE
#define MOTOR_2_PWR_PAD                     11
#define MOTOR_2_PWR_AF                      1
#define MOTOR_3_IN1_PORT                    GPIOF
#define MOTOR_3_IN1_PAD                     4
#define MOTOR_3_IN2_PORT                    GPIOF
#define MOTOR_3_IN2_PAD                     5
#define MOTOR_3_PWR_PORT                    GPIOE
#define MOTOR_3_PWR_PAD                     13
#define MOTOR_3_PWR_AF                      1
#define MOTOR_4_IN1_PORT                    GPIOF
#define MOTOR_4_IN1_PAD                     6
#define MOTOR_4_IN2_PORT                    GPIOF
#define MOTOR_4_IN2_PAD                     7
#define MOTOR_4_PWR_PORT                    GPIOE
#define MOTOR_4_PWR_PAD                     14
#define MOTOR_4_PWR_AF                      1
