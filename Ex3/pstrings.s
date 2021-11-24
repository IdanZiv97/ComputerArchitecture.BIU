#318175197 Idan Ziv
.section .rodata
    .allign 8
    format_invalidInput: .string "invalid input!\n"
    .text
    .global pstrlen
    .type pstrlen, @function
pstrlen: #the pstring address is saved on %rdi
    movq (%rdi), %rax #the length of the pstring is the on the first address of the pstring
    ret

    .global replaceChar
    .type replaceChar, @function
pstrlen: # %rdi- pointer to pstring, %sil oldChar, 
