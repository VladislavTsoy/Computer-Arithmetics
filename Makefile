all: calc format

calc: calc.c
	gcc -o calc calc.c 

format: format.c
	gcc -o format format.c

clean: 
	rm -rf *.o calc format
