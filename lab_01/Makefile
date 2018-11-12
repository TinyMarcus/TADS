CC := gcc
FLAGS := -std=c99 -pedantic -Wall -Werror

OBJS := main.o mult.o output.o input.o

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

ifeq ($(mode), debug)
	FLAGS += -g3
endif

app.exe : main.o $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o : %.c *.h
	$(CC) $(FLAGS) -c $<

clean :
	$(RM) *.o *.exe