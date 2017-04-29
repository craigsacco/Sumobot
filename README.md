# About

# Hardware

* Waveshare Port407Z development board (an STM32F407ZE MCU with 512kB FLASH)
* Waveshare FT232 accessory board (a TTL-to-USB UART transceiver)
* ST-Link/V2 programmer
* HC-SR04 ultrasonic sensor integrated controller
* 2 x L298N dual DC-to-DC full bridge driver
* 4 x 12V 1A DC motor

## Pin Assignments

| Pad | Mode | Description |
| --- | --- | --- |
| PA4 | DO/PP | LED #1 |
| PA5 | DO/PP | LED #2 |
| PA6 | DO/PP | LED #3 |
| PA7 | DO/PP | LED #4 |
| PA9 | AF7/USART1 | Serial Data Interface Transmit Data |
| PA10 | AF7/USART1 | Serial Data Interface Receive Data |
| PA13 | AF0/JTAG | Debug SWDIO |
| PA14 | AF0/JTAG | Debug SWCLK |
| PB3 | AF0/JTAG | Debug SWO |
| PC14 | N/A | LSE Oscillator (32.768kHz) |
| PC15 | N/A | LSE Oscillator (32.768kHz) |
| PE9 | AF1/TIM1 | DC Motor #1 PWM Speed Control |
| PE11 | AF1/TIM1 | DC Motor #2 PWM Speed Control |
| PE13 | AF1/TIM1 | DC Motor #3 PWM Speed Control |
| PE14 | AF1/TIM1 | DC Motor #4 PWM Speed Control |
| PF0 | DO/PP | DC Motor #1 Forward Control |
| PF1 | DO/PP | DC Motor #1 Reverse Control |
| PF2 | DO/PP | DC Motor #2 Forward Control |
| PF3 | DO/PP | DC Motor #2 Reverse Control |
| PF4 | DO/PP | DC Motor #3 Forward Control |
| PF5 | DO/PP | DC Motor #3 Reverse Control |
| PF6 | DO/PP | DC Motor #4 Forward Control |
| PF7 | DO/PP | DC Motor #4 Reverse Control |
| PG0 | DO/PP | Ultrasonic Sensor #1 Trigger Control |
| PG1 | DO/PP | Ultrasonic Sensor #2 Trigger Control |
| PG2 | DO/PP | Ultrasonic Sensor #3 Trigger Control |
| PG3 | DO/PP | Ultrasonic Sensor #4 Trigger Control |
| PG4 | DO/PP | Ultrasonic Sensor #5 Trigger Control |
| PG5 | DO/PP | Ultrasonic Sensor #6 Trigger Control |
| PG6 | DO/PP | Ultrasonic Sensor #7 Trigger Control |
| PG7 | DO/PP | Ultrasonic Sensor #8 Trigger Control |
| PG8 | DI/F | Ultrasonic Sensor #1 Echo Feedback |
| PG9 | DI/F | Ultrasonic Sensor #2 Echo Feedback |
| PG10 | DI/F | Ultrasonic Sensor #3 Echo Feedback |
| PG11 | DI/F | Ultrasonic Sensor #4 Echo Feedback |
| PG12 | DI/F | Ultrasonic Sensor #5 Echo Feedback |
| PG13 | DI/F | Ultrasonic Sensor #6 Echo Feedback |
| PG14 | DI/F | Ultrasonic Sensor #7 Echo Feedback |
| PG15 | DI/F | Ultrasonic Sensor #8 Echo Feedback |
| PH0 | N/A | HSE Oscillator (8MHz) |
| PH1 | N/A | HSE Oscillator (8MHz) |

# Environment

* Ubuntu Linux 16.04.2 LTS or Linux Mint 18.2
* Following packages from APT
  * build-essential
  * git
  * openocd
* Following packages from third-party PPAs
  * GNU ARM Embedded Toolchain (https://launchpad.net/~team-gcc-arm-embedded/+archive/ubuntu/ppa)

# Usage

## Build

Clone the repository as well as submodules

Run `make` to build everything

## Flash

If you haven't built stlink yet, run the following in the *lib/stlink* directory:
~~~~
make clean
make all
sudo cp -a etc/udev/rules.d/* /etc/udev/rules.d
sudo udevadm control --reload
~~~~

In the repository root, run the following:
~~~~
./flash.sh
~~~~

## Debug

In the repository root, run the following:
~~~~
openocd
~~~~

Using a second terminal window, run the following:
~~~~
arm-none-eabi-gdb
~~~~

Run the following commands in GDB to load and run a new binary:
~~~~
target remote :3333
monitor halt
load build/sumobot.elf
continue
~~~~

From this point on, you can use the standard set of GDB commands to debug your application
