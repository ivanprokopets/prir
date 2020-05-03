CC=mpicc #gcc
CFLAGS=-lmpi
RUN=mpirun -np 2
fscount: finish.c
	${CC} finish.c -g -o mapreduce ${CFLAGS}
run: mapreduce
	${RUN} ./mapreduce

