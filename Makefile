
output: nea.o
	@gcc nea.o -Wall -ansi -pedantic-errors -o out

main.o: nea.c
	@gcc -c nea.c

clean:
	rm *.o out
