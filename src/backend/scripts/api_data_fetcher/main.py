import json
import time

import requests


def send_data_to_mqtt_broker(device_name, mode_data_dict):
    import paho.mqtt.client as mqtt

    client = mqtt.Client()
    client.connect("192.168.0.120", 1883, 60)
    print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")
    client.publish(device_name, json.dumps(mode_data_dict))


def get_data_from_api(url):
    response = requests.get(url)
    data = response.json()
    devices_data = {}
    for device_data_row in data:
        device = device_data_row["name"]
        if device not in devices_data:
            devices_data[device] = {}
        for mode in device_data_row["modes"]:
            devices_data[device][mode["name"]] = {
                "data": mode["data"],
                "config": mode["config"]
            }
    return devices_data

#Sending to arduino-1: mode_data_dict={'mode': 'car', 'mode_data': {'data': 'forward', 'config': '{"speed":1}'}}
#Sending to arduino-1: mode_data_dict={'mode': 'car', 'mode_data': {'data': 'forward', 'config': '{"speed":1}'}}
#Sending to arduino-1: mode_data_dict={'mode': 'car', 'mode_data': {'data': 'forward', 'config': '{"speed": 0.3}'}}
#Sending to arduino-1: mode_data_dict={'mode': 'car', 'mode_data': {'data': 'right', 'config': '"speed": 0.3'}}
#Sending to arduino-1: mode_data_dict={'mode': 'car', 'mode_data': {'data': 'forward', 'config': '{"speed":1}'}}
if __name__ == '__main__':
    while True:
        devices_data_map = get_data_from_api("http://192.168.0.245:8000/api/devices/")
        for device_name, device_data in devices_data_map.items():
            for mode, mode_data in device_data.items():
                send_data_to_mqtt_broker(device_name, {"mode": mode, "mode_data": mode_data})
        time.sleep(0.15)
