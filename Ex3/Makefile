a.out: main.o run_main.o func_select.o pstring.o
	gcc -g -no-pie -o a.out main.o run_main.o func_select.o pstring.o
main.o: main.c pstring.h
	gcc -g -no-pie -c -o main.o main.c

run_main.o: run_main.s pstring.h
	gcc -g -no-pie -c -o run_main.o run_main.s

func_select.o: func_select.s pstring.h
	gcc -g -no-pie -c -o func_select.o func_select.s

pstring.o: pstring.s
	gcc -g -no-pie -c -o pstring.o pstring.s

tests:
	gcc -g -no-pie main.c run_main.s func_select.s pstring.s
	chmod +x tests.sh
	./tests.sh

clean:
	rm -rf *.o a.out
	rm dump.txt
dump:
	objdump -d a.out > dump.txt
