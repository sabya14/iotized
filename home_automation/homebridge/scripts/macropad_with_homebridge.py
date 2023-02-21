import json
import time
from multiprocessing.connection import Listener

import keyboard
import requests
import sys
import logging

LOGIN_URL = "/api/auth/login"
AUTH_CHECK = "/api/auth/check"
ACCESSORIES_CHECK = "/api/accessories"
root = logging.getLogger()

UUID = {
    "FAN": "9db917b003b4de769675cc0d78358d62648b4694824f0a1ee903964e5d2c9308",
    "TUBE": "6c0e02c1ce764ae3630eb1915924bf51699d5cfea1f46d2056926272680de19d",
    "LAPTOP_STAND_LIGHT": "120b5afc26fafb99642c6d97b3ea9a220366b5592a8564ef11b5c5147865b9bb",
    "MONITOR_LIGHT": "6b6048a240f1c3869b469748a1bd1d8e95a24f3952dd243e6239130bd6695d65",
    "TV_LIGHT": "4329710622e073852327a4958c60744578123528b4142971c2a48f245057bd6f",
    "CHILL_MODE_TRIGGER": "b0dcacdf8ce839f3db9842e40b3590b058e44fbebe8a80be82028ad1f9b6a4e8",
    "SLEEP_MODE_TRIGGER": "f8445985b54eb07dce3c90afa21c018149995106e56f1d19437d74665bb4cdd2"
}

SWITCH_OFF_DATA = {
    "characteristicType": 'On',
    "value": "0"
}

SWITCH_ON_DATA = {
    "characteristicType": 'On',
    "value": "1"
}


def configure_logger():
    root.setLevel(logging.DEBUG)
    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    handler.setFormatter(formatter)
    root.addHandler(handler)


class HomeBridge:
    def __init__(self, url, username, password):
        self.url = url
        self.username = username
        self.password = password
        self.token = None
        self.accessories = None
        configure_logger()
        self.authenticate()
        self.set_accessories()

    def authenticate(self):
        resp = requests.post(self.url + LOGIN_URL, data={
            "username": self.username,
            "password": self.password,
            'headers': {'Accept': '*/*',
                        'Content-Type': 'application/json',
                        },
        })
        if resp:
            self.token = resp.json()["access_token"]
            root.info("Logged in, saved access token")

    def check_auth(self):
        resp = requests.get(self.url + AUTH_CHECK,
                            headers=self.get_request_headers(),
                            )
        if not resp:
            logging.info("Re authenticating")
            self.authenticate()
        else:
            print("Authenticated")

    def get_request_headers(self):
        return {'Accept': '*/*',
                'Content-Type': 'application/json',
                'Authorization': f'bearer {self.token}'
                }

    def set_accessories(self):
        resp = requests.get(self.url + ACCESSORIES_CHECK,
                            headers=self.get_request_headers(),
                            )
        self.accessories = resp.json()

    def get_accessory_power_state_by_uuid(self, uuid):
        resp = requests.get(self.url + ACCESSORIES_CHECK + "/" + uuid,
                            headers=self.get_request_headers(),
                            )
        power_state = None
        if resp:
            power_state = resp.json()["values"]["On"]
            print("Power state of device: " + str(power_state))
        else:
            root.error("Could get power state of device")
        return power_state

    def set_accessory_value(self, uuid, value):
        resp = requests.put(self.url + ACCESSORIES_CHECK + "/" + uuid,
                            data=json.dumps(value),
                            headers=self.get_request_headers(),
                            )
        if resp:
            root.info("New value set for: " + uuid)
        else:
            root.error("Could not change value for: " + uuid)

    def toggle_power_state_by_uuid(self, uuid):
        current_power_state = self.get_accessory_power_state_by_uuid(uuid)
        logging.info("Current State: " + str(current_power_state) + " Changing to: " + str(not current_power_state))
        self.set_accessory_value(uuid, value={
            "characteristicType": 'On',
            "value": not current_power_state
        })


class KeyEventCapturer:
    KEY_MAPPING = {
        1: UUID["FAN"],
        2: UUID["TUBE"],
        3: UUID["CHILL_MODE_TRIGGER"],
        4: UUID["SLEEP_MODE_TRIGGER"],
        '1': UUID["FAN"],
        '2': UUID["TUBE"],
        '3': UUID["CHILL_MODE_TRIGGER"],
        '4': UUID["SLEEP_MODE_TRIGGER"],

    }

    def __init__(self, home_bridge):
        self.home_bridge = home_bridge

    def start_listening(self):
        while 1:
            key = keyboard.read_key()
            root.info("Pressed key " + str(key))
            print(key)
            if key in KeyEventCapturer.KEY_MAPPING:
                print("Yes found")
                try:
                    self.home_bridge.authenticate() # Better this
                    self.home_bridge.toggle_power_state_by_uuid(KeyEventCapturer.KEY_MAPPING[key])
                except Exception:
                    pass
            else:
                print("Not found")
            time.sleep(0.5)
            print("Listening")


if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) > 3:
        # test run
        home_bridge = HomeBridge(url=args[0], username=args[1], password=args[2])
        print(home_bridge.accessories)
        exit(0)

    time.sleep(10)
    while 1:
        try:
            home_bridge = HomeBridge(url=args[0], username=args[1], password=args[2])
            capturer = KeyEventCapturer(home_bridge)
            capturer.start_listening()
        except Exception as e:
            print(e)
            time.sleep(1)
            pass

