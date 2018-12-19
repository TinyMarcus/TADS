CC := gcc

CFLAGS := -std=c99 -g3

OFILES := arrstack.o interface.o liststack.o analisis.o
	
	
main.exe : main.o $(OFILES)
	$(CC) -o main.exe main.o $(OFILES)
	
main.o : main.c arrstack.h interface.h liststack.h analisis.h
	$(CC) $(CFLAGS) -c main.c
	
arrstack.o : arrstack.c arrstack.h
	$(CC) $(CFLAGS) -c arrstack.c
	
liststack.o : liststack.c liststack.h
	$(CC) $(CFLAGS) -c liststack.c
	
interface.o : interface.c interface.h
	$(CC) $(CFLAGS) -c interface.c
	
analisis.o : analisis.c analisis.h
	$(CC) $(CFLAGS) -c analisis.c
	
clean :
	rm *.o *.exe
