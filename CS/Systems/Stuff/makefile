all: server client

server: server.o game.o
	gcc -o server server.o game.o

server.o: server.c shared.h
	gcc -c server.c

game.o: game.c game.h shared.h
	gcc -c game.c

client: client.c
	gcc -o client client.c

clean:
	rm *.o
	rm *~
	rm *#

cleaner:
	rm server
	rm client