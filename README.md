<div align="center">
  <h1>VTigerCRM customized by Dibaia</h1>
</div>
<div align="center">
  <strong>The perfect solution for small and medium-sized companies</strong>
</div>

<div align="center">
This repository is based on the version of VTigerCRM v8.2. 
The aim of this project is to help companies that need a solution with well-defined business rules.
</div>

<br>

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/V7V7VPS3W) OR [!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/kapsule_code)

<br>

## Web Server installation

```bash
sudo apt update
sudo apt install nginx
```

We verify the services after installation

```bash
sudo systemctl stop nginx.service
sudo systemctl start nginx.service
sudo systemctl enable nginx.service
```

## MariaDB database installation

```bash
sudo apt-get install mariadb-server mariadb-client
```

We verify the services after installation

```bash
sudo systemctl stop mysql.service
sudo systemctl start mysql.service
sudo systemctl enable mysql.service
```

We activate the security of access to the database.

```bash
sudo mysql_secure_installation
```

We specify the following values in the different questions.

```bash
Enter current password for root (enter for none): Just press the Enter
Set root password? [Y/n]: Y
New password: Enter password
Re-enter new password: Repeat password
Remove anonymous users? [Y/n]: Y
Disallow root login remotely? [Y/n]: Y
Remove test database and access to it? [Y/n]: Y
Reload privilege tables now? [Y/n]: Y
```

Restart the service

```bash
sudo systemctl restart mysql.service
```

## Installation of PHP on NGINX web server

```bash
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:ondrej/php

sudo apt update

sudo apt install php8.2-fpm php8.2-common php8.2-mbstring php8.2-xmlrpc php8.2-soap php8.2-gd php8.2-xml php8.2-intl php8.2-mysql php8.2-cli php8.2-mcrypt php8.2-ldap php8.2-zip php8.2-curl
```

Editing php.ini file to define the correct values to work with vtigercrm

```bash
sudo nano /etc/php/8.2/fpm/php.ini
```

- file_uploads = On
- allow_url_fopen = On
- memory_limit = 256M
- upload_max_filesize = 64M
- max_execution_time = 30
- display_errors = Off
- cgi.fix_pathinfo = 0
- max_input_vars = 1500

## Database and user creation

```sql
sudo mysql -u root -p

CREATE DATABASE vtigercrm;
CREATE USER 'vtuser'@'localhost' IDENTIFIED BY 'new_password_here';
GRANT ALL ON vtigercrm.* TO 'vtuser'@'localhost' IDENTIFIED BY 'user_password_here' WITH GRANT OPTION;

FLUSH PRIVILEGES;
EXIT;
```

We import the database of the base project

```sql
mysql -u username -p vtuser < /var/www/html/vtigercrm/schema/vtigercrm82.sql
```

## Download and install the project VTigerCRM

```bash
cd /var/www/html/
git clone https://github.com/Dibaia/VTigerCRM-members.git
```

We apply permissions necessary for the web server to be able to write to the directory

```bash
sudo chown -R www-data:www-data /var/www/html/vtigercrm/
sudo chmod -R 755 /var/www/html/vtigercrm/
```

## Web server configuration

```bash
sudo nano /etc/nginx/sites-available/vtigercrm
```

```
server {
    listen 80;
    listen [::]:80;
    root /var/www/html/vtigercrm;
    index  index.php index.html index.htm;

     client_max_body_size 100M;

    location / {
        try_files $uri $uri/ /index.php?$args;
    }

    location ~ \.php$ {
         include snippets/fastcgi-php.conf;
         fastcgi_pass unix:/var/run/php/php7.4-fpm.sock;
         fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
         include fastcgi_params;
    }
}
```

Once the changes have been applied, we activate the configuration on the nginx web server.

```bash
sudo ln -s /etc/nginx/sites-available/vtigercrm/etc/nginx/sites-enabled/
```

To finish, we restart the web server

```bash
sudo systemctl restart nginx.service
```

## Install composer

As of version v8.2, it is necessary to have composer installed to install the necessary dependencies.

Once composer is installed, we will have to access the vtiger folder and execute the following command.

```bash
composer install
```

Although this installation already has the dependencies updated, it could have some pending updates. For this reason, it is important to execute the indicated command.

## Access to the platform

With all changes completed, you should now be able to access the http:\localhost\vtigercrm service.

The user data defined in the default database are as follows:

User: Admin

Password: Admin\*1234
