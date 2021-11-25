#318175197 Idan Ziv
.section .rodata
    .allign 8
    format_invalidInput: .string "invalid input!\n"

    .text
    .global pstrlen
    .type pstrlen, @function
pstrlen: #the pstring address is saved on %rdi
    # There is no need to create a stack frame, since we are not using any local vars
    movq (%rdi), %rax #the length of the pstring is the on the first address of the pstring
    ret

    .global replaceChar
    .type replaceChar, @function
replaceChar: # %rdi- pointer to pstring, %rsi oldChar, %rdx - new char
    # save the old frame base pointer
    pushq %rbp
    movq %rsp, %rbp 

    # the function returns the pointer to the pstring
    movq %rdi, %rax # saving the pointer to the start of the pstring, this way we can manipulate it and still have a pointer
    addq $1, %rdi # the first byte of the struct is saved for the lenght, we want to start form the string itself
    # do while loop
.replaceChar_while:
    cmpb $0, (%rdi) # check if we reached '\0'
    je .end_replaceChar # pstr[i] == '\0' - reached the end of the string, end loop
    # we need to check if the char is valid
    cmpb (%rdi), %sil # check if pstr[i] == oldChar
    je .replaceChar_if
    addq %1, %rdi # pstr++
    jmp .replaceChar_while

.replaceChar_if:
    # we found the old char, we need to rewirte it with the new char
    movb %dl, (%rdi)
    addq $1, %rdi
    jmp .replaceChar_while

.end_replaceChar:
    # restore the stack pointers
    movq %rbp, %rsp
    pop %rbp
    ret

    .global pstrijcpy
    .type pstrijcpy, @function
pstrijcpy: # %rdi - dst, %rsi - src, %rdx -i, %rcx - j
    # save the old frame base pointer and, set new one
    pushq %rbp
    movq %rsp,      %rbp
    # Check for proper range
    # test for i < j && j,i != 0 ?
    # test for i < des.length
    cmpb (%rdi),    %dl
    ja pstrijcpy_invalidInput    # if not - invalid input
    # test for j < det.length
    cmpb (%rdi),    %cl
    ja pstrijcpy_invalidInput    # if not - invalid input
    # test for i < src.length
    cmpb (%rsi),    %dl
    ja pstrijcpy_invalidInput    # if not - invalid input
    # test for j < src.length
    cmpb (%rsi),    %cl
    ja pstrijcpy    # if not - invalid input
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
swapCase:
    





