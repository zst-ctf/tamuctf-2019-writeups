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

/**************************************************************************/
int _app(int arg0, int arg1) {
    var_10 = strlen(arg0);
    *(int8_t *)(arg0 + sign_extend_64(var_10)) = arg1;
    rax = arg0;
    *(int8_t *)(rax + sign_extend_64(var_10 + 0x1)) = 0x0;
    rsp = rsp + 0x18;
    rbp = stack[2047];
    return rax;
}

/**************************************************************************/
int _rb(int arg0, int arg1) {
    rdx = (arg0 - arg1) + 0xd & 0x80000000 ? 0xffffffff : 0x0;
    rax = ((arg0 - arg1) + 0xd) / 0x1a;
    rax = ((arg0 - arg1) + 0xd) % 0x1a + arg1;
    rsp = rsp + 0x8;
    rbp = stack[2047];
    return rax;
}

/**************************************************************************/
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


/**************************************************************************/
// ASM = LBB3_9:
function sub_100000f45 {
    asm { ud2 };
    rax = loc_100000f47();
    return rax;
}
