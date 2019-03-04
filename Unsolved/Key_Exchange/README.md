# Key Exchange
Network/Pentest

## Challenge 

Get your keys here!

2/23 7:38 pm CST: Alice and Bob are much more willing to talk to each other but do so less often.
2/24 8:20 am CST: Alice and Bob join the open source community.
2/24 9:01 pm CST: Alice and Bob use Python3 and you should to.

Difficulty: medium

[AESCipher.py](AESCipher.py)
[DiffieHellman.py](DiffieHellman.py)
[key_xchange.ovpn](key_xchange.ovpn)

## Solution

### Setup

Install OpenVPN

	$ sudo apt-get install -y openvpn

Start OpenVPN with the given configuration

	$ sudo openvpn key_xchange.ovpn

### Scan Hosts

Scan subnet and we find 2 hosts: `172.30.0.2` and `172.30.0.3`

	$ nmap -sP 172.30.0.0/28

Scan for ports

	$ nmap -sV 172.30.0.2
	All 1000 scanned ports on 172.30.0.2 are closed

	$ nmap -sV 172.30.0.3
	All 1000 scanned ports on 172.30.0.3 are closed


### Man in the middle (MITM) attack

Similar to the earlier [Calculator](../Solved/Calculator) and [Clock](../Solved/Calculator) challenge. Follow the same instructions in previous challenges to launch MITM attack.

We need to sniff & alter the telnet traffic using Wireshark and Ettercap




## Flag

	??