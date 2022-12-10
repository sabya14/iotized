from rest_framework.generics import ListCreateAPIView, RetrieveUpdateDestroyAPIView

from devices.models.device import Device
from devices.serializers.devices import DevicesSerializer


class DevicesListCreateAPIView(ListCreateAPIView):
    queryset = Device.objects.all()
    serializer_class = DevicesSerializer


class DevicesListRUDAPIView(RetrieveUpdateDestroyAPIView):
    queryset = Device.objects.all()
    serializer_class = DevicesSerializer
