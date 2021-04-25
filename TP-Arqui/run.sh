#!/bin/bash
qemu-system-x86_64 -hda  Image/x64BareBonesImage.qcow2 -m 512 -rtc clock=host -rtc base=localtime -rtc clock=vm