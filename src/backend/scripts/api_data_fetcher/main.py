import json
import time

import requests
import serial

LAST_COMMAND = '1'


def send_data_to_mqtt_broker(device_name, mode_data_dict):
    import paho.mqtt.client as mqtt

    client = mqtt.Client()
    client.connect("192.168.0.120", 1883, 60)
    print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")
    client.publish(device_name, json.dumps(mode_data_dict))


def send_data_to_bluetooth(device_name, mode_data_dict):
    global LAST_COMMAND
    # pass from api
    command = mode_data_dict["mode_data"]["data"]["command"]
    if LAST_COMMAND != command:
        print(command.encode())
        port.write(command.encode())
        print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")
    LAST_COMMAND = command


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
            if "bluetoothOnly" in mode["config"]:
                devices_data[device][mode["name"]]["bluetoothOnly"] = True
    return devices_data


if __name__ == '__main__':
    port = serial.Serial("/dev/rfcomm0", baudrate=9600)

    while True:
        devices_data_map = get_data_from_api("http://192.168.0.245:8000/api/devices/")
        for device_name, device_data in devices_data_map.items():
            for mode, mode_data in device_data.items():
                if "bluetoothOnly" in mode_data:
                    send_data_to_bluetooth(device_name, {"mode": mode, "mode_data": mode_data})
                else:
                    send_data_to_mqtt_broker(device_name, {"mode": mode, "mode_data": mode_data})
        time.sleep(0.05)
