# Cr4ckZ33C0d3
Reversing

## Challenge 

nc rev.tamuctf.com 8189

Difficulty: hard

[prodkey](prodkey)

## Solution

### Basic function

Hopper decompiler, we see this

	int verify_key(int arg0) {
	    var_8 = arg0;
	    if (strlen(var_8) <= 0x1c) {
	        printf("Key was too short %d.\n", strlen(var_8));
	    }
	    else {
	        if (
	        	(check_01(var_8) != 0x0) && 
	        	(check_02(var_8) != 0x0) && 
	        		<lots more here>
	        	(check_0F(var_8) != 0x0)
	        	) {
	        	return 1;
	        }
	    }
	}

Working operation:
1. we need to enter a product key of length 29 or longer
2. it does `check_01()` through `check_0F()`

---

### Reversing - Part 1

> I extracted all the checks in [checks-decompiled.c](checks-decompiled.c)

> Doing some simplifications of decompiled code, we see some patterns.

> My cleaned-up decompiled code is in [checks-simplified.c](checks-simplified.c)

Let's start with the simplest static checks first...

	int check_01(int var_8) {
	    if (    (var_8[0x5] == 0x2d) &&
	            (var_8[0xb] == 0x2d) && 
	            (var_8[0x11] == 0x2d) &&
	            (var_8[0x17] == 0x2d) ) {
	            return 1;
	    }
	    return 0;
	}

	int check_02(int arg0) {
	    var_8 = arg0;
	    if ((var_8[0x1] <= 0x39) &&
	        (var_8[0x4] <= 0x39) &&
	        (var_8[0x6] <= 0x39) &&
	        (var_8[0x9] <= 0x39) &&
	        (var_8[0xf] <= 0x39) &&

	        (var_8[0x12] <= 0x39) &&
	        (var_8[0x16] <= 0x39) &&
	        (var_8[0x1b] <= 0x39) &&
	        (var_8[0x1c] <= 0x39) ) {
	            return 1;
	    }
	    return 0;
	}

	int check_0B(int var_8) {
	    return ((var_8[0x14] == 0x42) && (var_8[0x15] == 0x42));
	}

	int check_0F(int arg0) {
	    return (arg0[0] == 0x4d); // M
	}

This provides the following insights

	check_01: dash (-) at index 0x5, 0xb, 0x11, 0x17
	check_02: number/symbol at index 0x1, 0x4, 0x6, 0x9, 0xf, 0x12, 0x16, 0x1b, 0x1c
	check_0B: (B) at index 0x14, 0x15
	check_0F: first character is (M)

Let's fill it in

	Index1: 00000000000000001111111111111
	Index0: 0123456789ABCDEF0123456789ABC  [Length = 0x1C]
	Key:    M#xx#-#xx#x-xxx#x-#xBB#-xxx##

---

### Reversing - Part 2

	int check_03(int arg0) {
	    var_8 = arg0;
	    rdx = var_8[0x4] - 0x30; // convert ascii digit to integer
	    rax = var_8[0x1];

	    if ((rdx == 0x1 + (rax - 0x30) + (rax - 0x30)) &&
	        (var_8[0x4] > 0x37) && 
	        (var_8[0x9] == (var_8[0x4] - var_8[0x1]) + 0x32)
	    ){
	        return 1;
	    }
	    return 0;
	}

We get the following equations

	// var[x] refers to ASCII char code
	// int(var[x]) refers to the integer of the ASCII digit

    ## (var[4] - 0x30) == 1 + (var[1] - 0x30) + (var[1] - 0x30)
    -> int(var[4]) == 2 * int(var[1]) + 1
    
    ## var[4] > 0x37
    -> int(var[4]) > 7

    ## var[9] == (var[4] - var[1]) + 0x32
    -> var[9] - 0x30 == (var[4] - var[1]) + 0x02)
    -> int(var[9]) == int(var[4]) - int(var[1]) + 2)

