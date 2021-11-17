#318175197 Idan Ziv
    .text
    .section    .rodata
    .text
    .globl go, even
even: #num in %rdx, i in %rsi
    movl %edi, %eax #Moving 'num' to %rax - return value
    movl %esi, %ecx #Moving 'i' to %rcx - to perform arithmic operations
    sall %cl, %eax #left arhitmic shift 
    ret
go: #The array is in %rdi?
    #intilizing sum in %r10 , i in %rbx
    movl $0, %r10d #later on we will move it into %rax
    movl $0, %ebx
    movq %rdi, %r9 #moving the array start adress
    jmp .TEST
.TEST:
    cmpq $10, %rbx #test i<10 i-10
    jl .LOOP
    movq %r10, %rax
    ret
.LOOP:
    #load the A[i] to 
    movq (%r9, %rbx, 4), %rax
    movl $2, %r8d
    cqto #signed padding the value in %rax to %rdx
    idivl %r8d  # %rax:%rdx : 2 
    testq %rdx, %rdx #check if the the reminder is zero
    jne .ELSE #if not zero perfom else
    #moving the variables to even
    movq (%r9, %rbx, 4), %rdi #sending 'num' paraemeter for even.
    movq %rbx, %rsi #seing 'i' parameter for even.
    call even
    add  %rax, %r10 # sum += return value from even
    incq %rbx #increment i
    jmp .TEST
.ELSE:
    #sum is in %r10, the start of the array is in %r9
    add (%r9, %rbx, 4), %r10
    incl %ebx
    jmp .TEST
