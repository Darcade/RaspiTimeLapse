#!/bin/sh

gcc -o raspitimelapse raspitimelapse.c -L/usr/local/lib -lwiringPi -lwiringPiDev -lpthread -lm
