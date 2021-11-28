    # 318175197 Idan Ziv check the tertain
    .section    .rodata
        .align 8
        # literals for scanf and printf
        format_int:     .string "% d"
        format_str:     .string "% s\0"
        format_test1:    .string "pstr1: %d, %s\n"
        format_test2:   .string "pstr2: %d, %s\n"
        format_test3:   .string "choice: %d\n"
    .section    .text
        .global main
        .type main, @function
main:
    movq %rsp, %rbp #for correct debugging
    # initialize the stack frame
    pushq   %rbp
    movq    %rsp, %rbp
    # pushq used to proper align the stack pointer adress
    pushq   %r12
    # pushq   %r11
    # Creating the stack frame for the function
    subq    $536, %rsp  # two pStrings (256 * 2 = 512) and 1 int for the choice (8 bytes for the address)

    # 1st pString

    # get the length
    movq    $format_int, %rdi    # pass the 1st argument for scanf
    leaq    -528(%rbp), %rsi    # pass the 2nd argument for scanf
    xorq    %rax, %rax
    call    scanf
    # get the string
    movq    $format_str, %rdi    # pass the 1st argument for scanf
    leaq    -527(%rbp), %rsi    # pass the 2nd argument for scanf
    xorq    %rax, %rax
    call    scanf

    # 2nd pstring
    # get the length
    movq    $format_int, %rdi    # pass the 1st argument for scanf
    leaq    -272(%rbp), %rsi    # pass the 2nd argument for scanf
    xorq    %rax, %rax
    call    scanf
    # get the string
    movq    $format_str, %rdi    # pass the 1st argument for scanf
    leaq    -271(%rbp), %rsi    # pass the 2nd argument for scanf
    xorq    %rax, %rax
    call    scanf

    # get the users choice

    movq    $format_int, %rdi   # pass the 1st argument for scanf
    leaq    -16(%rbp), %rsi    # pass the 2nd argument for scanf
    xorq    %rax, %rax
    call scanf

    # print

    movq    $format_test1, %rdi
    leaq    -528(%rbp), %rsi
    leaq    -527(%rbp), %rcx
    xorq    %rax, %rax
    call printf

    movq    $format_test2, %rdi
    leaq    -272(%rbp), %rsi
    leaq    -271(%rbp), %rcx
    xorq    %rax, %rax
    call printf

    movq    $format_test3, %rdi
    leaq    -16(%rbp), %rsi
    xorq    %rax, %rax
    call printf

    popq    %r11
    popq    %r12
    popq    %rbp
    movq    %rbp, %rsp
    ret