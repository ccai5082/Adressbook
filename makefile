run:main.o tongxunlu.o
	gcc main.o tongxunlu.o -o run
main.o:main.c
	gcc -c main.c -o main.o
tongxunlu.o:tongxunlu.c
	gcc -c tongxunlu.c -o tongxunlu.o
clean:
	rm *.o *.txt run