OS - Ubuntu - 22.10 LTS

1. Create SD card with above ubuntu image.
   1. While setting up image, in the settings option enable ssh with username password and also pass nw credentials
2. Might have some problem connecting with ipv4, check settings in router.
3. Check Boot, and ssh with ssh -v  'ubuntu@host'. Change password.
4. Run ansible playbook. 


Important Links
   - https://stackoverflow.com/questions/36609083/how-to-delete-current-sudoer-with-ansible