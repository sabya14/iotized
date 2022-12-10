cd /backend/api/iotized
python manage.py makemigrations && python manage.py migrate && python manage.py runserver 192.168.0.120:8000
cd ../scripts/api_data_fetcher
python3 main.py


