// verify_key(&var_90)
int _Z10verify_keyPc(int * arg0) {
    var_18 = arg0;
    if ((strlen(var_18) > 0x9) && (strlen(var_18) <= 0x40)) {
            rax = enc(var_18);
            rax = strcmp(0x3c00, rax);
            rax = rax == 0x0 ? 0x1 : 0x0;
    }
    else {
            rax = 0x0;
    }
    return rax;
}

 _ZN3obfL4timeE:        // obf::time
0000000000003bf0         db  0x31 ; '1'
0000000000003bf1         db  0x34 ; '4'
0000000000003bf2         db  0x3a ; ':'
0000000000003bf3         db  0x33 ; '3'
0000000000003bf4         db  0x36 ; '6'
0000000000003bf5         db  0x3a ; ':'
0000000000003bf6         db  0x30 ; '0'
0000000000003bf7         db  0x30 ; '0'
0000000000003bf8         db  0x00 ; '.'
0000000000003bf9         db  0x00 ; '.'
0000000000003bfa         db  0x00 ; '.'
0000000000003bfb         db  0x00 ; '.'

 _ZN3obfL4seedE:        // obf::seed
0000000000003bfc         db  0x50 ; 'P'
0000000000003bfd         db  0xcd ; '.'
0000000000003bfe         db  0x00 ; '.'
0000000000003bff         db  0x00 ; '.'
// strcmp(0x3c00, rax); -> 16 chats
0000000000003c00         db  0xae ; '.'                                         ; DATA XREF=_Z10verify_keyPc+71
0000000000003c01         db  0x9e ; '.'
0000000000003c02         db  0xff ; '.'
0000000000003c03         db  0x9c ; '.'
0000000000003c04         db  0xab ; '.'
0000000000003c05         db  0xc7 ; '.'
0000000000003c06         db  0xd3 ; '.'
0000000000003c07         db  0x81 ; '.'
0000000000003c08         db  0xe7 ; '.'
0000000000003c09         db  0xee ; '.'
0000000000003c0a         db  0xfb ; '.'
0000000000003c0b         db  0x8a ; '.'
0000000000003c0c         db  0x9d ; '.'
0000000000003c0d         db  0xef ; '.'
0000000000003c0e         db  0x8d ; '.'
0000000000003c0f         db  0xae ; '.'
0000000000003c10         db  0x00 ; '.'
0000000000003c11         db  0x00 ; '.'


int _Z3encPKc(int * arg0) {
    var_D8 = arg0;
    var_38 = *0x28;
    rax = 0x0;
    var_C4 = 0x3;
    var_A0 = 0x0;
    var_98 = 0x0;
    var_B8 = malloc(0x40);
    var_C0 = strlen(var_D8);
    var_B0 = malloc(0x5);
    rdi = &var_60;
    rax = obf::Num<int, 3858>::Num();
    rdi = &var_60;
    *(int8_t *)var_B0 = obf::Num<int, 3858>::get() ^ 0xffffffcc;
    rdi = &var_60;
    rax = obf::Num<int, 2568>::Num();
    rdi = &var_60;
    *(int8_t *)(var_B0 + 0x1) = obf::Num<int, 2568>::get() ^ 0xffffffa5;
    rdi = &var_60;
    rax = obf::Num<int, 1868>::Num();
    rdi = &var_60;
    *(int8_t *)(var_B0 + 0x2) = obf::Num<int, 1868>::get() ^ 0xfffffff2;
    rdi = &var_60;
    rax = obf::Num<int, 749>::Num();
    rdi = &var_60;
    *(int8_t *)(var_B0 + 0x3) = obf::Num<int, 749>::get() ^ 0x2;
    rdi = &var_60;
    rax = obf::Num<int, 1056>::Num();
    rdi = &var_60;
    *(int8_t *)(var_B0 + 0x4) = obf::Num<int, 1056>::get() ^ 0x20;
    var_90 = 0x0;
    var_88 = 0x0;
    rbx = &var_C0;
    rax = &var_BC;
    r8 = &var_C0;
    rbx = &var_C4;
    rax = &var_BC;
    stack[2016] = &var_C4;
    stack[2015] = &var_BC;
    rcx = &var_BC;
    rax = obf::for_wrapper::for_wrapper<enc(&var_80, &var_BC, &var_C4);
    stack[2015] = &var_C4;
    stack[2014] = &var_B0;
    stack[2013] = &var_D8;
    stack[2012] = &var_BC;
    stack[2011] = &var_B8;
    rsp = ((rsp - 0x10) + 0x10 - 0x30) + 0x30;
    rdi = obf::for_wrapper& obf::for_wrapper::set_body<enc(&var_80);
    rax = obf::for_wrapper::run();
    rdi = &var_80;
    rax = obf::for_wrapper::~for_wrapper();
    rdi = &var_90;
    rax = std::shared_ptr<obf::base_rvholder>::~shared_ptr();
    rbx = operator new(0x18);
    rdx = var_B8;
    rax = obf::rvholder<char*>::rvholder(rbx, var_B8);
    rsi = rbx;
    rax = std::enable_if<std::__sp_is_constructible<obf::base_rvholder, obf::rvholder<char*> >::value, void>::type std::__shared_ptr<obf::base_rvholder, (&var_A0);
    rbx = __cxa_allocate_exception(0x10);
    rsi = &var_A0;
    rax = std::shared_ptr<obf::base_rvholder>::shared_ptr(rbx);
    rax = __cxa_throw(rbx, typeinfo for std::shared_ptr<obf::base_rvholder>, std::shared_ptr<obf::base_rvholder>::~shared_ptr());
    return rax;
}

