# Copper
Network/Pentest

## Challenge 

Bob learned that telnet was actually not secure. Because Bob is a good administrator he wanted to make his own, more secure, version of telnet. He heard AES was secure so he decided to use that.

Here is the script he runs every day over telnet:

	ls -la
	date > monitor.txt
	echo "=========================================" >> monitor.txt
	echo "ps -aux" >> monitor.txt
	ps -aux >> monitor.txt
	echo "=========================================" >> monitor.txt
	echo "df -h" >> monitor.txt
	df -h >> monitor.txt
	cp ./monitor.txt /logs
	exit

Difficulty: medium

[copper.ovpn](zst123.copper.ovpn)

## Solution

### Setup

Install OpenVPN

	$ sudo apt-get install -y openvpn

Start OpenVPN with the given configuration

	$ sudo openvpn copper.ovpn

### Scan Hosts

Scan subnet and we find 2 hosts: `172.30.0.2` and `172.30.0.3`

	$ nmap -sP 172.30.0.0/28

Scan for ports

	$ nmap -sV 172.30.0.2
	PORT     STATE    SERVICE       VERSION
	1046/tcp filtered wfremotertm
	4446/tcp filtered n1-fwp
	4550/tcp filtered gds-adppiw-db
	8080/tcp open     http          SimpleHTTPServer 0.6 (Python 3.6.7)

	$ nmap -sV 172.30.0.3
	Not shown: 999 closed ports
	PORT      STATE    SERVICE VERSION
	56738/tcp filtered unknown

### Website

When visiting the server, see merely see a file called monitor.txt (http://172.30.0.2:8080/monitor.txt)

	Sun Mar  3 15:39:13 UTC 2019
	=========================================
	ps -aux
	USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
	root         1  0.0  0.0  18376  3012 ?        Ss   15:21   0:00 /bin/bash ./entry.sh
	root         6  0.0  0.1  53244 16420 ?        S    15:22   0:00 python3 -m http.server 8080
	root         7  0.0  0.1 141624 22884 ?        Sl   15:22   0:00 python3 ./server.py
	root       114  0.0  0.0   4628   780 ?        S    15:39   0:00 /bin/sh -c ps -aux >> monitor.txt
	root       115  0.0  0.0  34400  2804 ?        R    15:39   0:00 ps -aux
	=========================================
	df -h
	Filesystem      Size  Used Avail Use% Mounted on
	overlay         250G  8.9G  242G   4% /
	tmpfs            64M     0   64M   0% /dev
	tmpfs           7.6G     0  7.6G   0% /sys/fs/cgroup
	/dev/nvme0n1    250G  8.9G  242G   4% /etc/hosts
	shm              64M     0   64M   0% /dev/shm
	tmpfs           7.6G     0  7.6G   0% /proc/acpi
	tmpfs           7.6G     0  7.6G   0% /proc/scsi
	tmpfs           7.6G     0  7.6G   0% /sys/firmware


---



	Sun Mar  3 15:27:16 UTC 2019
	sssssssssssssssssssssssssssssssssssssssss
	ps -aux
	USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
	root         1  0.0  0.0  18376  3012 ?        Ss   15:21   0:00 /bin/bash ./entry.sh
	root         6  0.0  0.1  53244 16420 ?        S    15:22   0:00 python3 -m http.server 8080
	root         7  0.1  0.1 141368 22724 ?        Sl   15:22   0:00 python3 ./server.py
	root        71  0.0  0.0   4628   780 ?        S    15:28   0:00 /bin/sh -c ps -aux >> monitor.txt
	root        72  0.0  0.0  34400  2808 ?        R    15:28   0:00 ps -aux
	sssssssssssssssssssssssssssssssssssssssss
	df -h
	Filesystem      Size  Used Avail Use% Mounted on
	overlay         250G  8.9G  242G   4% /
	tmpfs            64M     0   64M   0% /dev
	tmpfs           7.6G     0  7.6G   0% /sys/fs/cgroup
	/dev/nvme0n1    250G  8.9G  242G   4% /etc/hosts
	shm              64M     0   64M   0% /dev/shm
	tmpfs           7.6G     0  7.6G   0% /proc/acpi
	tmpfs           7.6G     0  7.6G   0% /proc/scsi
	tmpfs           7.6G     0  7.6G   0% /sys/firmware




### Man in the middle (MITM) attack

Similar to the earlier [Calculator](../Solved/Calculator) and [Clock](../Solved/Calculator) challenge. Follow the same instructions in previous challenges to launch MITM attack.

We need to sniff & alter the telnet traffic using Wireshark and Ettercap


## Flag

	??