Now, putting what we have together so far

    ## From previous part, we know...
    ## var[4] <= 0x39
    -> 0x37 < var[4] <= 0x39
    -> var[4] = 0x38 or 0x39 = '8' or '9'

    ## For the following to be valid, var[4] must be odd
    ## int(var[4]) == 2 * int(var[1]) + 1

    -> var[4] = '9'
    -> var[1] = '4'

	-> int(var[9]) == 9 - 4 + 2 = 7

    var[1] = '4'
    var[4] = '9'
    var[9] = '7'


Let's fill it in

	Index1: 00000000000000001111111111111
	Index0: 0123456789ABCDEF0123456789ABC  [Length = 0x1C]
	Key:    M4xx9-#xx7x-xxx#x-#xBB#-xxx##

Now let's verify that we made progress using GDB

	(gdb) break verify_key
	Breakpoint 1 at 0x400c9d
	(gdb) run
	Starting program: /FILES/prodkey 

	Please Enter a product key to continue: 
	M4xx9-#xx7x-xxx#x-#xxx#-xxx##

	Breakpoint 1, 0x0000000000400c9d in verify_key ()
	(gdb) call (int) check_01()
	$1 = 1
	(gdb) call (int) check_02()
	$2 = 0
	(gdb) call (int) check_03()
	$3 = 1
	(gdb) call (int) check_0B()
	$4 = 1
	(gdb) call (int) check_0F()
	$5 = 1

---

### Reversing - Part 3

So now we are left with these checks, depending on the following indexes

	-- FUNCTION: CHECKED INDEX -- 
	// check_04: 0x1b, 0x1c
	// check_05: 0x1b, 0x16
	// check_06: 0x12, 0x16
	// check_07: 0x12, 0x1c, 0x16
	// check_08: 0x1, 0x4, 0x6
	// check_09: 0xf, 0x1c
	// check_0A: 0x4, 0x16
	// check_0C: 0x6, 0xf
	// check_0D: 0x4, 0xf, 0x1b
	// check_0E: 0x9, 0x1c

Notice that it corresponds to only the digits.

Hence, the other characters can be ignored. (ie. Those with `x` is not even part of the checks)

	Index1: 00000000000000001111111111111
	Index0: 0123456789ABCDEF0123456789ABC  [Length = 0x1C]
	Key:    M4xx9-#xx7x-xxx#x-#xBB#-xxx##
	Checks:  ^  ^ ^  ^     ^  ^   ^    ^^  


#### Theory on Compiled Divisions

Now I had big issues reversing the rest of the functions.

It is due to ***optimised divisions into inverse multiplication (using magic numbers)***

Here's some very good references on how compilers optimise divisions:
- https://zneak.github.io/fcd/2017/02/19/divisions.html
- http://blog.dkbza.org/2007/09/reverse-engineering-compiler-produced.html

More references:
- http://www.hexblog.com/?p=17
- http://www.nynaeve.net/?p=115

Some integer division tables
- https://github.com/halide/Halide/blob/master/src/IntegerDivisionTable.cpp
- http://eval.dan.co.jp/friends/dlang/dmd-2.073.2/src/dmd/backend/divcoeff.c

IMUL assembly instruction:
- https://stackoverflow.com/questions/3818755/imul-assembly-instruction-one-operand


#### Try on check_08

I decided to try out my learnt theory.

Choosing a function at random, I did check_08 first. 

	int check_08(int arg0) {
	    rdx = arg0[0x1];
	    rcx = arg0[0x4];
	    rcx = rdx + arg0[0x6] * rcx;
	    if (rcx - (
	        ((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f)) << 0x2) +
	        ((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f))) << 0x3) +
	        ((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f)))
	         == 0x5) {
	        return 1;
	    }
	    return 0;
	}

> Reference: http://blog.dkbza.org/2007/09/reverse-engineering-compiler-produced.html

Note that decompiling may garble up some of the logic, hence I'm simply going to focus on these as done in the reference.
1. Magic Number `0x63e7063f`
2. SAR (Shift Arithmetic Right) `0x4`
3. DWORD used `HIDWORD`

> ##### What is HIDWORD?
> 
> When multiplying using IMUL instruction, the result will be in EDX:EAX
>
> Hence, we simply assume it is divided by 2^32.
> 
> since we are discarding the LO-DWORD(EAX) and using the HI-DWORD(EDX)

