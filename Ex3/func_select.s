#318175197 Idan Ziv by me
.section    .rodata
    .align 8
#cases for switch case
.JUMP_TABLE:
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

#literals for pstr.h functions
msg_pstrlen:     .string "first pstring length: %d,second pstring length: %d\n"
msg_replaceChar:    .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
format_pstr_info:   .string "lenght: %d, string: %s\n"
msg_pstrijcmp:  .string "comapre result: %d\n"
msg_default_case:   .string "invalid option\n"
#literals for scanf, printf
format_int:     .string: "%d"
format_char:    .string: "%c"
format_str:     .string: "%s"

    .text
.global run_func
.type run_func, @function
run_func: #the case number is in %rdi
    #setting the stack acess to the jump tables
    leaq -50(%rdi), %rbx #setting the choice to match the range
    cmpq $10, %rbx #check if the choice is in range
    ja .f_default #if the number is not in range we ha
    jmp *.JUMP_TABLE(,%rsi,8)