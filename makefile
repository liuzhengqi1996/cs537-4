malloc537.o: malloc537.c malloc537.h avltree.o
	gcc -g -Wall -pedantic -o malloc537.o malloc537.c avltree.o
avltree.o: avltree.c avltree.h
	gcc -g -Wall -pedantic avltree.c
