void main(int arg0, int arg1) {
    if (system("uname -a | grep Linux > /dev/null") == 0x0) goto loc_405390;

loc_40537c:
    puts("Must be on a linux system");
    exit(0xffffffff);
    return;

loc_405390:
    initial_setup(&var_340);
    build_server(&var_340);
    goto loc_4053ae;

loc_4053ae:
    handle_connections(&var_340);
    goto loc_4053ae;
}


int initial_setup(int arg0) {
    var_18 = arg0;
    memset(var_18, 0x0, 0x338);
    if (sqlite3_open("Banking.db", var_18 + 0x10) != 0x0) {
            puts("Failed to connect to database");
            rax = exit(0x1);
    }
    else {
            if (sqlite3_prepare_v2(*(var_18 + 0x10), "SELECT SQLITE_VERSION()", 0xffffffff, &var_10, 0x0) != 0x0) {
                    fprintf(*stderr@@GLIBC_2.2.5, "Failed to fetch data: %s\n", sqlite3_errmsg(*(var_18 + 0x10)));
                    rax = sqlite3_close(*(var_18 + 0x10));
            }
            else {
                    rax = populate_actions(var_18);
            }
    }
    return rax;
}

asm populate_actions() {
	; populate_actions:
	0000000000404866         push       rbp           ; Begin of unwind block (FDE at 0x4b8554), CODE XREF=initial_setup+201
	0000000000404867         mov        rbp, rsp
	000000000040486a         mov        qword [rbp+var_8], rdi
	000000000040486e         mov        rax, qword [rbp+var_8]
	0000000000404872         mov        qword [rax+0x18], login
	000000000040487a         mov        rax, qword [rbp+var_8]
	000000000040487e         mov        qword [rax+0x20], check_balance
	0000000000404886         mov        rax, qword [rbp+var_8]
	000000000040488a         mov        qword [rax+0x28], create_account
	0000000000404892         mov        rax, qword [rbp+var_8]
	0000000000404896         mov        qword [rax+0x30], faulty_deposit
	000000000040489e         mov        rax, qword [rbp+var_8]
	00000000004048a2         mov        qword [rax+0x48], send_funds
	00000000004048aa         mov        rax, qword [rbp+var_8]
	00000000004048ae         mov        qword [rax+0x58], keep_alive
	00000000004048b6         mov        rax, qword [rbp+var_8]
	00000000004048ba         mov        qword [rax+0x60], update_user
	00000000004048c2         mov        rax, qword [rbp+var_8]
	00000000004048c6         mov        qword [rax+0x70], fibonacci
	00000000004048ce         mov        rax, qword [rbp+var_8]
	00000000004048d2         mov        qword [rax+0x80], ackermann_function
	00000000004048dd         mov        rax, qword [rbp+var_8]
	00000000004048e1         mov        qword [rax+0x88], memory_Allocator
	00000000004048ec         mov        rax, qword [rbp+var_8]
	00000000004048f0         mov        qword [rax+0x98], MD5
	00000000004048fb         mov        rax, qword [rbp+var_8]
	00000000004048ff         mov        qword [rax+0xa0], SHA1
	000000000040490a         mov        rax, qword [rbp+var_8]
	000000000040490e         mov        qword [rax+0xa8], SHA256
	0000000000404919         mov        rax, qword [rbp+var_8]
	000000000040491d         mov        qword [rax+0xe0], SHA512
	0000000000404928         mov        rax, qword [rbp+var_8]
	000000000040492c         mov        qword [rax+0xf0], RSA
	0000000000404937         mov        rax, qword [rbp+var_8]
	000000000040493b         mov        qword [rax+0x120], ROT13
	0000000000404946         mov        rax, qword [rbp+var_8]
	000000000040494a         mov        qword [rax+0x138], quick_sort
	0000000000404955         mov        rax, qword [rbp+var_8]
	0000000000404959         mov        qword [rax+0x150], merge_sort
	0000000000404964         mov        rax, qword [rbp+var_8]
	0000000000404968         mov        qword [rax+0x160], bubble_sort
	0000000000404973         mov        rax, qword [rbp+var_8]
	0000000000404977         mov        qword [rax+0x170], dijkstra_algorithm
	0000000000404982         mov        rax, qword [rbp+var_8]
	0000000000404986         mov        qword [rax+0x198], quad_form
	0000000000404991         mov        rax, qword [rbp+var_8]
	0000000000404995         mov        qword [rax+0x1a8], fizz_buzz
	00000000004049a0         mov        rax, qword [rbp+var_8]
	00000000004049a4         mov        qword [rax+0x1b0], binary_tree
	00000000004049af         mov        rax, qword [rbp+var_8]
	00000000004049b3         mov        qword [rax+0x1e8], euclid_algorithm
	00000000004049be         mov        rax, qword [rbp+var_8]
	00000000004049c2         mov        qword [rax+0x1f8], search_for_number_in_list
	00000000004049cd         mov        rax, qword [rbp+var_8]
	00000000004049d1         mov        qword [rax+0x208], largest_number_in_a_list
	00000000004049dc         mov        rax, qword [rbp+var_8]
	00000000004049e0         mov        qword [rax+0x228], sieve_of_Eratosthenes
	00000000004049eb         mov        rax, qword [rbp+var_8]
	00000000004049ef         mov        qword [rax+0x230], spew
	00000000004049fa         mov        rax, qword [rbp+var_8]
	00000000004049fe         mov        qword [rax+0x248], data_compression
	0000000000404a09         mov        rax, qword [rbp+var_8]
	0000000000404a0d         mov        qword [rax+0x250], simulate_monty_hall_problem
	0000000000404a18         mov        rax, qword [rbp+var_8]
	0000000000404a1c         mov        qword [rax+0x258], random_string
	0000000000404a27         mov        rax, qword [rbp+var_8]
	0000000000404a2b         mov        qword [rax+0x260], time
	0000000000404a36         mov        rax, qword [rbp+var_8]
	0000000000404a3a         mov        qword [rax+0x268], rock_paper_scissors
	0000000000404a45         mov        rax, qword [rbp+var_8]
	0000000000404a49         mov        qword [rax+0x270], palindrome
	0000000000404a54         mov        rax, qword [rbp+var_8]
	0000000000404a58         mov        qword [rax+0x298], average
	0000000000404a63         mov        rax, qword [rbp+var_8]
	0000000000404a67         mov        qword [rax+0x2c0], longest_subsequence
	0000000000404a72         mov        rax, qword [rbp+var_8]
	0000000000404a76         mov        qword [rax+0x2e8], matrix_multiplication
	0000000000404a81         mov        rax, qword [rbp+var_8]
	0000000000404a85         mov        qword [rax+0x308], process_pending
	0000000000404a90         mov        rax, qword [rbp+var_8]
	0000000000404a94         mov        qword [rax+0x318], send_arb_funds
	0000000000404a9f         mov        rax, qword [rbp+var_8]
	0000000000404aa3         mov        qword [rax+0x320], create_login
	0000000000404aae         mov        rax, qword [rbp+var_8]
	0000000000404ab2         mov        qword [rax+0x328], dereference_null
	0000000000404abd         nop
	0000000000404abe         pop        rbp
}


