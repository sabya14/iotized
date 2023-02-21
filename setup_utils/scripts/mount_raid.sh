#!/bin/sh

user=${1:-'pi'}

# Skip step if file system already exists
mkfs.ext4 -v -m .1 -b 4096 -E stride=32,stripe-width=64 /dev/md0
mkdir /mnt/raidx
mount /dev/md0 /mnt/raidx
chown $user:$user /mnt/raidx
ls -la /mnt/raidx
update-initramfs -u
exit