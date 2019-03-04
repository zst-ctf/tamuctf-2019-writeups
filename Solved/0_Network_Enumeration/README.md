# 0_Network_Enumeration
ReadingRainbow

## Challenge 

Recently, the office put up a private webserver to store important information about the newest research project for the company. This information was to be kept confidential, as it's release could mean a large loss for everyone in the office.

Just as the research was about to be published, a competing firm published information eerily similar. Too similar...

Time to take a look through the office network logs to figure out what happened.

1. What is the IP address of the private webserver?
2. How many hosts made contact with the private webserver that day?

Difficulty: easy

[capture.pcap](capture.pcap)

## Solution

### Question 1

	tcp.port == 80

Search for any HTTP get request which is the server

### Question 2

Find all packets that connect to destination 192.168.11.4

	$ tshark -r capture.pcap -Y 'ip.dst == 192.168.11.4'
		-T fields -e ip.src | sort | uniq
	128.194.165.200
	172.217.6.138
	172.226.209.130
	192.168.1.1
	192.168.11.5
	192.168.11.7
	192.168.11.8
	192.168.11.9
	35.222.85.5
	35.224.99.156
	52.43.40.243
	54.213.168.194
	91.189.92.38

	$ !! | wc -l
      13

## Flag

	1. 192.168.11.4
	2. 13
