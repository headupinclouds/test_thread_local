#!/bin/bash

TOOLCHAIN=ios-10-1-arm64-dep-8-0-hid-sections

polly.py --toolchain ${TOOLCHAIN} --framework-device --reconfig --clear