Here's my workings

	Observation:
	-> Multiply by 0x63e7063f
	-> SAR 4 = divide by 2^4
	-> Using HIGH-DWORD[EDX] = divide by 2^32
	
	Calculate inverse multiplication:
	=> (0x63e7063f / 2^4 / 2^32)^-1 = 40.99
	=> division of 41

	Simplify it to:
	=> rcx - rcx/41 == 0x5

	Which is simply a modulus or remainder of
	=> rcx % 41 == 0x5

	We know from earlier on that
		key[1] = '4' = 0x34
		key[4] = '9' = 0x39

	Hence, sub it into rax
		(key[1] + key[6]*key[4]) % 41 == 5

	By trial and error,
		key[6] = 0x38 = '8'

Try out in GDB and we confirm out analysis works!

	(gdb) run
	The program being debugged has been started already.
	Start it from the beginning? (y or n) y
	Starting program: /FILES/prodkey 

	Please Enter a product key to continue: 
	M4xx9-8xx7x-xxx#x-#xBB#-xxx##

	Breakpoint 1, 0x0000000000400c9d in verify_key ()
	(gdb) call (int) check_08()
	$3 = 1

However, I will not fill in the key[6] into our progress yet in case of any cyclic dependencies.


#### Calculate Div's (Inverse Multiplication)

	Formula
	= (Magic / 2^SAR / 2^32)^-1
	[where 2^32 is due to using HIDWORD]

	check_04
	= (0x4ec4ec4f / 2^2 / 2^32)^-1
	= 13

	check_05
	= (0x2e8ba2e9 / 2^2 / 2^32)^-1
	= 22

	check_06
	= (0x2e8ba2e9 / 2^1 / 2^32)^-1
	= 11

	check_07
	= (0x4ec4ec4f / 2^3 / 2^32)^-1
	= 26

	check_08
	= (0x63e7063f / 2^4 / 2^32)^-1 
	= 41

	check_0C
	= (0x66666667 / 2^2 / 2^32)^-1
	= 10

Finally, putting it all in, we have the results

	-- FUNCTION: INDEX -- 
	// check_04: (key[0x1b] + key[0x1c]) % 13 == 8
	// check_05: (key[0x1b] + key[0x16]) % 22 == 0x12
	// check_06: (key[0x12] + key[0x16]) % 11 == 5
	// check_07: (key[0x12] + key[0x1c] + key[0x16]) % 26 == 4
	// check_08: (key[1] + key[6]*key[4]) % 41 == 5
	// check_0C: (key[0x6] + key[0x9] * key[0xf]) % 10 == 1
	
### Reversing - Part 4

Finally, we have the other checks which are not divisions. 

	// check_09: ?
	// check_0A: ?
	// check_0D: ?
	// check_0E: ?

Let's take a look at their decompiled code.

	int check_09(int arg0) {
	    rdx = arg0[0xf];
	    rax = arg0[0x1c];
	    //if (((rdx - rax - rax) + (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) & 0x3) - (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) == 0x1) {
	    if (((rdx - 2*rax) + (SAR((rdx - 2*rax), 0x1f) >> 0x1e) & 0x3) - (SAR((rdx - 2*rax), 0x1f) >> 0x1e) == 0x1) {
	        return 1;
	    }
	    return 0;
	}
	int check_0A(int arg0) {
	    rdx = arg0[0x4]
	    rax = arg0[0x16]
	    if (
	        ((SAR(sign_extend_64(rax) + rdx + sign_extend_64(rax), 0x1f) >> 0x1e) + 
	          sign_extend_64(rax) + rdx + sign_extend_64(rax) & 0x3) - 
	        (SAR(sign_extend_64(rax) + rdx + sign_extend_64(rax), 0x1f) >> 0x1e) == 0x3
	        ) {
	        return 1;
	    }
	    return 0;
	}
	int check_0D(int arg0) {
	    rdx = arg0[0x4];
	    rdx = rdx + arg0[0xf];
	    rax = arg0[0x1b];
	    if ((
	        (SAR((rax) + (rax) + rdx + 0xffffffffffffffdc, 0x1f) >> 0x1c) + 
	        (rax) + (rax) + rdx + 0xffffffffffffffdc & 0xf) - 
	        (SAR((rax) + (rax) + rdx + 0xffffffffffffffdc, 0x1f) >> 0x1c) == 0x8) {
	        return 1;
	    }
	    return 0;
	}
	int check_0E(int arg0) {
	    rdx = arg0[0x1c];
	    rax = arg0[0x9];
	    if (((rdx - rax - rax) + (SAR(rdx - rax - rax, 0x1f) >> 0x1f) & 0x1) - (SAR(rdx - rax - rax, 0x1f) >> 0x1f) == 0x1) {
	            rax = 0x1;
	    }
	    else {
	            rax = 0x0;
	    }
	    return rax;
	}

