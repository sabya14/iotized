#!/bin/bash
rfcomm bind rfcomm0 00:20:12:08:9E:98
chmod a+rw /dev/rfcomm0
rfcomm bind rfcomm1 00:20:10:08:50:70
chmod a+rw /dev/rfcomm1