/********************** FOR LOOP ***************************/

/********************** INITIAL ***************************/
// enc(char const*)::{lambda()#1}::operator()() const
int _ZZ3encPKcENKUlvE_clEv() {
    var_38 = rdi;
    LODWORD(rax) = 0x0;
    rdi = &var_30;
    rax = obf::Num<int, 2520>::Num();
    rdi = &var_30;
    var_2C = LODWORD(LODWORD(obf::Num<int, 2520>::get()) ^ 0x9d8);
    var_28 = *var_38;
    rdi = &var_28;
    rax = enc();
    stack[2037] = rbx;
    rsp = (rsp - 0x10) + 0x10;
    var_20 = obf::refholder<int> obf::operator<< <int>(*var_38, rsi);
    rsi = &var_2C;
    rax = obf::refholder<int>::operator=(&var_20);
    LODWORD(rax) = *(int32_t *)*(var_38 + 0x8);
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = var_8;
    }
    return rax;
}

// var_20 = obf::refholder<int> obf::operator<< <int>(*var_38, rsi);
void _ZN3obflsIiEENS_9refholderIT_EENS_13stream_helperERS2_(int arg0, void * arg1) {
    rsi = arg1;
    rax = 0x0;
    rsi = arg0;
    rax = obf::refholder<int>::refholder(&var_10);
    rax = var_10;
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    return;
}

// rax = enc();
int _ZZZ3encPKcENKUlvE_clEvENKUlvE_clEv() {
    rax = 0x0;
    rsi = *rdi;
    rax = obf::extra_addition<int>::extra_addition(&var_30);
    rdi = &var_30;
    rax = obf::extra_addition<int>::~extra_addition();
    rax = rbx;
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = stack[2046];
            rsp = rsp + 0x48;
            rbp = stack[2047];
    }
    return rax;
}

// rax = obf::extra_addition<int>::extra_addition(&var_30);
int _ZN3obf14extra_additionIiEC1ERi(int * arg0) {
    *arg0 = 0x206ae8;
    *(arg0 + 0x8) = rsi;
    rax = *(arg0 + 0x8);
    *(int32_t *)rax = *(int32_t *)*(arg0 + 0x8) + 0xb1;
    rsp = rsp + 0x8;
    rbp = stack[2047];
    return rax;
}

// rax = obf::extra_addition<int>::~extra_addition();
int _ZN3obf14extra_additionIiED2Ev() {
    *rdi = 0x206ae8;
    rax = *(rdi + 0x8);
    *(int32_t *)rax = *(int32_t *)*(rdi + 0x8) - 0xb1;
    rsp = rsp + 0x8;
    rbp = stack[2047];
    return rax;
}

/********************** CONDITION ***************************/

// enc(char const*)::{lambda()#2}::operator()() const
int _ZZ3encPKcENKUlvE0_clEv() {
    var_38 = rdi;
    LODWORD(rax) = 0x0;
    var_2C = LODWORD(LODWORD(*(int32_t *)*(var_38 + 0x8)) - 0x1);
    var_28 = *var_38;
    rdi = &var_28;
    rax = enc();
    stack[2037] = rbx;
    rsp = (rsp - 0x10) + 0x10;
    var_20 = obf::refholder<int> obf::operator<< <int>(*var_38, rsi);
    rsi = &var_2C;
    rax = obf::refholder<int>::operator<(&var_20);
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = var_8;
    }
    return rax;
}

// enc();
int _ZZZ3encPKcENKUlvE0_clEvENKUlvE_clEv() {
    LODWORD(rax) = 0x0;
    rsi = *rdi;
    rax = obf::extra_addition<int>::extra_addition(&var_30);
    rdi = &var_30;
    rax = obf::extra_addition<int>::~extra_addition();
    LODWORD(rax) = LODWORD(rbx);
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = stack[2046];
            rsp = rsp + 0x48;
            rbp = stack[2047];
    }
    return rax;
}


/********************** Increment ***************************/

// enc(char const*)::{lambda()#3}::operator()() const
int _ZZ3encPKcENKUlvE1_clEv() {
    var_38 = rdi;
    rax = 0x0;
    var_2C = 0x1;
    var_28 = *var_38;
    rdi = &var_28;
    rax = enc();
    stack[2037] = rbx;
    rsp = (rsp - 0x10) + 0x10;
    var_20 = obf::refholder<int> obf::operator<< <int>(*var_38, rsi);
    rsi = &var_2C;
    rax = obf::refholder<int>::operator+=(&var_20);
    rax = *(int32_t *)*(var_38 + 0x8);
    rcx = *0x28 ^ *0x28;
    if (rcx != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = var_8;
    }
    return rax;
}

/********************** Body ***************************/

// enc(char const*)::{lambda()#4}::operator()() const
int _ZZ3encPKcENKUlvE2_clEv() {
    var_88 = rdi;
    rax = 0x0;
    var_50 = *(var_88 + 0x10);
    var_48 = *(var_88 + 0x8);
    rdi = &var_50;
    rax = enc();
    stack[2027] = rbx;
    var_70 = obf::refholder<char const> obf::operator<< <char const>(sign_extend_32(*(int32_t *)*(var_88 + 0x8)) + **(var_88 + 0x10), rsi);
    rdi = &var_70;
    rbx = obf::refholder<char const>::operator char const();
    var_40 = *(var_88 + 0x18);
    var_38 = *(var_88 + 0x8);
    rdi = &var_40;
    rax = enc();
    rdx = *(int32_t *)*(var_88 + 0x8) & 0x80000000 ? 0xffffffff : 0x0;
    stack[2027] = r13;
    var_68 = obf::refholder<char> obf::operator<< <char>(sign_extend_32((*(int32_t *)*(var_88 + 0x8) + (rdx >> 0x1e) & 0x3) - (rdx >> 0x1e)) + **(var_88 + 0x18), rsi);
    rdi = &var_68;
    var_79 = obf::refholder<char>::operator char() ^ rbx;
    var_60 = *var_88;
    var_58 = *(var_88 + 0x8);
    rdi = &var_60;
    rax = enc();
    stack[2027] = r12;
    rsp = (((rsp - 0x10) + 0x10 - 0x10) + 0x10 - 0x10) + 0x10;
    var_78 = obf::refholder<char> obf::operator<< <char>(sign_extend_32(*(int32_t *)*(var_88 + 0x8)) + **var_88, rsi);
    rsi = &var_79;
    rax = obf::refholder<char>::operator=(&var_78);
    rax = *(int32_t *)*(var_88 + 0x20);
    rsi = *0x28 ^ *0x28;
    if (rsi != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = stack[2044];
            r12 = stack[2045];
            r13 = stack[2046];
            rsp = &var_18 + 0x20;
            rbp = stack[2047];
    }
    return rax;
}



