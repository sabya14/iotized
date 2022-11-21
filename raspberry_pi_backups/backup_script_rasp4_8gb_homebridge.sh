ssh neel@192.168.1.165 "sudo dd if=/dev/mmcblk0 bs=1M | gzip -" | dd of=/Users/neel/Documents/Work/iot-mqtt-rasp/raspberry_pi_backups/backup_script_rasp4_8gb_homebridge/pi_backup.gz
