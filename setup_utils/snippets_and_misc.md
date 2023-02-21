## SNIPPETS

Kafka Commands
   ```
   list topics opt/kafka/bin/kafka-topics.sh --list --zookeeper 192.168.0.120:2181
   create topics opt/kafka/bin/kafka-topics.sh --create --topic mqtt.iot --replication-factor 1   --partitions 2  --zookeeper 192.168.0.120:2181
   ```
    
Start Data Collection Service

    ```
        sudo systemctl daemon-reload
        sudo systemctl enable data_collector.service
        sudo systemctl start data_collector.service
        # Check status
        sudo systemctl status test-py.service
    ```
    
OpenWrt -
    Package update not working try - opkg update --no-check-certificate