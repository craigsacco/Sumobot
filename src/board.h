#pragma once

#include <sumobot.h>

#define BOARD_NAME                  "Generic STM32F407 board using SWD/HSE/LSE"

#define STM32_LSECLK                32768U
#define STM32_HSECLK                8000000U
#define STM32_VDD                   330U

#define STM32F407xx

#define PIN_MODE_INPUT(n)                   (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)                  (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)               (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)                  (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)                      (0U << (n))
#define PIN_ODR_HIGH(n)                     (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)               (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)              (1U << (n))
#define PIN_OSPEED_VERYLOW(n)               (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)                   (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)                (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)                  (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)               (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)                 (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)               (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)                   ((v) << (((n) % 8U) * 4U))

#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(LED1_PAD) | \
                                     PIN_MODE_OUTPUT(LED2_PAD) | \
                                     PIN_MODE_OUTPUT(LED3_PAD) | \
                                     PIN_MODE_OUTPUT(LED4_PAD) | \
                                     PIN_MODE_ALTERNATE(SERIAL_DATA_INTERFACE_TX_PAD) | \
                                     PIN_MODE_ALTERNATE(SERIAL_DATA_INTERFACE_RX_PAD) | \
                                     PIN_MODE_ALTERNATE(DEBUG_SWDIO_PAD) | \
                                     PIN_MODE_ALTERNATE(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(LED1_PAD) | \
                                     PIN_OTYPE_PUSHPULL(LED2_PAD) | \
                                     PIN_OTYPE_PUSHPULL(LED3_PAD) | \
                                     PIN_OTYPE_PUSHPULL(LED4_PAD) | \
                                     PIN_OTYPE_PUSHPULL(SERIAL_DATA_INTERFACE_TX_PAD) | \
                                     PIN_OTYPE_PUSHPULL(SERIAL_DATA_INTERFACE_RX_PAD) | \
                                     PIN_OTYPE_PUSHPULL(DEBUG_SWDIO_PAD) | \
                                     PIN_OTYPE_PUSHPULL(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_VERYLOW(LED1_PAD) | \
                                     PIN_OSPEED_VERYLOW(LED2_PAD) | \
                                     PIN_OSPEED_VERYLOW(LED3_PAD) | \
                                     PIN_OSPEED_VERYLOW(LED4_PAD) | \
                                     PIN_OSPEED_HIGH(SERIAL_DATA_INTERFACE_TX_PAD) | \
                                     PIN_OSPEED_HIGH(SERIAL_DATA_INTERFACE_RX_PAD) | \
                                     PIN_OSPEED_HIGH(DEBUG_SWDIO_PAD) | \
                                     PIN_OSPEED_HIGH(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(LED1_PAD) | \
                                     PIN_PUPDR_FLOATING(LED2_PAD) | \
                                     PIN_PUPDR_FLOATING(LED3_PAD) | \
                                     PIN_PUPDR_FLOATING(LED4_PAD) | \
                                     PIN_PUPDR_FLOATING(SERIAL_DATA_INTERFACE_TX_PAD) | \
                                     PIN_PUPDR_FLOATING(SERIAL_DATA_INTERFACE_RX_PAD) | \
                                     PIN_PUPDR_FLOATING(DEBUG_SWDIO_PAD) | \
                                     PIN_PUPDR_FLOATING(DEBUG_SWCLK_PAD))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW(LED1_PAD) | \
                                     PIN_ODR_LOW(LED2_PAD) | \
                                     PIN_ODR_LOW(LED3_PAD) | \
                                     PIN_ODR_LOW(LED4_PAD))
#define VAL_GPIOA_AFRL              (0U)
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(SERIAL_DATA_INTERFACE_TX_PAD, \
                                                 SERIAL_DATA_INTERFACE_TX_AF) | \
                                     PIN_AFIO_AF(SERIAL_DATA_INTERFACE_RX_PAD, \
                                                 SERIAL_DATA_INTERFACE_RX_AF) | \
                                     PIN_AFIO_AF(DEBUG_SWDIO_PAD, DEBUG_SWDIO_AF) | \
                                     PIN_AFIO_AF(DEBUG_SWCLK_PAD, DEBUG_SWCLK_AF))

#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(DEBUG_SWO_PAD))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(DEBUG_SWO_PAD))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(DEBUG_SWO_PAD))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(DEBUG_SWO_PAD))
#define VAL_GPIOB_ODR               (0U)
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(DEBUG_SWO_PAD, DEBUG_SWO_AF))
#define VAL_GPIOB_AFRH              (0U)

#define VAL_GPIOC_MODER             (0U)
#define VAL_GPIOC_OTYPER            (0U)
#define VAL_GPIOC_OSPEEDR           (0U)
#define VAL_GPIOC_PUPDR             (0U)
#define VAL_GPIOC_ODR               (0U)
#define VAL_GPIOC_AFRL              (0U)
#define VAL_GPIOC_AFRH              (0U)

#define VAL_GPIOD_MODER             (0U)
#define VAL_GPIOD_OTYPER            (0U)
#define VAL_GPIOD_OSPEEDR           (0U)
#define VAL_GPIOD_PUPDR             (0U)
#define VAL_GPIOD_ODR               (0U)
#define VAL_GPIOD_AFRL              (0U)
#define VAL_GPIOD_AFRH              (0U)

