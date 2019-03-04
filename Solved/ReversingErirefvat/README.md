# ReversingErirefvat
Reversing

## Challenge 

    Harder..?

    #medium

[reversing4.s](reversing4.s)

## Solution

We are given source code in AT&T syntax assembly.

Since I am very weak in assembly, let's assemble it and then decompile it back into psuedo-C code.

**Edited: Apparently, it ca only be compiled on macOS, so I got lucky here**

[Assemble the ASM file using GCC](https://stackoverflow.com/a/7190391)

    $ gcc reversing4.s -o hello

Then decompile in Hopper to get some C code. 

Because decompiling is not 100% correct, we will be fixing the psuedo-C code along the way to understand the program

> [decompiled.c](decompiled.c)

### Reversing `_rb()`

Look at original ASM

    _rb:                                    ## @rb
        .cfi_startproc
    ## %bb.0:
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset %rbp, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register %rbp
        movl    $26, %eax
        movl    %edi, -4(%rbp)
        movl    %esi, -8(%rbp)
        movl    -4(%rbp), %esi
        subl    -8(%rbp), %esi
        addl    $13, %esi
        movl    %eax, -12(%rbp)         ## 4-byte Spill
        movl    %esi, %eax
        cltd
        movl    -12(%rbp), %esi         ## 4-byte Reload
        idivl   %esi
        addl    -8(%rbp), %edx
        movl    %edx, -4(%rbp)
        movl    -4(%rbp), %edx
        movl    %edx, %eax
        popq    %rbp
        retq
        .cfi_endproc

From the ASM code we know that

    The main operator is the IDIVL operator

    1. IDIVL [operand]
        - Does operation on registers: `EDX:EAX` (numerator) / `operand` (divisor)
        - Quotient saved to EAX, remainder in EDX

    2. After division, operations are done to EDX, and EAX is unused.
       (ie. the quotient is discarded)

Look at Hopper decompiled

    int _rb(int arg0, int arg1) {
        rdx = (arg0 - arg1) + 0xd & 0x80000000 ? 0xffffffff : 0x0;
        rax = ((arg0 - arg1) + 0xd) / 0x1a;
        rax = ((arg0 - arg1) + 0xd) % 0x1a + arg1;
        rsp = rsp + 0x8;
        rbp = stack[2047];
        return rax;
    }

From our understanding with the ASM code, it can be simplified...

    int _rb(int arg0, int arg1) {
        return ((arg0 - arg1) + 0xd) % 0x1a + arg1;
    }

If we recognise the code, it is [simply a **ROT13 function**](https://stackoverflow.com/questions/25214008/rot13-and-the-use-of-the-modulo)

Function:
- `arg0` = original char
- `arg1` = offset char ('A' or 'a' depends on whether `arg0` is upper/lowercase)
- returns ***ROT13 of original char***


### Reversing `_app()`

Look at Hopper decompiled

    int _app(int arg0, int arg1) {
        var_10 = strlen(arg0);
        *(int8_t *)(arg0 + sign_extend_64(var_10)) = arg1;
        rax = arg0;
        *(int8_t *)(rax + sign_extend_64(var_10 + 0x1)) = 0x0;
        rsp = rsp + 0x18;
        rbp = stack[2047];
        return rax;
    }

We do not need to refer to ASM code as it is quite apparent what it does...

Let me simplify it

    int _app(int arg0, int arg1) {
        var_10 = strlen(arg0);
        arg0[var_10] = arg1;
        arg0[var_10 + 1] = 0x0;
        return arg0;
    }

We can see that `arg_0` is a char array, where `strlen()` is being called on it. 
Note that in terms of indexing, `arg0[0]` is the 1st char and `arg0[var_10]` is the last char (null byte).

We see that `arg1` is replacing the original null byte at `arg0[var_10]` 
and a new null byte is added to `arg0[var_10+1]`.

Function:
- `arg0` is a char array
- `arg1` is one char
- ***appends one char to the char array*** and returns it

### Reversing `_ra()`

Look at Hopper decompiled

    int _ra(int arg0) {
        var_8 = arg0;
        if ((0x61 <= var_8) && (var_8 <= 0x7a)) {
            var_4 = _rb(var_8, 0x61);
        }else {
            if (0x41 <= var_8) {
                if (var_8 <= 0x5a) {
                    var_4 = _rb(var_8, 0x41);
                }else {
                    var_4 = var_8;
                }
            }else {
                var_4 = var_8;
            }
        }
        rax = var_4;
        rsp = rsp + 0x18;
        rbp = stack[2047];
        return rax;
    }

Simplify it

    int _ra(int var_8) {
        if ((0x61 <= var_8) && (var_8 <= 0x7a)) { // lowercase
            return _rb(var_8, 0x61);
        }else if ((0x41 <= var_8) && (var_8 <= 0x5a)) {
            return _rb(var_8, 0x41);
        } else {
            retur var_8;
        }
    }

Function:
- see that `_ra` is simply a ***wrapper around `_rb`***.
- if lowercase, set `_rb` offset char as 0x61 = 'a'.
- if uppercase, set `_rb` offset char as 0x41 = 'A'.
- else, just return the original char.

### Reversing `main()`

Hopper decompiled

    int _main() {
        var_8 = **___stack_chk_guard;
        var_34 = 0x0;
        var_30 = *"abcdefghijklmnopqrstuvxyz";
        var_28 = *0x100000f98;
        var_20 = *0x100000fa0;
        var_18 = *(int16_t *)0x100000fa8;
        var_35 = 0x0;
        for (var_4C = 0x0; var_4C < 0x3; var_4C = var_4C + 0x1) {
                rdx = (0x96 & 0xff) + sign_extend_64(0x19) & 0x80000000 ? 0xffffffff : 0x0;
                rdx = ((0x96 & 0xff) + sign_extend_64(0x19)) % sign_extend_64(0xd);
                xmm0 = intrinsic_cvtsi2sd(xmm0, ((0x96 & 0xff) + sign_extend_64(0x19)) / sign_extend_64(0xd) * sign_extend_64(0x2) * sign_extend_64(0x2) * sign_extend_64(0x2) + sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35) & 0xff, sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35), sign_extend_64(var_35));
                rax = round(xmm0);
                rax = intrinsic_cvttsd2si(rax, xmm0);
                var_35 = sign_extend_64(var_35) + 0x1;
                rax = _app(&var_3D, sign_extend_64(rax));
        }
        var_50 = 0x5;
        for (var_4C = 0x0; var_4C <= 0x5; var_4C = var_4C + 0x1) {
                *(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffbe) = _ra(sign_extend_64(*(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffc3)));
        }
        if (**___stack_chk_guard == var_8) {
                rax = 0x0;
                rsp = rsp + 0x68;
                rbp = stack[2047];
        }
        else {
                rax = __stack_chk_fail();
        }
        return rax;
    }

