# backup script for Raspberry Pi
#
# electronut.in
# 

#!/bin/bash
echo Backing up RPi \#1...

# set this to Raspberry Pi IP address
PI_ADDR="192.168.1.165"

# set this to Raspberry Pi code directory
# note that the trailing / is important with rsync
PI_DIR="/"

# set this to local code (backup) directory
BKUP_DIR="/Users/neel/Documents/Work/backups/rpi-1/"

# run rsync
# use this first to test: 
# rsync -uvrn pi@$PI_ADDR:$PI_DIR $BKUP_DIR
rsync -uvr --rsync-path="sudo rsync" --exclude=/proc/ --exclude=/sys/ --exclude=/dev/ --exclude=/boot/ --exclude=/tmp/ --exclude=/run/ --exclude=/mnt/ --exclude=/media/ --exclude=home/pi/.cache/ --exclude=/lost+found neel@$PI_ADDR:$PI_DIR $BKUP_DIR

echo ...
echo done.

# play sound - optional
afplay /System/Library/Sounds/Basso.aiff 