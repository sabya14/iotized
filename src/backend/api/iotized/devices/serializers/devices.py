from rest_framework import serializers

from devices.models.device import Device
from devices.serializers.modes import ModesSerializer


class DevicesSerializer(serializers.ModelSerializer):
    modes = ModesSerializer(many=True)

    class Meta:
        model = Device
        fields = '__all__'