At first glance it is a very long code.

Let's remove some of those "stack check" codes. I also split up the code into 3 parts: `INIT`, `LOOP 1`, `LOOP 2`

    int _main() {
        // INIT
        var_34 = 0x0;
        var_30 = *"abcdefghijklmnopqrstuvxyz";
        var_28 = *0x100000f98;
        var_20 = *0x100000fa0;
        var_18 = *(int16_t *)0x100000fa8;
        var_35 = 0x0;

        // LOOP 1
        var_35 = 0x0;
        for (var_4C = 0x0; var_4C < 0x3; var_4C = var_4C + 0x1) {
                rdx = (0x96 & 0xff) + sign_extend_64(0x19) & 0x80000000 ? 0xffffffff : 0x0;
                rdx = ((0x96 & 0xff) + sign_extend_64(0x19)) % sign_extend_64(0xd);
                xmm0 = intrinsic_cvtsi2sd(xmm0, ((0x96 & 0xff) + sign_extend_64(0x19)) / sign_extend_64(0xd) * sign_extend_64(0x2) * sign_extend_64(0x2) * sign_extend_64(0x2) + sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35) & 0xff, sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35), sign_extend_64(var_35));
                rax = round(xmm0);
                rax = intrinsic_cvttsd2si(rax, xmm0);
                var_35 = sign_extend_64(var_35) + 0x1;
                rax = _app(&var_3D, sign_extend_64(rax));
        }

        // LOOP 2
        var_50 = 0x5;
        for (var_4C = 0x0; var_4C <= 0x5; var_4C = var_4C + 0x1) {
                *(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffbe) = _ra(sign_extend_64(*(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffc3)));
        }
        return rax;
    }

