# About

# Hardware

* A Waveshare Port407Z development board (an STM32F407ZE MCU with 512kB FLASH)
* Ultrasonic Sensor

## Pin Assignments

| Pad | Mode | Description |
| --- | --- | --- |
| PA4 | DO/PP | LED #1 |
| PA5 | DO/PP | LED #2 |
| PA6 | DO/PP | LED #3 |
| PA7 | DO/PP | LED #4 |
| PA13 | AF0 | Debug SWDIO |
| PA14 | AF0 | Debug SWCLK |
| PB3 | AF0 | Debug SWO |
| PE0 | DO/PP | Ultrasonic Sensor Common Trigger |
| PE1 | DI/F | Ultrasonic Sensor #1 Echo |

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
Run <code>make</code> to build everything

## Flash

If you haven't built stlink yet, run the following in the *lib/stlink* directory:
<code>
make clean
make all
sudo cp -a etc/udev/rules.d/* /etc/udev/rules.d
sudo udevadm control --reload
</code>
In the repository root, run the following:
<code>
./flash.sh
</code>

## Debug

In the repository root, run the following:
<code>
openocd
</code>
Using a second terminal window, run the following:
<code>
arm-none-eabi-gdb
</code>
Run the following commands in GDB to load and run a new binary:
<code>
target remote :3333
monitor halt
load build/sumobot.elf
continue
</code>
From this point on, you can use the standard set of GDB commands to debug your application
