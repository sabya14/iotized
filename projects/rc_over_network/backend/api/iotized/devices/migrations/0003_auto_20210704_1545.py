# Generated by Django 3.2.5 on 2021-07-04 15:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('devices', '0002_rename_devices_device'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='device',
            name='id',
        ),
        migrations.AlterField(
            model_name='device',
            name='name',
            field=models.CharField(max_length=60, primary_key=True, serialize=False),
        ),
    ]