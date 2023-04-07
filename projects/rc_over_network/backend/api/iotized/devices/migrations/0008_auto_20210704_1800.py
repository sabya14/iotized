# Generated by Django 3.2.5 on 2021-07-04 18:00

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('devices', '0007_alter_mode_device'),
    ]

    operations = [
        migrations.AddField(
            model_name='mode',
            name='config',
            field=models.JSONField(default={}, verbose_name='Config'),
        ),
        migrations.AlterUniqueTogether(
            name='mode',
            unique_together={('device', 'name', 'data', 'config')},
        ),
    ]