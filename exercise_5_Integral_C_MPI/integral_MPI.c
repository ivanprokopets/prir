#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double function(double x) {
	return x*x;
}


double integrate(double (*func)(double), double begin, double end, int num_points) {
	double result = 0.0;
	double i = 0.0;
	for(i = begin; i < end; i += (end - begin )/ num_points) {
		result += func(i) * (end - begin) / num_points;
	}
	return result;
}


int main(int argc, char** argv) {
	//Initialize the MPI environment
	MPI_Init(&argc,	&argv);
	// Find out rank, size
	int my_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	int p;
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	float begin = atof(argv[1]);
	float end = atof(argv[2]);
	int N = atoi(argv[3]);

	float my_range = (end - begin) / p;
  	int num = N/p;
	int reszta = N % p;
	int add = reszta - my_id > 0 ? 1 : 0;
	num = num + add;
	float h = (end - begin) / N;
	float my_begin = begin + my_id*my_range;
	float my_end = my_begin + my_range;
	
	float my_result = integrate(function, my_begin, my_end, num);
	printf("Process %d - result: %f (num_steps: %d -> step_len: %.16f, begin: %f, end: %f)\n", my_id, my_result, num, h, my_begin, my_end);

	if(my_id == 0) {
		float sum = my_result;
		int i = 0;
		for(i = 1; i < p; i++) {
			MPI_Recv(&my_result, 1, MPI_REAL, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += my_result;
		}
		printf("\nWynik: %f\n", sum);
		
	} else {
		MPI_Send(&my_result, 1, MPI_REAL, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
} 

