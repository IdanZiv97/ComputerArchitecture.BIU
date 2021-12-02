# 318175197 Idan Ziv
    .section    .rodata

    .align 8
.JUMP_TABLE:    # cases for switch case
    .quad   .f_pstrlen    # case 50
    .quad   .f_default    # case 51 - default
    .quad   .f_replaceChar    # case 52
    .quad   .f_pstrijcpy    # case 53
    .quad   .f_swapCase    # case 54
    .quad   .f_pstrijcmp    # case 55
    .quad   .f_default    # case 56 - default 
    .quad   .f_default    # case 57 - default
    .quad   .f_default    # case 58 - default
    .quad   .f_default    # case 59 - default
    .quad   .f_pstrlen    # case 60

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

    .text
    .global run_func
    .type run_func, @function
run_func:   # the case number is in %rdi (%edi), the 1st pString in %rsi, the 2nd pString in %rdx
    # create stack frame to hold the pointers to pStrings and chars that will be scaned.
    pushq    %rbp
    movq    %rsp, %rbp
    # correcting the input offset to match the first case
    leaq    -50(%rdi), %rbx # setting the choice to match the range
    cmpq    $10, %rbx # check if the choice is in range
    ja    .f_default # if the number is not in range we ha
    jmp    *.JUMP_TABLE(,%rbx,8)
    movq    %rbp, %rsp
    popq    %rbp
    ret

.f_pstrlen:
    # getting the length of the 1st pString
    movq    %rsi, %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %r11    # saving the return value from pstrlen to the stack

    # getting the length of the 2nd pString
    movq    %rdx, %rdi    # send the pointer as the parameter
    call    pstrlen
    movq    %rax, %r10    # saving the return value from pstrlen to the stack

    # print the message
    movq    $msg_pstrlen, %rdi    # pasing the proper message to printf
    movq    %r11, %rsi    # passing the length of the 1st pString
    movq    %r10, %rdx    # passing the length of the 2nd pString
    xorq    %rax, %rax    # set %rax to 0
    call    printf

    # Jump to end sequence to deallocate the stack frame
    jmp    .end_sequence

.f_replaceChar:
    # allocate memory for the two chars on the stack - 1-byte * 2
    subq    $16, %rsp    # this makes rsp as the offset, subtracted 16 in order to keep the alignment
    
    # push the pointers to the stack
    pushq    %rdx    # pointer to the 2nd pString
    pushq    %rsi    # pointer to the 1st pString
    
    # scan the oldChar
    movq    $format_scan_char, %rdi    # pass the proper scan format
    leaq    16(%rsp), %rsi    # oldChar will be saved on the stack
    xorq    %rax, %rax    # set %rax to 0
    call    scanf

    # scan the newChar
    movq    $format_scan_char, %rdi    # pass the proper scan format
    leaq    17(%rsp), %rsi    # newChar will be saved on the stack
    xorq    %rax, %rax    # set %rax to 0
    call    scanf

    # call replaceChar on the 1st pString
    popq    %rdi    # the pointer to the 1st pString
    movq    %rdi, %r12    # create a copy of the pointer for later use
    leaq    8(%rsp), %rsi    # pass oldChar as an argument to replaceChar
    leaq    9(%rsp), %rdx    # pass newChar as an argument to replaceChar    
    call    replaceChar

    # call replace char on the 2nd pString
    popq    %rdi    # the pointer to the 2nd pString, the are now in of set of 0,1
    movq    %rdi, %r14    # create a copy of the pointer for later use
    leaq    (%rsp), %rsi    # pass oldChar as an argument to replaceChar
    leaq    1(%rsp), %rdx    # pass newChar as an argument to replaceChar
    call    replaceChar

    # printing the result
    movq    $msg_replaceChar, %rdi    # pass the proper format for printf
    movzbq    (%rsp), %rsi    # pass the oldChar
    movzbq    1(%rsp), %rdx    # pass the newChar
    # pass the pointer, recall they must be adjusted to the start of the string itself
    movq    %r12, %rcx    # 1st pString pointer
    incq    %rcx
    movq    %r14, %r8     # 2nd pString pointer
    incq    %r8
    xorq    %rax, %rax    # set %rax to 0
    call    printf
    # restoring the stack frame
    movq    %rbp, %rsp
    popq    %rbp
    ret


.f_pstrijcpy:
    # get the i index - save on stack
    movq    $format_scan_int, %rdi    # pass the proper format to scanf
    leaq    -32(%rbp), %rsi    # pass the address of i
    xorq    %rax, %rax    # set %rax to 0
    call    scanf
    # movq    %rax, %rdx    # saving the the index 
    # get the j index - save on stack
    leaq    -24(%rbp), %rsi   # pass the address of j, note that the correct format is in %rdi
    xorq    %rax, %rax    # set %rax to 0
    call    scanf
    # movq    %rax, %rcx
    # prep parameters to pstrijcpy
    leaq    -48(%rbp), %rdi    # dest - the 1st pString
    leaq    -40(%rbp), %rsi    # src - the 2nd Pstring
    leaq    -32(%rbp), %rdx    # index i
    leaq    -24(%rbp), %rcx    # index j 
    call    pstrijcpy    # call pstrijcpy
    movq    %rax, -16(%rbp)    # saving the pointer to pString from pstrijcpy

    # print the pStrings by the proper format
    
    # 1st pString - destination (actually the new pString)
    movq    -16(%rbp), %rdi    
    call    pstrlen    # calculating the legth of the pString
    movq    %rax, %rsi    # will be used later when calling for printf
    movq    -16(%rbp), %rdx    # passing the pointer of the pString for printf
    incq    %rdx    # adjusting the pointer to the string part of the pString
    movq    $format_pstr_info, %rdi    # passing the proper format for prtinf
    xorq    %rax, %rax  # set %rax to 0
    call    printf

    # 2nd pString - src (the 2nd pString)
    movq    -40(%rbp), %rdi
    call    pstrlen    # calculating the length of the pString
    movq    %rax, %rsi    # will be used later when calling for printf
    movq    -40(%rbp), %rdx     # passing the pointer to the pString as a parameter to printf
    incq    %rdx    # adjusting the pointer to the string part of the string
    movq    $format_pstr_info, %rdi    # passing the proper format to printf
    xorq    %rax, %rax  # set %rax to 0
    call printf

    # end of the case, initiate end sequence
    jmp    .end_sequence

.f_swapCase:
    ret

.f_pstrijcmp:
    ret

.f_default:
    movq    $msg_default_case, %rdi
    xorq    %rax, %rax
    call printf
    ret

.end_sequence:
    # restore the data saved to the proper registers
    movq    -48(%rbp), %rsi
    movq    -40(%rbp), %rdx
    # set the old process stack frame
    addq    $48, %rsp    # deallocate the stack frame
    movq    %rbp, %rsp
    popq    %rbp
    ret