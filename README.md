# About

# Hardware

* A Waveshare Port407Z development board (an STM32F407ZE MCU with 512kB FLASH)
* ST-Link/V2 programmer
* HC-SR04 ultrasonic sensor integrated controller

## Pin Assignments

| Pad | Mode | Description |
| --- | --- | --- |
| PA4 | DO/PP | LED #1 |
| PA5 | DO/PP | LED #2 |
| PA6 | DO/PP | LED #3 |
| PA7 | DO/PP | LED #4 |
| PA9 | AF? | USART1 Transmit Data |
| PA10 | AF? | USART1 Receive Data |
| PA13 | AF0 | Debug SWDIO |
| PA14 | AF0 | Debug SWCLK |
| PB3 | AF0 | Debug SWO |
| PC14 | N/A | LSE Oscillator (32.768kHz) |
| PC15 | N/A | LSE Oscillator (32.768kHz) |
| PD0 | DO/PP | Ultrasonic Sensor Common Trigger |
| PD1 | DI/F | Ultrasonic Sensor #1 Echo |
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