---

#### > INIT

For INIT, it corresponds to the following ASM code. Strangely there is no `w` in the alphabet set.

    movl    $0, -52(%rbp)
    movq    L_main.alpha(%rip), %rax
    movq    %rax, -48(%rbp)
    movq    L_main.alpha+8(%rip), %rax
    movq    %rax, -40(%rbp)
    movq    L_main.alpha+16(%rip), %rax
    movq    %rax, -32(%rbp)
    movw    L_main.alpha+24(%rip), %cx
    movw    %cx, -24(%rbp)
    movb    $0, -53(%rbp)
    movl    $0, -76(%rbp)

    L_main.alpha:
    .asciz  "abcdefghijklmnopqrstuvxyz"

So we can rewrite the code as

    var_34 = 0x0;
    var_30 = *"abcdefghijklmnopqrstuvxyz"; // L_main.alpha
    var_28 = *"ijklmnopqrstuvxyz";         // offset by 8
    var_20 = *"qrstuvxyz";                 // offset by 16
    var_18 = *"z";                         // offset by 25

    Addr1: 1111111122222222222222223333333333333333
    Addr0: 89ABCDEF0123456789ABCDEF0123456789ABCDEF
    Char : z.......qrstuvxyijklmnopabcd.fghijklmnopqrstuvxyz

However, I noticed later on... We can ignore this piece of code.

These are not used anywhere else in the main(). I think it is simply here to distract us.

---

#### > LOOP 2

For LOOP 2, we have this C-code

    for (var_4C = 0x0; var_4C <= 0x5; var_4C = var_4C + 0x1) {
            *(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffbe) = _ra(sign_extend_64(*(int8_t *)(rbp + sign_extend_64(var_4C) + 0xffffffffffffffc3)));
    }

Simplify it

    for (var_4C = 0x0; var_4C <= 0x5; var_4C = var_4C + 0x1) {            
        *(rbp + 0xffffffffffffffbe)[var_4C] = _ra(*(rbp + 0xffffffffffffffc3)[var_4C])
    }

Corresponds to the ASM code. I have written comments on the right.

    LBB3_3:
        movl    $5, -80(%rbp)         # -> const 5
        movl    $0, -76(%rbp)         # -> assign x = 0
    LBB3_4:
        movl    -76(%rbp), %eax
        cmpl    -80(%rbp), %eax       # -> compare x and 5
        jg  LBB3_7                    # -> jump out of loop if greater than 5
    ## %bb.5:
        movslq  -76(%rbp), %rax       # -> get x
        movsbl  -61(%rbp,%rax), %edi  # -> (rbp-61)[x] ==> param1
        callq   _ra                   # -> call _ra(param1)
        movb    %al, %cl
        movslq  -76(%rbp), %rdx
        movb    %cl, -66(%rbp,%rdx)
    ## %bb.6:                               ##   in Loop: Header=BB3_4 Depth=1
        movl    -76(%rbp), %eax
        addl    $1, %eax              # -> increment x by 1
        movl    %eax, -76(%rbp)
        jmp LBB3_4

Now let's rewrite the code based on our understanding

    // Do ROT13 on original_array and store into another_array.
    for (i = 0; i <= 5; i++) {
        another_array[i] = _ra(original_array[i]);
    }

---

#### > LOOP 1

For LOOP 1, we have this C-code

    // LOOP 1
    var_35 = 0x0;
    for (var_4C = 0x0; var_4C < 0x3; var_4C = var_4C + 0x1) {
        rdx = (0x96 & 0xff) + sign_extend_64(0x19) & 0x80000000 ? 0xffffffff : 0x0;
        rdx = ((0x96 & 0xff) + sign_extend_64(0x19)) % sign_extend_64(0xd);
        xmm0 = intrinsic_cvtsi2sd(xmm0, ((0x96 & 0xff) + sign_extend_64(0x19)) / sign_extend_64(0xd) * sign_extend_64(0x2) * sign_extend_64(0x2) * sign_extend_64(0x2) + sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35) & 0xff, sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35), sign_extend_64(var_35));
        rax = round(xmm0);
        rax = intrinsic_cvttsd2si(rax, xmm0);
        var_35 = sign_extend_64(var_35) + 0x1;
        rax = _app(&var_3D, sign_extend_64(rax));
    }

