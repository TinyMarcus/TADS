CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g6
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

app.exe : main.o graph.o
	$(CC) -o app.exe main.o graph.o

main.o : main.c graph.h
	$(CC) $(FLAGS) -c main.c

graph.o : graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

clean :
	rm *.exe *.o
