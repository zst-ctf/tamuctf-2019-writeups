# PWN
Secure Coding

## Challenge 

https://gitlab.tamuctf.com/root/pwn

Difficulty: easy

## Solution

From the Git Repo,

	Now that you have broken a PWN challenge it's your turn to fix it!  
	  
	To solve this challenge you must first fork the challenge and then modify the files in this repository and attempt to fix the vulnerability that you found.  
	Everytime you make a commit your files are tested on the backend system. The results can be found under CI/CD->Jobs and then the last test ran.  
	If you pass all of the tests the flag will be printed at the bottom of the CI/CD display. Otherwise you will either get an error or statement saying what happened.

So we need to fix the vulnerability of buffer overflow

Simply replace gets() with fgets();

	gets(buf);

	fgets(buf, 128, stdin);

And we pass the test

	Running with gitlab-runner 11.7.0 (8bb608ff)
	  on runner4 xp5zxg1s
	Using Docker executor with image tamuctf/buffer_overflow:latest ...
	Using locally found image version due to if-not-present pull policy
	Using docker image sha256:3e4133f031992dc281f0d814d945024900c649ea646d36fcb80ef591d83b82b6 for tamuctf/buffer_overflow:latest ...
	Running on runner-xp5zxg1s-project-123-concurrent-0 via ip-172-31-19-180...
	Cloning repository...
	Cloning into '/builds/zst123/pwn'...
	Checking out a79b5c21 as master...
	Skipping Git submodules setup
	$ ./tests/entry.sh
	2019/02/23 08:32:18 socat[22] E write(5, 0x5578ec32a050, 7233): Broken pipe
	172.17.0.3
	Pushing: {'serviceHost': '172.17.0.3', 'userInfo': u'5d3bf17b6b5f539156fe42626fc14435f3d0827e8b4262a2a434da2d3aa31edc', 'chal': 'echo_overflow'}
	{"msg": "Service Check Succeeded After Attack\nflag: gigem{check_that_buffer_size_baby}"}
	Job succeeded


## Flag

	gigem{check_that_buffer_size_baby}
