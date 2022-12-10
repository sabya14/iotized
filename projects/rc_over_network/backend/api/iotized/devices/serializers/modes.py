from rest_framework import serializers

from devices.models.device import Device
from devices.models.mode import Mode


class ModesSerializer(serializers.ModelSerializer):
    class Meta:
        model = Mode
        fields = "__all__"
