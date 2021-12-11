ARCHITECTURE ->
    GOOGLE SHEETS -> PYTHON SERVICE RUNNING IN RASPBERRY -> PICKUP CHANGES -> DUMP TO MQTT -> MQTT WILL SEND TO ARDUINO
    

RASPBERRY SETUP NOTES
 Clean install of ubuntu -> Use raspberry pi imager app. Link -> [https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview][Install ubuntu in raspberry pi]
 1. Connect to Wifi ->
  In sd card change network config to ->
    network:
      wifis:
        wlan0:
          dhcp4: true
          optional: true
          access-points:
            "Your WiFi Name":
              password: "YourSecret"

  If connection fails,
   1. Add REGDOMAIN=IN or US to -> sudo vim /etc/default/crda 
   2. go to cd /etc/netplan and follow thread -> [https://askubuntu.com/questions/1291424/failed-to-start-netplan-wpa-wlan0-sevice-unit-netplan-wpa-wlan0-service-not-fou][Connect to 5ghz wifi]
 
 2. Configure SSH
    Create rsa key.   
    Transfer key to raspberry by - ssh-copy-id <username>@?<host> -p<ssh port>
 
 3. 
 
 2. Docker setup -
  ```
    sudo apt  install docker.io
    sudo usermod -aG docker [pi-username]
    
    sudo apt  install docker-compose
    
 ```

 3. Kafka Commands
    ```
    list topics opt/kafka/bin/kafka-topics.sh --list --zookeeper 192.168.0.120:2181
    create topics opt/kafka/bin/kafka-topics.sh --create --topic mqtt.iot --replication-factor 1   --partitions 2  --zookeeper 192.168.0.120:2181
    ```
    
Start Data Collection Service
    ```
    sudo systemctl daemon-reload
    sudo systemctl enable data_collector.service
    sudo systemctl start data_collector.service
    
    #Check status
    sudo systemctl status test-py.service
    ```
    


SOURCES ->

For bluetooth - HC05 follow steps from - https://dev.to/ivanmoreno/how-to-connect-raspberry-pi-with-hc-05-bluetooth-module-arduino-programm-3h7a
Notes -> Scan takes time, look for device with name hc-05/06




[Install ubuntu in raspberry pi]: https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview

[Connect to 5ghz wifi]: https://askubuntu.com/questions/1291424/failed-to-start-netplan-wpa-wlan0-sevice-unit-netplan-wpa-wlan0-service-not-fou