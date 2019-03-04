# NoCCBytes
Reversing

## Challenge 

nc rev.tamuctf.com 8188

Difficulty: medium

[noccbytes](noccbytes)

## Solution

### Main code operation

	if ((check(passCheck(char*)) == passCheck(char*) ? 0x1 : 0x0) != 0x0) {
	    var_30 = 0x0;
	    var_28 = 0x0;
	    var_20 = 0x0;
	    var_18 = 0x0;
	    rax = strcpy(&var_30, globPass);
	    if (strcmp(var_38, &var_30) == 0x0) {
	            rax = 0x1;
	    }
	    else {
	            rax = puts("\nWrong Password");
	            rax = 0x0;
	    }
	}


input_text must be such that:

1. check(passCheck(input_text)) == passCheck(input_text)
2. input_text.startswith(globPass)
3. globPass = bytes.fromhex('467065657e427068621b')

### Reversing the code

Decompiled in Hopper. Then I slowly reversed/refactored it to its logic.

> [decompile_check.c](decompile_check.c)

Then

> [decompile_check2.c](decompile_check2.c)

Finally

> [decompile_check3.c](decompile_check3.c)


### Understanding the calculations

Code

	// initialise
	int var_16 = 17 // 0x11;
	var_8 = arg0;

	// some calculations
	for (int var_10 = 0; var_10 < 3; var_10++) {
	    for (int var_14 = 0; var_14 <= 0xf; ) {
	        // loc_a97:
	        var_16 = var_16 + var_14 * var_10;
	        var_8 += 1;
	        if (0x99 != (var_8 & 0xff ^ 0x55)) {
	            // at loc_ac7;
	            var_16 = var_16 - var_14 * var_10;
	            var_14++;
	            
	        }
	    }
	}

Our goal is to make `var_16 == 0` in order to keep `globPass` unchanged. This is because later on, `var_16` is used as an XOR cipher key as in this code below.

	// The do XOR cipher with var_16
	var_C = 0x0;
	while (var_C <= 0x18) {
	    if (arg0 == passCheck(char*)) {
	        if (globPass[var_C] != 0x0) {
	            globPass[var_C] ^= var_16;
	        }
	    }
	    var_C++;
	}

---

Without special input, `var_16` is incremented then decremented to the same value. As seen in the following code.

    var_16 = var_16 + var_14 * var_10;
    var_8 += 1;
    if (0x99 != (var_8 & 0xff ^ 0x55)) {
        // at loc_ac7;
        var_16 = var_16 - var_14 * var_10;
        var_14++;
        
    }

If we make the `if (0x99 != (var_8 & 0xff ^ 0x55))` condition true, then `var_16` will increase by `var_14 * var_10`.

For the condition to be true, `var_8` (the input char in a certain index) must be equal to `0x99 ^ 0x55 == 0xCC`.

***This seems to make sense as the title is hinting 0xCC byte***


### Simpler than I thought

At the start `var_16 = 0x11` is initialised. Hence we need to increment it a total of `0xEF = 239` times in order to have it wrap arounnd back to `0x00`. This is not feasible for the buffer size given.

If we think back again at the XOR cipher. It is a simpler solution than I thought

	// The do XOR cipher with var_16
	var_C = 0x0;
	while (var_C <= 0x18) {
	    if (arg0 == passCheck(char*)) {
	        if (globPass[var_C] != 0x0) {
	            globPass[var_C] ^= var_16;
	        }
	    }
	    var_C++;
	}

We notice that the global variable itself is being modified.

Hence we can simply XOR 0x11 with the original globPass.

	>>> def xor_zip_bytes(bytearray1, bytearray2):
	...     final = b''
	...     for a, b in zip(bytearray1, bytearray2):
	...         final += bytes([a ^ b])
	...     return final

	>>> from itertools import cycle
	>>> xor_zip_bytes(bytes.fromhex('467065657e427068621b'), cycle(bytes([17])) )
	b'WattoSays\n'

Solved

	# nc rev.tamuctf.com 8188

	Welcome. Please Enter a password to continue: 
	WattoSays
	gigem{Y0urBreakpo1nt5Won7Work0nMeOnlyMon3y}

## Flag

	gigem{Y0urBreakpo1nt5Won7Work0nMeOnlyMon3y}
