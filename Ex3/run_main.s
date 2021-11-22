#318175197 Idan Ziv
.section    .rodata
    .align 8
    #literals for scanf and printf
    format_int:     .string "%d"
    format_str:     .string "%s"
.section    .text
    .global run_main, main
    .type run_main, @function
main:
    call run_main
run_main:
    pushq %rbp
    movq %rsp, %rbp
    subq $528, %rsp #create space for local pstrings
    movq $format_int, %rdi #sending the format for the size of the 1st p string
    leaq -528(%rbp), %rsi #sedning the addres to the size of the 1st pstring variable
    xorq %rax, %rax #set %rax to 0
    call scanf
    ret