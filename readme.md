ARCHITECTURE ->
    GOOGLE SHEETS -> PYTHON SERVICE RUNNING IN RASPBERRY -> PICKUP CHANGES -> DUMP TO MQTT -> MQTT WILL SEND TO ARDUINO
    

RASPBERRY SETUP NOTES
 1. Docker setup -
  ```
    sudo apt  install docker.io
    sudo usermod -aG docker [pi-username]
    
    sudo apt  install docker-compose
    
 ```

 2. Kafka Commands
    ```
    list topics opt/kafka/bin/kafka-topics.sh --list --zookeeper 192.168.0.120:2181
    create topics opt/kafka/bin/kafka-topics.sh --create --topic mqtt.iot --replication-factor 1   --partitions 2  --zookeeper 192.168.0.120:2181
    ```