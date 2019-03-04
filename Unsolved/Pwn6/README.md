# Pwn6
Pwn

## Challenge 

Setup the VPN and use the client to connect to the server.

The servers ip address on the vpn is 172.30.0.2

Difficulty: hard

2/23 10:06 am: Added server ip

## Solution

Tutorial: Setup OpenVPN 
- https://nordvpn.com/tutorials/linux/openvpn/


Install OpenVPN and copy the file in

	sudo apt-get install -y openvpn
	cp pwn6.ovpn /etc/openvpn/

Start OpenVPN with a chosen configuration by entering:

	sudo openvpn pwn6.ovpn

Now I should be able to ping the server

	$ ping 172.30.0.2

	# ./client 172.30.0.2
		 0. View Recent Login's With client
		 1. Login
	Enter command to send to server...
	0 
	Most recent login's from this client
	1. 1337
	2. 23646
	...
	\





## Flag

	??