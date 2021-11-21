#318175197 Idan Ziv
.section    .rodata
    .extern scanf
    .align 8
    #literals for scanf and printf
    format_int:     .string "%d"
    format_str:     .string "%s"
    .text
    .global run, main
    .type run, @function
main:
    movq %rsp, %rbp #for correct debugging
    call run
run:
    #intial stack frame for the procedure
    pushq %rbp
    movq %rsp, %rbp
    #make space for a pstring - lets check if i know how to read them
    subq $500, %rsp #the size of a p string
    #reading the size of the pstring
    movq $format_int, %rdi #passing the data format for scanf 
    leaq -500(%rbp), %rsi #passing the address to store the size
    movq $0, %rax
    call scanf
    #reading the string
    movq $format_str, %rdi
    leaq -499(%rbp), %rsi
    movq $0, %rax
    call scanf
    
 
    