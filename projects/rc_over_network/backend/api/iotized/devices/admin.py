from django.contrib import admin
from .models.device import Device


class DeviceAdmin(admin.ModelAdmin):
    list_display = [field.name for field in Device._meta.get_fields()]
    list_filter = [field.name for field in Device._meta.get_fields()]


admin.site.register(Device, DeviceAdmin)
