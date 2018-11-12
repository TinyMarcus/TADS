CC := gcc
CFLAGS := -std=c99 -Wall -Werror -ggdb

app.exe : main.o read_write_file.o actions.o sorts.o
	$(CC) -o $@ $^
	
main.o : main.c structure.h read_write_file.h actions.h sorts.h
	$(CC) $(CFLAGS) -c $<
	
read_write_file.o : read_write_file.c read_write_file.h structure.h actions.h sorts.h
	$(CC) $(CFLAGS) -c $<
	
%.o : %.c %.h structure.h
	$(CC) $(CFLAGS) -c $<
	
clean :
	$(RM) *.o *.exe
