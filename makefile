all: main

main: graph.o main.c
	gcc main.c graph.o -o main -std=c99 -Wall -lm

graph.o: graph.c graph.h
	gcc -c graph.c -o graph.o

run: all
	./main

clean:
	rm -f *.o main

memory: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
