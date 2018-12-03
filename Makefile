CC=gcc
SCAN_BUILD_DIR = scan-build-out
EXE=output

all: main.o malloc537.o avltree.o
	$(CC) -o $(EXE) main.o malloc537.o avltree.o

# main.c is your testcase file name
main.o: main.c
	$(CC) -Wall -Wextra -c main.c

# Include all your .o files in the below rule
obj: malloc537.o avltree.o

malloc537.o: malloc537.c malloc537.h avltree.h
	$(CC) -Wall -Wextra -g -O0 -c malloc537.c

avltree.o: avltree.c avltree.h
	$(CC) -Wall -Wextra -g -O0 -c avltree.c

clean:
	-rm *.o $(EXE)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
