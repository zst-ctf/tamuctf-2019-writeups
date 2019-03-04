# Cheesy
Reversing

## Challenge 

Where will you find the flag?

[reversing1](reversing1)

## Solution

Do a strings

	QUFBQUFBQUFBQUFBQUFBQQ==
	Hello! I bet you are looking for the flag..
	I really like basic encoding.. can you tell what kind I used??
	RkxBR2ZsYWdGTEFHZmxhZ0ZMQUdmbGFn
	Q2FuIHlvdSByZWNvZ25pemUgYmFzZTY0Pz8=
	Z2lnZW17M2E1eV9SM3YzcjUxTjYhfQ==
	WW91IGp1c3QgbWlzc2VkIHRoZSBmbGFn

We get these strings respectively

	AAAAAAAAAAAAAAAA
	FLAGflagFLAGflagFLAGflag
	Can you recognize base64??
	gigem{3a5y_R3v3r51N6!}
	You just missed the flag

## Flag

	gigem{3a5y_R3v3r51N6!}
