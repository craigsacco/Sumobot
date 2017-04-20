#!/bin/bash

lib/stlink/build/Release/st-flash write build/sumobot.bin 0x08000000
