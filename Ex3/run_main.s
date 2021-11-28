	# 207631466 Yanir Buznah

# Tests used, 'tests.sh' by Ron Even and me

    .section .rodata

    .align 8



format_scan_d:    .string "%d"

format_scan_s:   .string "%s"

	.text

	.globl	main

	.type	main, @function

main:

pushq   	%rbp

movq    	%rsp ,%rbp              # init new stack fergment


subq    	$528, %rsp              # init 528 bytes in the stack for the next varibales. (to allign the stack by 16)



movq  		$format_scan_d, %rdi      # init the format of the input and save in rdi

leaq  		-528(%rbp), %rsi          # change the rsi to the pointer of -528(%rbp)

movq  		$0, %rax

call  		scanf                     # scan the length of the first string



movq  		$format_scan_s, %rdi      # init the format of the input and save in rdi

leaq  		-527(%rbp), %rsi          # change the rsi to the pointer of -527(%rbp)

movq  		$0, %rax

call  		scanf                     # scan the first string (max size: 255)



movq  		$format_scan_d, %rdi      # init the format of the input and save in rdi

leaq  		-272(%rbp), %rsi          # change the rsi to the pointer of -272(%rbp)

movq  		$0, %rax

call  		scanf                     # scan the length of the second string



movq  		$format_scan_s, %rdi      # init the format of the input and save in rdi

leaq  		-271(%rbp), %rsi          # change the rsi to the pointer of -271(%rbp)

movq  		$0, %rax

call  		scanf                     # scan the second string (max size: 255)



movq  		$format_scan_d, %rdi      # init the format of the input and save in rdi

leaq  		-16(%rbp), %rsi           # change the rsi to the pointer of -16(%rbp)

movq  		$0, %rax

call  		scanf                     # scan the choise from the user (opt in run_main.c)



xorq    	%rdi,%rdi               # reset rdi (delete garbage from the 4 msb before using rdi)

movl    	-16(%rbp),%edi          # move the 4 bytes from the scanf to rdi (the format is %d so its just 4 bytes)

leaq    	-528(%rbp), %rsi        # save the first pstring to rsi

leaq    	-272(%rbp), %rdx        # save the second pstring to rdx

# call    	run_func





movq   		%rbp ,%rsp               # free the stack segment

popq   		%rbp



ret

