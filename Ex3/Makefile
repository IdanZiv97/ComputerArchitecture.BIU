run1: clean
	gcc -ggdb -no-pie -o run1 pstrings.s func_select.s run_main.s

all: clean
	gcc -ggdb -no-pie -o func_select func_select.s

clean:
	rm -rf *.o run1
