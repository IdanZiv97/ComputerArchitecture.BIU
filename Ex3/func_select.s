# 318175197 Idan Ziv
    .section    .rodata

    .align 8
.JUMP_TABLE:    # cases for switch case
    .quad   .f_pstrlen    #case 50
    .quad   .f_default    #case 51 - default
    .quad   .f_replaceChar    #case 52
    .quad   .f_pstrijcpy    #case 53
    .quad   .f_swapCase    #case 54
    .quad   .f_pstrijcmp    #case 55
    .quad   .f_default    #case 56 - default 
    .quad   .f_default    #case 57 - default
    .quad   .f_default    #case 58 - default
    .quad   .f_default    #case 59 - default
    .quad   .f_pstrlen    #case 60

    # literals for pstr.h functions
    msg_pstrlen:     .string    "first pstring length: %d,second pstring length: %d\n"
    msg_replaceChar:    .string    "old char: %c, new char: %c, first string: %s, second string: %s\n"
    format_pstr_info:   .string    "lenght: %d, string: %s\n"
    msg_pstrijcmp:    .string    "comapre result: %d\n"
    msg_default_case:    .string    "invalid option\n"
    # literals for scanf, printf
    format_scan_int:     .string    "%d"
    format_scan_char:    .string    " %c"
    format_scan_string:    .string    " %s"

    # literal for jump table tests
    test_pstrlen:    .string    "pstrlen case has been invoked\n"
    test_replaceChar:    .string    "replaceChar case has been invoked\n"
    test_pstrijcpy:    .string    "pstrijcpy case has been invoked\n"
    test_swapCase:    .string    "swapCase case has been invoked\n"
    test_pstrijcmp:    .string    "pstrijcmp case has been invoked\n"
    test_defaultCase:    .string    "default case has been invoked\n"
    
    .text
    .global run_func
    .type run_func, @function
run_func:   # the case number is in %rdi (%edi), the 1st pString in %rsi, the 2nd pString in %rdx
    # create stack frame to hold the pointers to pStrings and chars that will be scaned.
    pushq    %rbp
    movq    %rsp, %rbp
    subq    $48, %rsp    # Note: we need to hold only 8 refrences (2 pointers and 2 chars or 2 indexes) but it is not a
                         # multiple of 16 - so the we align the stack pointer to 48
    movq    %rsi, -48(%rbp)    # save the pointer to the 1st pString
    movq    %rdx, -40(%rbp)    # save the pointer to the 2nd Pstring
    # correcting the input offset to match the first case
    leaq    -50(%rdi), %rbx # setting the choice to match the range
    cmpq    $10, %rbx # check if the choice is in range
    ja    .f_default # if the number is not in range we ha
    jmp    *.JUMP_TABLE(,%rbx,8)

.end_sequence:
    # restore the data saved to the proper registers
    movq    -48(%rbp), %rsi
    movq    -40(%rbp), %rdx
    # set the old process stack frame
    addq    $48, %rsp    # deallocate the stack frame
    movq    %rbp, %rsp
    popq    %rbp
    ret

.f_pstrlen:
    # creating stack frame - saving the pString pointers
    pushq    %rbp
    movq    %rsp, %rbp

    # getting the length of the 1st pString
    leaq    -48(%rbp), %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %rsi    # saving the return value in %rsi

    # getting the length of the 2nd pString
    leaq    -40(%rbp), %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %rdx    # saving the return value in %rdi

    # print the message
    movq    $msg_pstrlen, %rdi    # pasing the proper message to printf
    call    printf    # Note: in %rsi and %rdx we saved the return values from calling pstrlen

    # Jump to end sequence to deallocate the stack frame
    jmp    .end_sequence

.f_replaceChar:
    # scan and save the oldCahr
    movq    $format_scan_char, %rdi    # pass the proper format
    leaq    -32(%rbp), %rsi    # pass the address of oldChar
    xorq    %rax, %rax    # set %rax to 0
    call    scanf
    # scan and save the newChar
    leaq    -24(%rbp), %rsi     # pass the address of oldChar, note that the format hasn't changed
    xorq    %rax, %rax
    call    scanf
    # init repalceChar on 1st pString
    leaq    -48(%rbp), %rdi    # pass the pointer to 1stPstring
    leaq    -32(%rbp), %rsi    # pass the oldChar
    leaq    -24(%rbp), %rdx    # pass the newChar
    call    replaceChar
    movq    %rax, %r8    # save the pointer to the new pString from replaceChar
                         # %r8 will later be used to pass the pointer to printf
    # init replaceChar on 2nd pString
    leaq    -40(%rbp), %rdi    # pass the pointer to 1stPstring
    leaq    -32(%rbp), %rsi    # pass the oldChar
    leaq    -24(%rbp), %rdx    # pass the newChar
    call    replaceChar
    movq    %rax, %rcx    # save the pointer to the new pString from replaceChar
    # set the arguments and format to pString
    movq    $msg_replaceChar, %rdi    # foramt
    leaq    -32(%rbp),  %rsi    # oldChar
    leaq    -24(%rbp),  %rdx    # newChar
    incq    %r8    # 1st pString - we increment by 1, so we will 'skip' to the start of the string itself
    incq    %rcx    # 2nd pString - we increment by 1, so we will 'skip' to the start of the string istelf
    xorq    %rax, %rax    # set %rax to 0
    call    printf
    jmp    end_sequence

.f_pstrijcpy:
    movq    $test_pstrijcpy, %rdi
    xorq    %rax, %rax
    call printf
    ret

.f_swapCase:
    movq    $test_swapCase, %rdi
    xorq    %rax, %rax
    call    printf
    ret

.f_pstrijcmp:
    movq    $test_pstrijcmp, %rdi
    xorq    %rax, %rax
    call    printf
    ret

.f_default:
    movq    $test_defaultCase, %rdi
    xorq    %rax, %rax
    call printf
    ret