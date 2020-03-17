all: matrix_mul.c
	cc -pthread -o matrix_mul matrix_mul.c -lm

clean:
	$(RM) matrix_mul.c

run: matrix_mul
	./matrix_mul

