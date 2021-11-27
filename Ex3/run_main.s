    #318175197 Idan Ziv
    .section    .rodata
        .align 8
        #literals for scanf and printf
        format_int:     .string "%d"
        format_str:     .string "%s"
    .section    .text
        .global main
        .type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    pushq %r12
    pushq %r11 # pushq used to proper align the stack pointer adress
    subq $512, %rsp # create space for local pstrings
    movq $format_int, %rdi # sending the format for the size of the 1st p string
    leaq -512(%rbp), %rsi # loading the address to the size of the 1st pstring variable
    xorq %rax, %rax # set %rax to 0
    call scanf
    movq $format_str, %rdi # sending the format for the 1st string
    leaq -511(%rbp), %rsi # loading the address to the string of the 1st pstring variable
    xorq %rax, %rax # set %rax to 0
    call scanf
    movq $format_int, %rdi # sending the format for the size of the 2nd p string
    leaq -512(%rbp), %rsi # loading the address to the size of the 2nd pstring variable
    xorq %rax, %rax # set %rax to 0
    call scanf
    movq $format_str, %rdi # sending the format for the 2nd string
    leaq -511(%rbp), %rsi # loading the address to the string of the 2nd pstring variable
    xorq %rax, %rax # set %rax to 0
    call scanf
    ret