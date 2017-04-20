/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef BOARD_H
#define BOARD_H

/*
 * Board identifier.
 */
#define BOARD_NAME                  "Generic STM32F407 board using SWD/HSE/LSE"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F407xx

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The following pins will be setup:
 *  * PA13/PA14/PB3 for SWD debug (AF0)
 *  * all other pins are digital inputs
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(13U) | PIN_MODE_ALTERNATE(14U))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(13U) | PIN_OTYPE_PUSHPULL(14U))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(13U) | PIN_OSPEED_HIGH(14U))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(13U) | PIN_PUPDR_FLOATING(14U))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(13U) | PIN_ODR_HIGH(14U))
#define VAL_GPIOA_AFRL              (0U)
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(13U, 0U) | PIN_AFIO_AF(14U, 0U))

#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(3U))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(3U))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(3U))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(3U))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(3U))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(3U, 0U))
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

#define VAL_GPIOE_MODER             (0U)
#define VAL_GPIOE_OTYPER            (0U)
#define VAL_GPIOE_OSPEEDR           (0U)
#define VAL_GPIOE_PUPDR             (0U)
#define VAL_GPIOE_ODR               (0U)
#define VAL_GPIOE_AFRL              (0U)
#define VAL_GPIOE_AFRH              (0U)

#define VAL_GPIOF_MODER             (0U)
#define VAL_GPIOF_OTYPER            (0U)
#define VAL_GPIOF_OSPEEDR           (0U)
#define VAL_GPIOF_PUPDR             (0U)
#define VAL_GPIOF_ODR               (0U)
#define VAL_GPIOF_AFRL              (0U)
#define VAL_GPIOF_AFRH              (0U)

#define VAL_GPIOG_MODER             (0U)
#define VAL_GPIOG_OTYPER            (0U)
#define VAL_GPIOG_OSPEEDR           (0U)
#define VAL_GPIOG_PUPDR             (0U)
#define VAL_GPIOG_ODR               (0U)
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

#endif /* BOARD_H */
