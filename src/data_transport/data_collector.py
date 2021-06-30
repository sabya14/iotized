from __future__ import print_function
import os
import time

from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google.oauth2.service_account import Credentials

SCOPES = ['https://www.googleapis.com/auth/spreadsheets.readonly']

SAMPLE_SPREADSHEET_ID = '1R_w-4oZnF-lTR7MQALLo4cEexyVGxA5QulPRAZ6Ol4g'
RANGE_NAME = 'Sheet1!A1:B4'


def send_data_to_mqtt_broker(topic, data):
    import paho.mqtt.client as mqtt

    client = mqtt.Client()
    client.connect("192.168.0.120", 1883, 60)
    print(f"Sending to {topic}: data={data}")
    client.publish(topic, data)


def get_data_from_sheet(sheet):
    """Shows basic usage of the Sheets API.
    Prints values from a sample spreadsheet.
    """
    values = get_sheet_values(sheet)
    if not values:
        return None
    else:
        data = {}
        for (row_number, row) in enumerate(values):
            print(row_number, row)
            if row_number:
                data[row[0]] = row[1]

        return data


def get_sheet_values(sheet):

    result = sheet.values().get(
        spreadsheetId=SAMPLE_SPREADSHEET_ID,
        range=RANGE_NAME
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
        device_data_map = get_data_from_sheet(sheet)
        for device, data in device_data_map.items():
            send_data_to_mqtt_broker(device, data)
        time.sleep(0.5)