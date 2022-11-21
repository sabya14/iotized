import requests

LOGIN_URL = "/api/auth/login"


class HomeBridge:
    def __init__(self, url, username, password):
        self.url = url
        self.username = username
        self.password = password


    def _authenticate(self):
        resp = requests.post(self.url + LOGIN_URL, data={
            "username": self.username,
            "password": self.password,

        })
        if resp:
            print(resp)