#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(MOTOR_1_PWR_PAD) | \
                                     PIN_MODE_ALTERNATE(MOTOR_2_PWR_PAD) | \
                                     PIN_MODE_ALTERNATE(MOTOR_3_PWR_PAD) | \
                                     PIN_MODE_ALTERNATE(MOTOR_4_PWR_PAD))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(MOTOR_1_PWR_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_2_PWR_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_3_PWR_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_4_PWR_PAD))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(MOTOR_1_PWR_PAD) | \
                                     PIN_OSPEED_HIGH(MOTOR_2_PWR_PAD) | \
                                     PIN_OSPEED_HIGH(MOTOR_3_PWR_PAD) | \
                                     PIN_OSPEED_HIGH(MOTOR_4_PWR_PAD))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(MOTOR_1_PWR_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_2_PWR_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_3_PWR_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_4_PWR_PAD))
#define VAL_GPIOE_ODR               (0U)
#define VAL_GPIOE_AFRL              (0U)
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(MOTOR_1_PWR_PAD, MOTOR_1_PWR_AF) | \
                                     PIN_AFIO_AF(MOTOR_2_PWR_PAD, MOTOR_2_PWR_AF) | \
                                     PIN_AFIO_AF(MOTOR_3_PWR_PAD, MOTOR_3_PWR_AF) | \
                                     PIN_AFIO_AF(MOTOR_4_PWR_PAD, MOTOR_4_PWR_AF))

#define VAL_GPIOF_MODER             (PIN_MODE_OUTPUT(MOTOR_1_IN1_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_1_IN2_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_2_IN1_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_2_IN2_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_3_IN1_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_3_IN2_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_4_IN1_PAD) | \
                                     PIN_MODE_OUTPUT(MOTOR_4_IN2_PAD))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(MOTOR_1_IN1_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_1_IN2_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_2_IN1_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_2_IN2_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_3_IN1_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_3_IN2_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_4_IN1_PAD) | \
                                     PIN_OTYPE_PUSHPULL(MOTOR_4_IN2_PAD))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_VERYLOW(MOTOR_1_IN1_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_1_IN2_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_2_IN1_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_2_IN2_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_3_IN1_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_3_IN2_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_4_IN1_PAD) | \
                                     PIN_OSPEED_VERYLOW(MOTOR_4_IN2_PAD))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(MOTOR_1_IN1_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_1_IN2_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_2_IN1_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_2_IN2_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_3_IN1_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_3_IN2_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_4_IN1_PAD) | \
                                     PIN_PUPDR_FLOATING(MOTOR_4_IN2_PAD))
#define VAL_GPIOF_ODR               (PIN_ODR_LOW(MOTOR_1_IN1_PAD) | \
                                     PIN_ODR_LOW(MOTOR_1_IN2_PAD) | \
                                     PIN_ODR_LOW(MOTOR_2_IN1_PAD) | \
                                     PIN_ODR_LOW(MOTOR_2_IN2_PAD) | \
                                     PIN_ODR_LOW(MOTOR_3_IN1_PAD) | \
                                     PIN_ODR_LOW(MOTOR_3_IN2_PAD) | \
                                     PIN_ODR_LOW(MOTOR_4_IN1_PAD) | \
                                     PIN_ODR_LOW(MOTOR_4_IN2_PAD))
#define VAL_GPIOF_AFRL              (0U)
#define VAL_GPIOF_AFRH              (0U)

#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(ULTRASONIC_SENSOR_1_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_2_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_3_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_4_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_5_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_6_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_7_ECHO_PAD) | \
                                     PIN_MODE_INPUT(ULTRASONIC_SENSOR_8_ECHO_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_1_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_2_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_3_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_4_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_5_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_6_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_7_TRIGGER_PAD) | \
                                     PIN_MODE_OUTPUT(ULTRASONIC_SENSOR_8_TRIGGER_PAD))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_1_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_2_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_3_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_4_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_5_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_6_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_7_TRIGGER_PAD) | \
                                     PIN_OTYPE_PUSHPULL(ULTRASONIC_SENSOR_8_TRIGGER_PAD))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_1_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_2_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_3_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_4_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_5_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_6_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_7_TRIGGER_PAD) | \
                                     PIN_OSPEED_HIGH(ULTRASONIC_SENSOR_8_TRIGGER_PAD))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_1_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_2_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_3_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_4_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_5_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_6_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_7_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_8_ECHO_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_1_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_2_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_3_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_4_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_5_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_6_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_7_TRIGGER_PAD) | \
                                     PIN_PUPDR_FLOATING(ULTRASONIC_SENSOR_8_TRIGGER_PAD))
#define VAL_GPIOG_ODR               (PIN_ODR_LOW(ULTRASONIC_SENSOR_1_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_2_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_3_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_4_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_5_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_6_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_7_TRIGGER_PAD) | \
                                     PIN_ODR_LOW(ULTRASONIC_SENSOR_8_TRIGGER_PAD))
#define VAL_GPIOG_AFRL              (0U)
#define VAL_GPIOG_AFRH              (0U)

#define VAL_GPIOH_MODER             (0U)
#define VAL_GPIOH_OTYPER            (0U)
#define VAL_GPIOH_OSPEEDR           (0U)
#define VAL_GPIOH_PUPDR             (0U)
#define VAL_GPIOH_ODR               (0U)
#define VAL_GPIOH_AFRL              (0U)
#define VAL_GPIOH_AFRH              (0U)

#define VAL_GPIOI_MODER             (0U)
#define VAL_GPIOI_OTYPER            (0U)
#define VAL_GPIOI_OSPEEDR           (0U)
#define VAL_GPIOI_PUPDR             (0U)
#define VAL_GPIOI_ODR               (0U)
#define VAL_GPIOI_AFRL              (0U)
#define VAL_GPIOI_AFRH              (0U)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */
