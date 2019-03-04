// check_01 done, x
int check_01(int var_8) {
    if (    (var_8[0x5] == 0x2d) &&
            (var_8[0xb] == 0x2d) && 
            (var_8[0x11] == 0x2d) &&
            (var_8[0x17] == 0x2d)
        ) {
            return 1;
    }
    return 0;
}

// check_02 done
int check_02(int arg0) {
    var_8 = arg0;
    if (
        (var_8[0x1] <= 0x39) &&
        (var_8[0x4] <= 0x39) &&
        (var_8[0x6] <= 0x39) &&
        (var_8[0x9] <= 0x39) &&
        (var_8[0xf] <= 0x39) &&

        (var_8[0x12] <= 0x39) &&
        (var_8[0x16] <= 0x39) &&
        (var_8[0x1b] <= 0x39) &&
        (var_8[0x1c] <= 0x39) &&

        ) {
            return 1;
    }
    return 0;
}


// check_03 done, x
int check_03(int arg0) {
    var_8 = arg0;
    //rdx = sign_extend_64(*(int8_t *)(var_8 + 0x4) & 0xff) + 0xffffffffffffffd0;
    rdx = var_8[0x4] - 0x30;
    rax = var_8[0x1];

    if (
        (rdx == 0x1 + (rax - 0x30) + (rax - 0x30)) &&
        (var_8[0x4] > 0x37) && 
        (var_8[0x9] == (var_8[0x4] - var_8[0x1]) + 0x32)
    ){
        return 1;
    }

    return 0;
}

// check_04 probably: 0x1b, 0x1c
int check_04(int arg0) {
    rcx = arg0[0x1b] + arg0[0x1c];
    //if (rcx - (((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) << 0x2) + ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) == 0x8) {
    if (
          rcx - 
          (   (SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) -
              (SAR(rcx, 0x1f)) + 
              (SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f)) +
              ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) << 0x2) +
              ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x2)) - (SAR(rcx, 0x1f))) == 0x8
        ) {
            return 1;
    }
    return 0;
}

// check_05 probably: 0x1b, 0x16
int check_05(int arg0) {
    rcx = arg0[0x1b] + arg0[0x16];

    if (rcx - ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x2)) - (SAR(rcx, 0x1f))) * 0x16 == 0x12) {
        return 1;
    }
    return 0;
}

// check_06 probably: 0x12, 0x16
int check_06(int arg0) {
    rcx = arg0[0x12] + arg0[0x16];

    if (rcx - ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x2e8ba2e9), 0x1)) - (SAR(rcx, 0x1f))) == 0x5) {
        return 1;
    }
    return 0;
}


// check_07 probably: 0x12, 0x1c, 0x16
int check_07(int arg0) {
    rcx = arg0[0x12] + arg0[0x1c] + arg0[0x16];
    if (rcx - ((SAR(HIDWORD(rcx * 0x4ec4ec4f), 0x3)) - (SAR(rcx, 0x1f))) * 0x1a == 0x4) {
        return 1;
    }
    return 0;
}

// check_08 probably: 0x1, 0x4, 0x6
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

// check_09 probably: 0xf, 0x1c
int check_09(int arg0) {
    rdx = arg0[0xf];
    rax = arg0[0x1c];
    if (((rdx - rax - rax) + (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) & 0x3) - (SAR(rdx - sign_extend_64(rax) - sign_extend_64(rax), 0x1f) >> 0x1e) == 0x1) {
        return 1;
    }
    return 0;
}

// check_0A 0x4, 0x16
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


// check_0B done, x
int check_0B(int var_8) {
    return ((var_8[0x14] == 0x42) && (var_8[0x15] == 0x42));
}

// check_0C 0x6, 0xf
int check_0C(int arg0) {
    rdx = arg0[0x6];
    rcx = arg0[0xf];
    rcx = rdx + arg0[0x9] * rcx;
    if (rcx - ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f))) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f)) << 0x2) + ((SAR(HIDWORD(rcx * 0x66666667), 0x2)) - (SAR(rcx, 0x1f))) == 0x1) {
            rax = 0x1;
    }
    else {
            rax = 0x0;
    }
    return rax;
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


// check_0E 0x9, 0x1c
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

// check_0F done, x
int check_0F(int arg0) {
    return (arg0[0] == 0x4d); // M
}