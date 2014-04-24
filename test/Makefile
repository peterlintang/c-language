
all:
	gcc -o my main.c -ldl
	gcc -o a.so test.c -shared
	gcc -o array array.c

clean:
	rm -rf my a.so array
