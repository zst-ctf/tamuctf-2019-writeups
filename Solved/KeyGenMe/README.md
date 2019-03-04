# KeyGenMe
Reversing

## Challenge 

nc rev.tamuctf.com 7223

Difficulty: medium

[keygenme](keygenme)

## Solution

Decompile in Hopper

	// arg0 is the char array buffer

	int verify_key(int arg0) {
	    var_18 = arg0;
	    if ((strlen(var_18) > 0x9) && (strlen(var_18) <= 0x40)) {
	            rax = enc(var_18);
	            rax = strcmp("[OIonU2_<__nK<KsK", rax);
	            rax = rax == 0x0 ? 0x1 : 0x0;
	    } else {
	            rax = 0x0;
	    }
	    return rax;
	}

	int enc(int arg0) {
	    var_28 = arg0;
	    var_8 = malloc(0x40);
	    var_C = strlen(var_28);
	    var_11 = 0x48;
	    for (var_10 = 0x0; var_10 < var_C; var_10 = var_10 + 0x1) {
	            rcx = (var_11 & 0xff) * (sign_extend_64(*(int8_t *)(var_28 + sign_extend_64(var_10)) & 0xff) + 0xc) + 0x11;
	            *(int8_t *)(var_8 + sign_extend_64(var_10)) = (rcx - ((SAR(HIDWORD(rcx * 0xea0ea0eb) + rcx, 0x6)) - (SAR(rcx, 0x1f))) * 0x46) + 0x30;
	            var_11 = *(int8_t *)(var_8 + sign_extend_64(var_10)) & 0xff;
	    }
	    rax = var_8;
	    return rax;
	}

I tried to reverse enc(), but I couldn't solve the division optimisation part.

	int enc(int arg0) {
	    array = malloc(0x40);
	    var_C = strlen(arg0);
	    
	    item = 0x48; // ASCII of 'H'

	    for (i = 0; i < var_C; i++) {
	        rcx = (item & 0xff) * (arg0[i] + 0xc) + 0x11;

	        array[i] = (rcx - ((SAR(HIDWORD(rcx * 0xea0ea0eb) + rcx, 0x6)) - (SAR(rcx, 0x1f))) * 0x46) + 0x30;
	        item = array[i]
	    }
	    rax = array;
	    return rax;
	}


---

From here I got quite stuck on what I should do, so I decided to ***bruteforce it using GDB***

Using GDB, it can dynamically call functions with parameters. I used it to bruteforce each character until the input matches the encoded value

	# python gdb_solver.py 
	...
	Result: jfZxSacfaahcfccnl

With this, we can enter it into the program. But doing so yields no flag.

	$ python3 -c 'print("jpZ2SZ9fovLUX9cnz")' | nc rev.tamuctf.com 7223

	Please Enter a product key to continue: 

We must add a null byte because a newline is added into the program input too

	$ python3 -c 'print("jpZ2SZ9fovLUX9cnz\x00")' | nc rev.tamuctf.com 7223

	Please Enter a product key to continue: 
	gigem{k3y63n_m3?_k3y63n_y0u!}


## Flag

	gigem{k3y63n_m3?_k3y63n_y0u!}
