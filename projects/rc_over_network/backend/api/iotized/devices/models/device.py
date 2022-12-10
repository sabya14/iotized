# device.py
from django.db import models

from base.model import BaseModel


class Device(BaseModel):
    name = models.CharField(max_length=60, primary_key=True)
    active = models.BooleanField(default=False)
    desc = models.CharField(max_length=100)

    def __str__(self):
        return self.name
