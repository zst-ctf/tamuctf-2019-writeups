int main(int arg0, int arg1) {
    setvbuf(*__TMC_END__, 0x0, 0x2, 0x0);
    if ((check(main) == main ? 0x1 : 0x0) == 0x0) goto loc_d0b;

loc_c71:
    puts("\nWelcome. Please Enter a password to continue: ");
    fgets(&var_90, 0x19, *stdin@@GLIBC_2.2.5);
    if (passCheck(&var_90) == 0x0) goto loc_d0b;

loc_cab:
    var_98 = fopen("flag.txt", 0xe60);
    if (var_98 != 0x0) goto loc_ce2;

loc_ccf:
    puts("Too bad the flag is only on the remote server!");
    rax = 0x0;
    goto loc_d10;

loc_d10:
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    return rax;

loc_ce2:
    fgets(&var_70, 0x64, var_98);
    printf(&var_70);
    goto loc_d0b;

loc_d0b:
    rax = 0x0;
    goto loc_d10;
}



// if (passCheck(&var_90) == 0x0) goto loc_d0b;
int _Z9passCheckPc(int * arg0) {
    var_38 = arg0;
    if ((check(passCheck(char*)) == passCheck(char*) ? 0x1 : 0x0) != 0x0) {
            var_30 = 0x0;
            strcpy(&var_30, globPass);
            if (strcmp(var_38, &var_30) == 0x0) {
                    rax = 0x1;
            }
            else {
                    puts("\nWrong Password");
                    rax = 0x0;
            }
    }
    else {
            rax = 0x0;
    }
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    return rax;
}

// globPass = 11 bytes
     globPass:
0000000000202010         db  0x46 ; 'F'             ; DATA XREF=_Z5checkPh+224, _Z5checkPh+245, _Z5checkPh+267, _Z9passCheckPc+91
0000000000202011         db  0x70 ; 'p'
0000000000202012         db  0x65 ; 'e'
0000000000202013         db  0x65 ; 'e'
0000000000202014         db  0x7e ; '~'
0000000000202015         db  0x42 ; 'B'
0000000000202016         db  0x70 ; 'p'
0000000000202017         db  0x68 ; 'h'
0000000000202018         db  0x62 ; 'b'
0000000000202019         db  0x1b ; '.'
000000000020201a         db  0x00 ; '.'

// (check(passCheck(char*)
int _Z5checkPh(int * arg0) {
    var_28 = arg0;
    if ((var_28 == check(unsigned char*)) || ((check(check(unsigned char*)) != check(unsigned char*) ? 0x1 : 0x0) == 0x0)) goto loc_a6d;

loc_a63:
    rax = 0x0;
    return rax;

loc_a6d:
    var_15 = 0x99;
    var_16 = 0x11;
    var_8 = var_28;
    var_10 = 0x0;
    goto loc_a84;

loc_a84:
    if (var_10 > 0x3) goto loc_ae5;

loc_a8a:
    var_14 = 0x0;
    goto loc_a91;

loc_a91:
    if (var_14 > 0xf) goto loc_adf;

loc_a97:
    var_16 = var_16 + var_14 * var_10;
    var_8 = var_8 + 0x1;
    if (0x99 != (*(int8_t *)var_8 & 0xff ^ 0x55)) goto loc_ac7;

loc_abd:
    rax = 0x0;
    return rax;

loc_ac7:
    var_16 = var_16 - var_14 * var_10;
    var_14 = var_14 + 0x1;
    goto loc_a91;

loc_adf:
    var_10 = var_10 + 0x1;
    goto loc_a84;

loc_ae5:
    var_C = 0x0;
    while (sign_extend_32(var_C) <= 0x18) {
            if (var_28 == passCheck(char*)) {
                    if ((*(int8_t *)(sign_extend_64(var_C) + globPass) & 0xff) != 0x0) {
                            *(int8_t *)(sign_extend_64(var_C) + globPass) = *(int8_t *)(sign_extend_64(var_C) + globPass) & 0xff ^ var_16;
                    }
            }
            var_C = var_C + 0x1;
    }
    *(int8_t *)checkFlag = 0x1;
    rax = var_28;
    return rax;
}