run_all: run_regular run_o0 run_o1 run_o2 run_o3

run_regular:
			gcc -g MyEx.c -o MyEx.out && objdump -d MyEx.out > regular.txt
run_o0: 
		gcc -g -O0 MyEx.c -o o0_opt.out && objdump -d o0_opt.out > o0_opt.txt
run_o1: 
		gcc -g -O1 MyEx.c -o o1_opt.out && objdump -d o1_opt.out > o1_opt.txt
run_o2:
		gcc -g -O2 MyEx.c -o o2_opt.out && objdump -d o2_opt.out > o2_opt.txt
run_o3:
		gcc -g -O3 MyEx.c -o o3_opt.out && objdump -d o3_opt.out > o3_opt.txt

clear:
		rm *.out
		rm *.txt
		rm -rf *.dSYM/