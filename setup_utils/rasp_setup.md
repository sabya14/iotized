Raspberry OS 64 BIT

RASPBERRY SETUP NOTES Clean install of ubuntu -> Use raspberry pi imager app. 
Link -> [https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview][Install ubuntu in raspberry pi]

1. Connect to Wifi ->
   In sd card change network config to ->
   network:
   wifis:
   wlan0:
   dhcp4: true optional: true access-points:
   "Your WiFi Name":
   password: "YourSecret"
   Then -
    1. sudo netplan generate
    2. sudo netplan apply

2. If connection fails,

   1. Add REGDOMAIN=IN or US to -> sudo vim /etc/default/crda
   2. go to cd /etc/netplan and follow thread
      -> [https://askubuntu.com/questions/1291424/failed-to-start-netplan-wpa-wlan0-sevice-unit-netplan-wpa-wlan0-service-not-fou][Connect to 5ghz wifi]

3. Configure SSH Create rsa key.   
   Transfer key to raspberry by - ssh-copy-id <username>@?<host> -p<ssh port>

4. Docker setup -
      ```
        sudo apt  install docker.io
        sudo usermod -aG docker [pi-username]
        
        sudo apt  install docker-compose
        
     ```


##  Important Links

1. Enable 4k - https://www.makeuseof.com/run-your-raspberry-pi-at-4k-60hz/
2. 5ghz - Change wifi local to US, IN does not work
3. Security Setup - https://raspberrytips.com/security-tips-raspberry-pi/
4. Raid Setup - https://gist.github.com/leandrofilipe/f9636be272f97d414652ce1f21e6b1f4
