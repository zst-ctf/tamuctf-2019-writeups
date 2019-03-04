void login(void * ut) {
    var_68 = ut;
    var_70 = rsi;
    var_10 = *(var_70 + 0x8);
    var_54 = 0xffffffff;
    var_50 = LOWORD(*(int16_t *)(*(var_70 + 0x8) + 0x8) & 0xffff);
    var_48 = *(var_70 + 0x8) + 0xa;
    var_40 = *(var_70 + 0x8) + (LOBYTE(var_50 & 0xff) & 0xff) + 0xa;
    for (var_4 = 0x0; LODWORD(LOBYTE(var_4F & 0xff) & 0xff) > var_4; var_4 = var_4 + 0x1) {
            if (LOBYTE(*(int8_t *)(sign_extend_32(LODWORD(var_4)) + var_40) & 0xff) > 0x40) {
                    *(int8_t *)(sign_extend_32(LODWORD(var_4)) + var_40) = LOBYTE(LODWORD(*(int8_t *)(sign_extend_64(LODWORD(var_4)) + var_40) & 0xff) | 0x20);
            }
    }
    LODWORD(rax) = 0x0;
    rax = printf("Looking up User");
    rax = *__TMC_END__;
    rax = fflush(rax);
    for (var_8 = 0x0; var_8 <= 0x2; var_8 = var_8 + 0x1) {
            rax = putchar(0x2e);
            rax = *__TMC_END__;
            rax = fflush(rax);
    }
    rax = putchar(0xa);
    var_14 = LODWORD(sqlite3_prepare_v2(*(var_68 + 0x10), "SELECT * from user where userID == (?1)", 0xffffffff, &var_38, 0x0));
    rax = sqlite3_bind_text(var_38, 0x1, var_48, LOBYTE(var_50 & 0xff) & 0xff, 0x0);
    if (var_14 == 0x0) goto loc_4055cc;

loc_40559b:
    rdx = sqlite3_errmsg(*(var_68 + 0x10));
    LODWORD(rax) = 0x0;
    rax = fprintf(*stderr@@GLIBC_2.2.5, "Failed to fetch data: %s\n", rdx);
    goto loc_405739;

loc_405739:
    var_54 = 0xffffffff;
    rax = send(LODWORD(*(int32_t *)var_70), &var_54, 0x4, 0x0);
    LODWORD(rax) = 0xffffffff;
    return;

loc_4055cc:
    if (LODWORD(sqlite3_step(var_38)) == 0x64) goto loc_405608;

loc_4055e1:
    rsi = sqlite3_errmsg(*(var_68 + 0x10));
    LODWORD(rax) = 0x0;
    rax = printf("ERROR Selecting: %s\n", rsi);
    goto loc_405739;

loc_405608:
    var_20 = malloc(sign_extend_32(LODWORD(LODWORD(LOBYTE(var_4F & 0xff) & 0xff) + 0x1)));
    rax = memcpy(var_20, var_40, LOBYTE(var_4F & 0xff) & 0xff);
    *(int8_t *)(var_20 + (LOBYTE(var_4F & 0xff) & 0xff)) = 0x0;
    var_28 = crypt(var_20, 0x4a8997);
    rax = sqlite3_column_text(var_38, 0x1);
    rax = strcmp(var_28, rax);
    if (LODWORD(rax) != 0x0) goto loc_40572f;

loc_405690:
    *(var_70 + 0x10) = malloc(LOBYTE(var_50 & 0xff) & 0xff);
    *(int8_t *)(var_70 + 0x18) = LOBYTE(var_50 & 0xff);
    rax = memcpy(*(var_70 + 0x10), var_48, LOBYTE(var_50 & 0xff) & 0xff);
    rax = sqlite3_column_int(var_38, 0x2);
    rax = populate_client_actions(var_68, var_70, LODWORD(rax));
    var_54 = LODWORD(sqlite3_column_int(var_38, 0x2));
    rax = send(LODWORD(*(int32_t *)var_70), &var_54, 0x4, 0x0);
    LODWORD(rax) = 0x1;
    return;

loc_40572f:
    rax = puts("Unauthorized Login Attempt.");
    goto loc_405739;
}