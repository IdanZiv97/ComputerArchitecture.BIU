# 318175197 Idan Ziv
    .section    .rodata

    .align 8
.JUMP_TABLE:    # cases for switch case
    .quad   .f_pstrlen #case 50
    .quad   .f_default #case 51 - default
    .quad   .f_replaceChar #case 52
    .quad   .f_pstrijcpy #case 53
    .quad   .f_swapCase #case 54
    .quad   .f_pstrijcmp #case 55
    .quad   .f_default #case 56 - default 
    .quad   .f_default #case 57 - default
    .quad   .f_default #case 58 - default
    .quad   .f_default #case 59 - default
    .quad   .f_strlen #case 60

    # literals for pstr.h functions
    msg_pstrlen:     .string "first pstring length: %d,second pstring length: %d\n"
    msg_replaceChar:    .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
    format_pstr_info:   .string "lenght: %d, string: %s\n"
    msg_pstrijcmp:  .string "comapre result: %d\n"
    msg_default_case:   .string "invalid option\n"
    # literals for scanf, printf
    format_scan_int:     .string "%d"
    format_scan_char:    .string "%c"
    format_scan_string:    .string "%s"

    .text
    .global run_func
    .type run_func, @function
run_func:   # the case number is in %rdi (%edi), the 1st pString in %rsi, the 2nd pString in %rdx
    # correcting the input offset to match the first case
    leaq -50(%rdi), %rbx # setting the choice to match the range
    cmpq $10, %rbx # check if the choice is in range
    ja .f_default # if the number is not in range we ha
    jmp *.JUMP_TABLE(,%rsi,8)

.f_pstrlen:
    # creating stack frame - saving the pString pointers
    pushq    %rbp
    movq    %rsp, %rbp
    pushq    %rsi    # saving the 1st pString pointer
    pushq    %rdx    # saving the 2nd pString poiner

    # getting the length of the 1st pString
    leaq    -8(%rbp), %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %rsi    # saving the return value in %rsi

    # getting the length of the 2nd pString
    leaq    -16(%rbp), %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %rdx    # saving the return value in %rdi

    # print the message
    movq    $msg_pstrlen, %rdi    # pasing the proper message to printf
    call    printf    # Note: in %rsi and %rdx we saved the return values from calling pstrlen

    # resotre the stack frame
    popq    %rdx
    popq    %rsi
    popq    %rbp
    movq    %rbp, %rsp
    ret