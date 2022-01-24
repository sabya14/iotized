STEPS TO RUN PLUGIN ->
   * Enable remote dev in idea, and sync to folder or copy entire folder.
   * Then use -> sudo npm install -g homebridge-universal-iot-plugin/
   * Then cd into the folder and npm run build
   * Then `npm run watch` to continuously build and watch.

Example Config -> 
```
{
    "bridge": {
        "name": "Homebridge 82DB",
        "username": "0E:C2:B6:5D:82:DB",
        "port": 51469,
        "pin": "702-56-838"
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
                    "id": "1",
                    "name": "Bulb",
                    "type": "Switch",
                    "port": "rfcomm0",
                    "debug": true
                }
            ]
        }
    ]
}
```

Bluetooth Setup - 
