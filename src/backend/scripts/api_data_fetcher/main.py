import json
import time

import requests
import serial

LAST_COMMAND = '1'
SERIAL_ENABLED = False
DEVICES_LAST_MODIFIED = {}


def send_data_to_mqtt_broker(device_name, mode_data_dict):
    import paho.mqtt.client as mqtt

    client = mqtt.Client()
    client.connect("192.168.0.120", 1883, 60)
    print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")
    client.publish(device_name, json.dumps(mode_data_dict))


def send_data_to_bluetooth(device_name, mode_data_dict):
    if not SERIAL_ENABLED:
        print("Cant send data to bluetooth device: ",device_name)
        return

    command = mode_data_dict["mode_data"]["data"]["command"]
    port.write(command.encode())
    print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")


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
                "config": mode["config"],
                "last_modified": mode["modified_date"]
            }

            if "bluetoothOnly" in mode["config"]:
                devices_data[device][mode["name"]]["bluetoothOnly"] = True
            add_data_only_if_new_event_event_received(device, devices_data, mode)
    return devices_data


def add_data_only_if_new_event_event_received(device, devices_data, mode):
    if f"{device}-{mode['name']}" not in DEVICES_LAST_MODIFIED:
        DEVICES_LAST_MODIFIED[f"{device}-{mode['name']}"] = mode["modified_date"]
    elif DEVICES_LAST_MODIFIED[f"{device}-{mode['name']}"] == mode["modified_date"]:
        print(f"No new data for {device}-{mode['name']}")
        del devices_data[device][mode["name"]]
    else:
        DEVICES_LAST_MODIFIED[f"{device}-{mode['name']}"] = mode["modified_date"]


if __name__ == '__main__':

    try:
        port = serial.Serial("/dev/rfcomm0", baudrate=9600)
        SERIAL_ENABLED = False
    except serial.SerialException as e:
        pass

    while True:
        all_devices_data = get_data_from_api("http://192.168.0.245:8000/api/devices/")
        for device_name, device_data in all_devices_data.items():
            for mode, mode_data in device_data.items():
                if "bluetoothOnly" in mode_data:
                    send_data_to_bluetooth(device_name, {"mode": mode, "mode_data": mode_data})
                else:
                    send_data_to_mqtt_broker(device_name, {"mode": mode, "mode_data": mode_data})
        time.sleep(0.05)
