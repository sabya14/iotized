#!/bin/sh


dev1=${1:-'/dev/sda1'}
dev2=${2:-'/dev/sdb1'}

echo "Dev 1 {$dev1}"
echo "Dev 1 {$dev2}"

apt-get update
apt-get upgrade
apt-get install madm


mdadm -Esv
mdadm  --stop /dev/md*
mdadm --create --verbose /dev/md0 --level=mirror --raid-devices=2 $dev1 $dev2
mdadm --detail --scan >> /etc/mdadm/mdadm.conf
exit

