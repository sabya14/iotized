Command to run playbook -  ansible-playbook raspberry.yml --ask-pass -bK
--ask-pass - For ssh
-bK - for root



Issues with Docker-Compose Install, check this link -
https://stackoverflow.com/questions/58747879/docker-compose-usr-local-bin-docker-compose-line-1-not-command-not-found
Correct fetch destination - https://github.com/docker/compose/releases/download/v2.1.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose