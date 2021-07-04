# device.py
from django.db import models

from devices.models.device import Device
from django.utils.translation import ugettext_lazy as _


class Mode(models.Model):
    device = models.ForeignKey(Device, on_delete=models.CASCADE, related_name='modes')
    name = models.CharField(_("Name"), max_length=255)
    data = models.JSONField(_("Data"), default={})
    config = models.JSONField(_("Config"), default={})

    class Meta:
        verbose_name = _("DeviceMode")
        unique_together = (('device', 'name', 'data', "config"),)