Clean up first, we will simplify later

    for (var_35 = 0; var_35 < 3; var_35++) {
        rdx = (0x96 & 0xff) + sign_extend_64(0x19) & 0x80000000 ? 0xffffffff : 0x0;
        rdx = ((0x96 & 0xff) + sign_extend_64(0x19)) % sign_extend_64(0xd);
        xmm0 = intrinsic_cvtsi2sd(xmm0, ((0x96 & 0xff) + sign_extend_64(0x19)) / sign_extend_64(0xd) * sign_extend_64(0x2) * sign_extend_64(0x2) * sign_extend_64(0x2) + sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35) & 0xff, sign_extend_64(var_35) * sign_extend_64(var_35) * sign_extend_64(var_35), sign_extend_64(var_35));
        rax = round(xmm0);
        rax = intrinsic_cvttsd2si(rax, xmm0);

        rax = _app(&var_3D, rax); // append the char
    }

ASM code, I added some comments at the side

    LBB3_1:
        cmpl    $3, -76(%rbp)
        jge LBB3_3                    # break out of loop if i >= 3
    ## %bb.2:
        leaq    -61(%rbp), %rdi
        movb    $-106, -69(%rbp)
        movb    $25, -56(%rbp)
        movb    $13, -54(%rbp)
        movb    $2, -55(%rbp)
        movzbl  -69(%rbp), %eax
        movsbl  -56(%rbp), %ecx
        addl    %ecx, %eax            # eax = byte(-106) + 25 = 0x96 + 0x19 = 0xAF
        movsbl  -54(%rbp), %ecx       # ecx = 13
        cltd
        idivl   %ecx                  # 0xAF / 13 = 13.46 = Quotient 13, Remainder 6
        movsbl  -55(%rbp), %ecx       # const 2
        movl    %ecx, %edx            # edx = 2
        imull   %edx, %edx            # edx *= 2
        imull   %ecx, %edx            # edx *= 2
        imull   %edx, %eax            # edx *= 0xAF
        movsbl  -53(%rbp), %ecx       # var_35
        movl    %ecx, %edx
        imull   %edx, %edx            # edx *= var_35
        imull   %ecx, %edx            # edx *= var_35
        addl    %edx, %eax
        movb    %al, %sil
        movb    %sil, -67(%rbp)
        movzbl  -67(%rbp), %eax
        cvtsi2sdl   %eax, %xmm0         # Convert int to double
        movq    %rdi, -88(%rbp)
        callq   _round
        cvttsd2si   %xmm0, %eax
        movb    %al, %sil
        movb    %sil, -68(%rbp)
        movsbl  -53(%rbp), %eax
        addl    $1, %eax
        movb    %al, %sil
        movb    %sil, -53(%rbp)
        movq    -88(%rbp), %rdi         ## 8-byte Reload
        movsbl  -68(%rbp), %esi
        callq   _app
        movl    -76(%rbp), %eax
        addl    $1, %eax
        movl    %eax, -76(%rbp)
        jmp LBB3_1

From the comments above, we can now understand its operation.

Rewrite the code.

    for (var_35 = 0; var_35 < 3; var_35++) {
        remaider = 0xAF % 0xD;
        quotient = 0xAF / 0xD; // = 13

        xmm0 = (double) byte(quotient * 2 * 2 * 2 + var_35 * var_35 * var_35);
        ch = (int) round(xmm0);

        rax = _app(&var_3D, ch); // append the char
    }

Realise that the loop only runs 3 times. In fact, it simply appends 3 chars as follows

    // Append chars
    104 + 0 = 104
    104 + 1 = 105
    104 + 8 = 112

Hence let's write the final effective code.

    void main() {
        _app(&var_3D, 104); // append the char
        _app(&var_3D, 105); // append the char
        _app(&var_3D, 112); // append the char

        // Do ROT13 on original_array and store into another_array.
        for (i = 0; i <= 5; i++) {
            another_array[i] = _ra(original_array[i]);
        }
    }

Now we simply need to get the payload

    >>> import codecs
    >>> x = bytes([104,105,112]).decode()
    >>> codecs.encode(x, 'rot_13')
    'uvc'

## Flag

    gigem{uvc}


### Fun fact

If we do a ROT13 of the title:

    ReversingErirefvat -> ErirefvatReversing


