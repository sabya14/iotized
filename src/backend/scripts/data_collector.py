from __future__ import print_function

import json
import os
import time

from googleapiclient.discovery import build
from google.oauth2.credentials import Credentials
from google.oauth2.service_account import Credentials

SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

SAMPLE_SPREADSHEET_ID = '1R_w-4oZnF-lTR7MQALLo4cEexyVGxA5QulPRAZ6Ol4g'
RANGE_NAME = 'Direction!A1:D5'


def send_data_to_mqtt_broker(device_name, mode_data_dict):
    import paho.mqtt.client as mqtt

    client = mqtt.Client()
    client.connect("192.168.0.120", 1883, 60)
    print(f"Sending to {device_name}: mode_data_dict={mode_data_dict}")
    client.publish(device_name, json.dumps(mode_data_dict))


def get_data_from_sheet(sheet):
    """Shows basic usage of the Sheets API.
    Prints values from a sample spreadsheet.
    """
    values = get_sheet_values(sheet)
    if not values:
        return None
    else:
        devices_data = {}
        for (row_number, row) in enumerate(values):
            if row_number:
                device = row[0]
                if device not in devices_data:
                    devices_data[device] = {}
                mode = row[1]
                mode_data = row[2]
                config = row[3]
                devices_data[device][mode] = {
                    "data": mode_data,
                    "config": config
                }
        return devices_data


def get_sheet_values(sheet):
    result = sheet.values().get(
        spreadsheetId=SAMPLE_SPREADSHEET_ID,
        range=RANGE_NAME,

    ).execute()
    values = result.get('values', [])
    return values


def authenticate_sheet():
    key_path = os.environ.get("SHEET_KEY")
    creds = Credentials.from_service_account_file(key_path)
    service = build('sheets', 'v4', credentials=creds)
    sheet = service.spreadsheets()
    return sheet


if __name__ == '__main__':
    sheet = authenticate_sheet()
    while True:
        devices_data_map = get_data_from_sheet(sheet)
        for device_name, device_data in devices_data_map.items():
            for mode, mode_data in device_data.items():
                send_data_to_mqtt_broker(device_name, {"mode": mode, "mode_data": mode_data})
        time.sleep(1)
