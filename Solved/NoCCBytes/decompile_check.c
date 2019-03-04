
// (check(passCheck(char*)
int _Z5checkPh(int * arg0) {
    arg0 = arg0;
    if ((arg0 == check(unsigned char*)) ||
        (check(check(unsigned char*)) == check(unsigned char*))) goto loc_a6d;

loc_a63:
    rax = 0x0;
    return rax;

loc_a6d: // initialise
    var_15 = 0x99;
    var_16 = 0x11;
    var_8 = arg0;
    var_10 = 0x0;
    goto loc_a84;

loc_a84: // check var_10
    if (var_10 > 0x3) {
        goto loc_ae5;
    } else {
        loc_a8a:
        var_14 = 0x0;
        goto loc_a91;
    }

loc_a91:
    if (var_14 > 0xf) goto loc_adf;

loc_a97:
    var_16 = var_16 + var_14 * var_10;
    var_8 += 1;
    if (0x99 != (*(int8_t *)var_8 & 0xff ^ 0x55)) goto loc_ac7;

loc_abd:
    rax = 0x0;
    return rax;

loc_ac7:
    var_16 = var_16 - var_14 * var_10;
    var_14 = var_14 + 0x1;
    goto loc_a91;

loc_adf:
    var_10 += 1;
    goto loc_a84;

loc_ae5: // xor_globPass
    var_C = 0x0;
    while (var_C <= 0x18) {
        if (arg0 == passCheck(char*)) {
            if (globPass[var_C] != 0x0) {
                globPass[var_C] ^= var_16;
            }
        }
        var_C++;
    }
    *(int8_t *)checkFlag = 0x1;
    rax = arg0;
    return rax;
}