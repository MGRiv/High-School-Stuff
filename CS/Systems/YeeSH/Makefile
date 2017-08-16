run: build
	./YeeSH

build: main.o parser.o execute.o
	gcc -o YeeSH main.o parser.o execute.o

main.o: main.c parser.o execute.o
	gcc -c main.c parser.o execute.o

parser.o: parser.c
	gcc -c parser.c

execute.o: execute.c
	gcc -c execute.c

clean:
	rm *.o
	rm output*
	rm YeeSH