void login(void * ut) {
    var_68 = ut;
    var_70 = rsi;
    var_50 = *(int16_t *)(*(var_70 + 0x8) + 0x8) & 0xffff;
    var_48 = *(var_70 + 0x8) + 0xa;
    var_40 = *(var_70 + 0x8) + (var_50 & 0xff & 0xff) + 0xa;
    for (var_4 = 0x0; (var_4F & 0xff & 0xff) > var_4; var_4 = var_4 + 0x1) {
            if ((*(int8_t *)(sign_extend_32(var_4) + var_40) & 0xff) > 0x40) {
                    *(int8_t *)(sign_extend_32(var_4) + var_40) = *(int8_t *)(sign_extend_64(var_4) + var_40) & 0xff | 0x20;
            }
    }
    printf("Looking up User");
    fflush(*__TMC_END__);
    for (var_8 = 0x0; var_8 <= 0x2; var_8 = var_8 + 0x1) {
            putchar(0x2e);
            fflush(*__TMC_END__);
    }
    putchar(0xa);
    var_14 = sqlite3_prepare_v2(*(var_68 + 0x10), "SELECT * from user where userID == (?1)", 0xffffffff, &var_38, 0x0);
    sqlite3_bind_text(var_38, 0x1, var_48, var_50 & 0xff & 0xff, 0x0);
    if (var_14 == 0x0) goto loc_4055cc;

loc_40559b:
    fprintf(*stderr@@GLIBC_2.2.5, "Failed to fetch data: %s\n", sqlite3_errmsg(*(var_68 + 0x10)));
    goto loc_405739;

loc_405739:
    var_54 = 0xffffffff;
    send(*(int32_t *)var_70, &var_54, 0x4, 0x0);
    return;

loc_4055cc:
    if (sqlite3_step(var_38) == 0x64) goto loc_405608;

loc_4055e1:
    printf("ERROR Selecting: %s\n", sqlite3_errmsg(*(var_68 + 0x10)));
    goto loc_405739;

loc_405608:
    var_20 = malloc(sign_extend_32((var_4F & 0xff & 0xff) + 0x1));
    memcpy(var_20, var_40, var_4F & 0xff & 0xff);
    *(int8_t *)(var_20 + (var_4F & 0xff & 0xff)) = 0x0;
    if (strcmp(crypt(var_20, 0x4a8997), sqlite3_column_text(var_38, 0x1)) != 0x0) goto loc_40572f;

loc_405690:
    *(var_70 + 0x10) = malloc(var_50 & 0xff & 0xff);
    *(int8_t *)(var_70 + 0x18) = var_50 & 0xff;
    memcpy(*(var_70 + 0x10), var_48, var_50 & 0xff & 0xff);
    populate_client_actions(var_68, var_70, sqlite3_column_int(var_38, 0x2));
    var_54 = sqlite3_column_int(var_38, 0x2);
    send(*(int32_t *)var_70, &var_54, 0x4, 0x0);
    return;

loc_40572f:
    puts("Unauthorized Login Attempt.");
    goto loc_405739;
}



