STEPS TO RUN PLUGIN ->
   * Update node to >14
   * Follow this blindly - https://stackoverflow.com/questions/10075990/upgrading-node-js-to-latest-version
   * npm cache clean -f
     npm install -g n
     n stable

   * Enable remote dev in idea, and sync to folder or copy entire folder.
   * Then use -> sudo npm install -g homebridge-universal-iot-plugin//
   * npm install typescript -g
   * Then cd into the folder and npm run build
   * Then `npm run watch` to continuously build and watch.




Device 00:20:10:08:50:70 HC-05
Device 00:20:12:08:9E:98 HC-06
Device 00:20:12:08:A4:D6 HC-06
Example Config -> 
```
{
    "bridge": {
        "name": "Homebridge 6D55",
        "username": "0E:6F:02:1F:6D:55",
        "port": 51952,
        "pin": "479-40-305",
        "advertiser": "bonjour-hap"
    },
    "accessories": [],
    "platforms": [
        {
            "name": "Config",
            "port": 8581,
            "platform": "config"
        },
        {
            "name": "UniversalIOTPlugin",
            "platform": "UniversalIOTPlugin",
            "debug": true,
            "devices_info": [
                {
                    "id": "4",
                    "name": "Ambilight-1",
                    "type": "lightBulb",
                    "port": "/dev/rfcomm3",
                    "debug": true
                },
                {
                    "id": "2",
                    "name": "Fan",
                    "type": "Switch",
                    "port": "/dev/rfcomm4",
                    "debug": true
                },
                {
                    "id": "3",
                    "name": "Tube",
                    "type": "Switch",
                    "port": "/dev/rfcomm5",
                    "debug": true
                }
            ]
        }
    ]
}
```

Service creation for rfcomm bind at startup - https://unix.stackexchange.com/questions/645914/running-a-sudo-command-automatically-on-startup

