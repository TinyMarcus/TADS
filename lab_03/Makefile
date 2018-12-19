CC := gcc
CFLAGS := -std=c99 -Wall -Werror

app.exe : main.o create.o comparison.o free.o matrix_operations.o print.o read.o
	$(CC) -o $@ $^

%.o : %.c *.h
	gcc -c $< -std=c99

clean :
	$(RM) *.o *.exe