And I simplified it to this

	int check_09(int arg0) {
	    rdx = arg0[0xf];
	    rax = arg0[0x1c];
	    return (((rdx - rax - rax) & 0x3) == 0x1);
	}

	int check_0A(int arg0) {
	    rdx = arg0[0x4]
	    rax = arg0[0x16]
	    return ((rax + rdx + rax) & 0x3) == 0x3;
	}

	int check_0D(int arg0) {
	    rdx = arg0[0x4] + arg0[0xf];
	    rax = arg0[0x1b];
	    if (((rax + rax + rdx - 36) & 0xf) == 0x8) {
	        return 1;
	    }
	    return 0;
	}

	int check_0E(int arg0) {
	    rdx = arg0[0x1c];
	    rax = arg0[0x9];
	    return (((rdx - rax - rax) & 0x1) == 0x1);
	}
	
### Reversing - Part 5

Now, remember when I said I won't be using the trial-and-errored value as part of my progress?

This is because it is too tedious to try each value by hand.

I will be putting all these reversed expressions into **Microsoft Z3** which is a constraint solver. 

*I have used it in previous CTFs too. [PicoCTF 2018 keygen-me-2](https://github.com/zst123/picoctf-2018-writeups/tree/master/Solved/keygen_me_2)*

---

***There were some issues with solving. I kept getting erroneous results or 'no solutions'***

- In `check_02`, I noticed it failed when it included symbols. It only allowed digits. Hence I modified my constraint to be `0x30 < key[X] < 0x39`.

- When I added `check_0A`, `check_0D`, `check_0E`, it gave no solutions. I have a feeling I made a mistake somewhere during reversing the functions.

- Thankfully, when I omitted them, I was still able to get a working solution!


### Solved

After much hours of work, I finally solved it

	$ time python3 solve.py 
	...
	prodkey = M4xx9-8xx7x-xxx9x-6xBB2-xxx88

Test in GDB

	(gdb) run
	Please Enter a product key to continue: 
	M4xx9-8xx7x-xxx9x-6xBB2-xxx88

	Breakpoint 1, 0x0000000000400c9d in verify_key ()
	(gdb) call (int) check_01()
	$48 = 1
	(gdb) call (int) check_02()
	$49 = 1
	(gdb) call (int) check_03()
	$50 = 1
	(gdb) call (int) check_04()
	$51 = 1
	(gdb) call (int) check_05()
	$52 = 1
	(gdb) call (int) check_06()
	$53 = 1
	(gdb) call (int) check_07()
	$54 = 1
	(gdb) call (int) check_08()
	$55 = 1
	(gdb) call (int) check_09()
	$56 = 1
	(gdb) call (int) check_0A()
	$57 = 1
	(gdb) call (int) check_0B()
	$58 = 1
	(gdb) call (int) check_0C()
	$59 = 1
	(gdb) call (int) check_0D()
	$60 = 1
	(gdb) call (int) check_0E()
	$61 = 1
	(gdb) call (int) check_0F()
	$62 = 1

Flag

	$ nc rev.tamuctf.com 8189

	Please Enter a product key to continue: 
	M4xx9-8xx7x-xxx9x-6xBB2-xxx88
	gigem{z3_b3st_thr33}

## Flag

	gigem{z3_b3st_thr33}
