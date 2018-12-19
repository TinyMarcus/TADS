CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

app.exe : main.o comparison.o queue_arr.o queue_list.o
	$(CC) -o $@ $^

%.o : %.c *.h
	gcc -c $< -std=c99

clean :
	$(RM) *.o *.exe

vlgr : app.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./app.exe
