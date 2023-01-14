CC = gcc
FLAGS = -Wall -g

all: graph

graph: main.o libgrp.a
	$(CC) $(FLAGS) main.o  libgrp.a -o graph

libgrp.a:  nodes.o edges.o algo.o
	ar -rcs libgrp.a nodes.o edges.o algo.o
	
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

nodes.o: nodes.c graph.h
	$(CC) $(FLAGS) -c nodes.c 

edges.o: edges.c graph.h
	$(CC) $(FLAGS) -c edges.c

algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c

.phony: clean all	

clean: 
	rm -f *.o *.a graph

leakTest: clean graph
	valgrind --leak-check=full  --track-origins=yes --show-leak-kinds=all --error-exitcode=1 ./connections