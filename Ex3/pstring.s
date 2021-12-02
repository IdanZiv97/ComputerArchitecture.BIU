#318175197 Idan Ziv
.section .rodata
    .align 8
    format_invalidInput: .string "invalid input!\n"

    .text
    .global pstrlen
    .type pstrlen, @function
pstrlen: # the pstring address is saved on %rdi
    # There is no need to create a stack frame, since we are not using any local vars
    movzbq (%rdi), %rax # the length of the pstring is the on the first address of the pstring
    ret

    .global replaceChar
    .type replaceChar, @function
replaceChar: # %rdi- pointer to pstring, %rsi - oldChar, %rdx - new char
    # Note: we are changing the pString itself, so we don't create a new pString,
    #       but we return the same pointer that we got
    movq    %rdi, %rax    # setting the return value to be the pointer we are working with
    # create a pointer to the end of the string
    movzbq    (%rdi), %r9     # saving the size of the pString
    leaq    (%rdi, %r9), %rdi    # creating a pointer to the end of the string
    movb    (%rsi), %r10b    # Note: we have pointers to chars saved in the memory, so we need to derefernce
    movb    (%rdx), %r11b    # them in order to perfom the comparisons and rewrites
    # starting from the end of the string, all the way down
    # when we reach to the address of the size we will stop (since we covered the whole string)
.replaceChar_doWhile:
    cmpb    %r10b, (%rdi)    # check if the current char in the string equals to the oldChar (which is save as a byte)
    je    .replaceChar_makeSwap   
    decq    %rdi    # == pstr--
    cmpq    %rdi, %rax    # check if we reached the end
    jl    .replaceChar_doWhile    # continue the loop
    ret
.replaceChar_makeSwap:
    movb    %r11b, (%rdi)    # write the newChar instead of the oldChar)
    decq    %rdi    # == pstr--
    cmpq    %rdi, %rax    # check if we reach the end
    jl    .replaceChar_doWhile
    ret
    

    .global pstrijcpy
    .type pstrijcpy, @function
pstrijcpy: # %rdi - dst, %rsi - src, %rdx -i, %rcx - j
    # save the old frame base pointer and, set new one
    pushq %rbp
    movq %rsp,      %rbp
    # Check for proper range
    # test for i < des.length
    cmpb (%rdi),    %dl
    ja .pstrijcpy_invalidInput    # if not - invalid input
    # test for j < det.length
    cmpb (%rdi),    %cl
    ja .pstrijcpy_invalidInput    # if not - invalid input
    # test for i < src.length
    cmpb (%rsi),    %dl
    ja .pstrijcpy_invalidInput    # if not - invalid input
    # test for j < src.length
    cmpb (%rsi),    %cl
    ja .pstrijcpy_invalidInput    # if not - invalid input
    # first update the pointers - dealing with addresses
    leaq (%rsi, %rdx),      %r8    # src -> src + i
    leaq (%rdi, %rdx),      %r9    # dst -> dst + i
    leaq (%rsi, %rcx),      %r10    # src -> src +j: as an end mark to the end of the copy process
    # do while:
.pstrijcpy_while:
    # copy the char - two steps since you cant mov form memory to memory
    movb (%r8),     %r11b
    movb %r11b,     (%r9)  
    # increase the pointers
    addq $1,     %r8
    addq $1,     %r9
    # check to see if we reached the end
    cmpq %r8,    %r10
    jne .pstrijcpy_while # if not continue the loop
    # end of the liip
    leave
    movq %rdi,  %rax
    ret
.pstrijcpy_invalidInput:
    # we need to use %rdi so we will push it
    pushq %rdi
    movq $format_invalidInput,  %rdi # pass the string format for printf
    xorq %rax, %rax
    call printf
    # we need to return the pstr pointer
    pop %rdi
    movq %rdi, %rax
    ret

    .global swapCase
    .type swapCase, @function
swapCase: # %rdi - *pstr
    # create a pointer to the end
    movq (%rdi), %rsi
    leaq (%rdi, %rsi),  %r8 # the end of the str 
.swapCase_checkChar: # checking if the value of the current char is in a proper range
    # check if pstr[i] < 65 or pstr[i] > 122 - if so it is not a char
    cmpb $65,   (%r8) # ?: pstr[i] >= 65
    jl .swapCase_nextChar
    cmpb $122, (%r8) # ?: pstr[i] <= 122
    ja .swapCase_nextChar
    # check if an upper case
    cmpb $90, (%r8) # ?: pstr[i] <= 90
    jb .swapCase_isUpperCase
    # check if in the range between upper and lower case
    cmpb $97, (%r8) # ?: pstr[i] < 97
    jb .swapCase_nextChar
    # check if a lower case
    cmpb $122, (%r8)
    jb .swapCase_isLowerCase

.swapCase_nextChar:
    decq %r8 # pstr--
    # check if we reached the begining
    cmpq %rdi, %r8
    jl .swapCase_checkChar # if it not less we haven't finished - go back to the loop
    # set the return value
    movq %rdi, %rax
    ret
.swapCase_isUpperCase:
    # add '32' to the value - the difference between the ASCII value of upper and lower case is 32
    add $32, (%r8)
    # go next char
    jmp .swapCase_nextChar
.swapCase_isLowerCase:
    # subtract '32' to the value - the difference between the ASCII value of upper and lower case is 32
    sub $32, (%r9)
    # go next char
    jmp .swapCase_nextChar

    .global pstrijcmp
    .type pstrijcmp, @function
pstrijcmp: # %rdi - pstr1, %rsi - pstr2, %rdx - i, %rcx - j
    # check for valid indexes
    # test for i < pstr1.length
    cmpb (%rdi), %dl
    ja .pstrijcmp_invalidInput    # if not - invalid input
    # test for j < pstr1.length
    cmpb (%rdi),    %cl
    ja .pstrijcmp_invalidInput    # if not - invalid input
    # test for i < pstr2.length
    cmpb (%rsi),    %dl
    ja .pstrijcmp_invalidInput    # if not - invalid input
    # test for j < pstr2.length
    cmpb (%rsi),    %cl
    ja .pstrijcmp_invalidInput    # if not - invalid input
.pstrijcmp_loop:
    # creating pointers to the right sections of each pstr
    leaq (%rdi, %rdx),  %r8 # pstr1 + i
    leaq (%rdi, %rcx),  %r9 # pstr1 + j
    leaq (%rsi, %rdx),  %r10 # pstr2 + i
    # comapre the pstr1[i] to pstr2[i]
    movb    (%r8), %r11b    # can't access memory to memory 
    cmpb    %r11b, (%r10)   
    ja    .pstrijcmp_pstr2isBigger
    jb    .pstrijcmp_pstr1isBigger
    incq    %r8    # pstr1[i++]
    incq    %r10    # pstr2[i++]
    # check if the address of the pstr[i] != pstr[j]
    cmpq    %r8, %r9
    jle    .pstrijcmp_loop # haven't reached the end of the range
    # In the case the ranges are equal
    movq    $0, %rax
    ret

.pstrijcmp_pstr1isBigger:
    movq    $1, %rax
    ret

.pstrijcmp_pstr2isBigger:
    movq    $-1, %rax
    ret

.pstrijcmp_invalidInput:
    pushq    %rdi
    movq    $format_invalidInput, %rdi    # pass proper format for printf
    xorq    %rax, %rax    # set %rax to 0
    call    printf
    popq    %rdi
    ret
