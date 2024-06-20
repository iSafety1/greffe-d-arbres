CFLAGS = -Wall -Werror
CC = gcc

main : main.o greffe.o saage.o arbres_binaires.o
	$(CC) $(CFLAGS) -o main main.o

main.o : main.c greffe.h saage.h arbres_binaires.h
	$(CC) $(CFLAGS) -c main.c

greffe.o : greffe.c greffe.h
	$(CC) $(CFLAGS) -c greffe.c

saage.o : saage.c saage.h
	$(CC) $(CFLAGS) -c saage.c

arbres_binaires.o : arbres_binaires.c arbres_binaires.h
	$(CC) $(CFLAGS) -c arbres_binaires.c

clean :
	rm -f *.o main
