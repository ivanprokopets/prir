all: nwd.c
	mpicc -o nwd nwd.c -lm

clean:
	$(RM) *.o

run: nwd.c
	mpiexec -n 4 nwd 10 15 20 25
