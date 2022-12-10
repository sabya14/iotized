from django.urls import path
from devices.views.devices import DevicesListCreateAPIView, DevicesListRUDAPIView
from devices.views.modes import ModesListCreateAPIView, ModesListRUDAPIView

app_name = 'devices'

urlpatterns = [
    path('', DevicesListCreateAPIView.as_view(), name="list"),
    path('name=<slug:pk>/', DevicesListRUDAPIView.as_view(), name="detail"),
    path('mode/', ModesListCreateAPIView.as_view(), name="list"),
    path('mode/<int:pk>/', ModesListRUDAPIView.as_view(), name="detail"),
]
