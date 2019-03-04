int check_01(int arg0) {
    var_8 = arg0;
    if ((((*(int8_t *)(var_8 + 0x5) & 0xff) == 0x2d) && ((*(int8_t *)(var_8 + 0xb) & 0xff) == 0x2d)) && ((*(int8_t *)(var_8 + 0x11) & 0xff) == 0x2d)) {
            if ((*(int8_t *)(var_8 + 0x17) & 0xff) != 0x2d) {
                    rax = 0x0;
            }
            else {
                    rax = 0x1;
            }
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_02(int arg0) {
    var_8 = arg0;
    if (((((sign_extend_64(*(int8_t *)(var_8 + 0x1) & 0xff) <= 0x39) && (sign_extend_64(*(int8_t *)(var_8 + 0x4) & 0xff) <= 0x39)) && (sign_extend_64(*(int8_t *)(var_8 + 0x6) & 0xff) <= 0x39)) && (sign_extend_64(*(int8_t *)(var_8 + 0x9) & 0xff) <= 0x39)) && (sign_extend_64(*(int8_t *)(var_8 + 0xf) & 0xff) <= 0x39)) {
            if (sign_extend_64(*(int8_t *)(var_8 + 0x12) & 0xff) <= 0x39) {
                    if (sign_extend_64(*(int8_t *)(var_8 + 0x16) & 0xff) <= 0x39) {
                            if (sign_extend_64(*(int8_t *)(var_8 + 0x1b) & 0xff) <= 0x39) {
                                    if (sign_extend_64(*(int8_t *)(var_8 + 0x1c) & 0xff) <= 0x39) {
                                            rax = 0x1;
                                    }
                                    else {
                                            rax = 0x0;
                                    }
                            }
                            else {
                                    rax = 0x0;
                            }
                    }
                    else {
                            rax = 0x0;
                    }
            }
            else {
                    rax = 0x0;
            }
    }
    else {
            rax = 0x0;
    }
    return rax;
}
int check_03(int arg0) {
    var_8 = arg0;
    rdx = sign_extend_64(*(int8_t *)(var_8 + 0x4) & 0xff) + 0xffffffffffffffd0;
    rax = *(int8_t *)(var_8 + 0x1) & 0xff;
    if ((rdx == 0x1 + (sign_extend_64(rax) - 0x30) + (sign_extend_64(rax) - 0x30)) && (sign_extend_64(*(int8_t *)(var_8 + 0x4) & 0xff) > 0x37)) {
            if (sign_extend_64(*(int8_t *)(var_8 + 0x9) & 0xff) == (sign_extend_64(*(int8_t *)(var_8 + 0x4) & 0xff) - sign_extend_64(*(int8_t *)(var_8 + 0x1) & 0xff)) + 0x32) {
                    rax = 0x1;
            }
            else {
                    rax = 0x0;
            }
    }
    else {
            rax = 0x0;
    }
    return rax;
}
int check_04(int arg0) {
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0x1b) & 0xff) + sign_extend_64(*(int8_t *)(arg0 + 0x1c) & 0xff);
    if (rcx - (((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) << 0x2) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) == 0x8) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}
int check_05(int arg0) {
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0x1b) & 0xff) + sign_extend_64(*(int8_t *)(arg0 + 0x16) & 0xff);
    if (rcx - ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x2)) - (SAR(rcx, 0x1f))) * 0x16 == 0x12) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_06(int arg0) {
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0x12) & 0xff) + sign_extend_64(*(int8_t *)(arg0 + 0x16) & 0xff);
    if (rcx - ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) == 0x5) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}
int check_07(int arg0) {
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0x12) & 0xff) + sign_extend_64(*(int8_t *)(arg0 + 0x1c) & 0xff) + sign_extend_64(*(int8_t *)(arg0 + 0x16) & 0xff);
    if (rcx - ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x3)) - (SAR(rcx, 0x1f))) * 0x1a == 0x4) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}
int check_08(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0x1) & 0xff);
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0x4) & 0xff);
    rcx = rdx + sign_extend_64(*(int8_t *)(arg0 + 0x6) & 0xff) * rcx;
    if (rcx - (((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f))) << 0x3) + ((SAR(HIDWORD(rcx * 0x63e7063f), 0x4)) - (SAR(rcx, 0x1f))) == 0x5) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_09(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0xf) & 0xff);
    rax = *(int8_t *)(arg0 + 0x1c) & 0xff;
    if (((rdx - sign_extend_64(rax) - sign_extend_64(rax)) + (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) & 0x3) - (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) == 0x1) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_0A(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0x4) & 0xff);
    rax = *(int8_t *)(arg0 + 0x16) & 0xff;
    if (((SAR(sign_extend_64(rax) + rdx + sign_extend_64(rax), 0x1f) >> 0x1e) + sign_extend_64(rax) + rdx + sign_extend_64(rax) & 0x3) - (SAR(sign_extend_64(rax) + rdx + sign_extend_64(rax), 0x1f) >> 0x1e) == 0x3) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}



int check_0B(int arg0) {
    var_8 = arg0;
    if (((*(int8_t *)(var_8 + 0x14) & 0xff) == 0x42) && ((*(int8_t *)(var_8 + 0x15) & 0xff) == 0x42)) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_0C(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0x6) & 0xff);
    rcx = sign_extend_64(*(int8_t *)(arg0 + 0xf) & 0xff);
    rcx = rdx + sign_extend_64(*(int8_t *)(arg0 + 0x9) & 0xff) * rcx;
    if (rcx - ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f))) == 0x1) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_0D(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0x4) & 0xff);
    rdx = rdx + sign_extend_64(*(int8_t *)(arg0 + 0xf) & 0xff);
    rax = *(int8_t *)(arg0 + 0x1b) & 0xff;
    if (((SAR(sign_extend_64(rax) + sign_extend_64(rax) + rdx + 0xffffffffffffffdc, 0x1f) >> 0x1c) + sign_extend_64(rax) + sign_extend_64(rax) + rdx + 0xffffffffffffffdc & 0xf) - (SAR(sign_extend_64(rax) + sign_extend_64(rax) + rdx + 0xffffffffffffffdc, 0x1f) >> 0x1c) == 0x8) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    rsp = rsp + 0x8;
    rbp = stack[2047];
    return rax;
}

int check_0E(int arg0) {
    rdx = sign_extend_64(*(int8_t *)(arg0 + 0x1c) & 0xff);
    rax = *(int8_t *)(arg0 + 0x9) & 0xff;
    if (((rdx - sign_extend_64(rax) - sign_extend_64(rax)) + (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1f) & 0x1) - (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1f) == 0x1) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

int check_0F(int arg0) {
    if ((*(int8_t *)arg0 & 0xff) == 0x4d) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
}