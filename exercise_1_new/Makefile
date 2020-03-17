all: err.o suma_wspolbieznie.o
	$(CC) suma_wspolbieznie.o err.o -o suma_wspolbieznie

	$(CC) add.c -o add
	
	$(CC) losuj.c -o losuj

suma_wspolbieznie.o: suma_wspolbieznie.c
	$(CC) suma_wspolbieznie.c -c -o suma_wspolbieznie.o

err.o: err.c
	$(CC) err.c -c -o err.o

clean:
	rm -f *.o