// obf::for_wrapper::for_wrapper<enc(&var_80, &var_BC, &var_C4);
int _ZN3obf11for_wrapperC2IZ3encPKcEUlvE_Z3encS3_EUlvE0_Z3encS3_EUlvE1_EET_T0_T1_(int arg0, int arg1, int arg2) {
    rax = 0x0;
    rdi = arg0;
    rax = std::unique_ptr<obf::next_step_functor_base, std::default_delete<obf::next_step_functor_base> >::unique_ptr<std::default_delete<obf::next_step_functor_base>, void>();
    rdi = arg0 + 0x8;
    rax = std::unique_ptr<obf::bool_functor_base, std::default_delete<obf::bool_functor_base> >::unique_ptr<std::default_delete<obf::bool_functor_base>, void>();
    rdi = arg0 + 0x10;
    rax = std::unique_ptr<obf::next_step_functor_base, std::default_delete<obf::next_step_functor_base> >::unique_ptr<std::default_delete<obf::next_step_functor_base>, void>();
    rdi = arg0 + 0x18;
    rax = std::unique_ptr<obf::next_step_functor_base, std::default_delete<obf::next_step_functor_base> >::unique_ptr<std::default_delete<obf::next_step_functor_base>, void>();
    rbx = operator new(0x18);
    rsi = rcx;
    rdx = r8;
    rax = obf::bool_functor<enc(rbx);
    rsi = rbx;
    rax = std::unique_ptr<obf::bool_functor_base, std::default_delete<obf::bool_functor_base> >::reset(arg0 + 0x8);
    r12 = operator new(0x18);
    rsi = arg1;
    rdx = arg2;
    rax = obf::next_step_functor<enc(r12);
    rsi = r12;
    rax = std::unique_ptr<obf::next_step_functor_base, std::default_delete<obf::next_step_functor_base> >::reset(arg0);
    rbx = operator new(0x18);
    rsi = arg_0;
    rdx = arg_8;
    rax = obf::next_step_functor<enc(rbx);
    rsi = rbx;
    rax = std::unique_ptr<obf::next_step_functor_base, std::default_delete<obf::next_step_functor_base> >::reset(arg0 + 0x10);
    rax = *0x28 ^ *0x28;
    if (rax != 0x0) {
            rax = __stack_chk_fail();
    }
    else {
            rbx = stack[2045];
            r12 = stack[2046];
            rsp = rsp + 0x68;
            rbp = stack[2047];
    }
    return rax;
}
