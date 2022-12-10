from rest_framework.generics import ListCreateAPIView, RetrieveUpdateDestroyAPIView

from devices.models.mode import Mode
from devices.serializers.modes import ModesSerializer


class ModesListCreateAPIView(ListCreateAPIView):
    queryset = Mode.objects.all()
    serializer_class = ModesSerializer


class ModesListRUDAPIView(RetrieveUpdateDestroyAPIView):
    queryset = Mode.objects.all()
    serializer_class = ModesSerializer
