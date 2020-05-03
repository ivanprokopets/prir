// mpicc zad.c
// mpiexec -n 4 ./a.out -100 100 1000
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define LEFT 0
#define RIGHT 1
#define STEP 1000
#define THOUSANDS 100

int main(int argc, char **argv)
{
    static struct timeval tm1;
    struct timeval tm2;
    
    gettimeofday(&tm1, NULL);
    int numtasks, rank, source, dest, tag = 1;
    int inbuf[1000];
    int outbuf[1000];
    int all_data[100000];
    int nbrs[2], dims[1], periods[1] = {0}, reorder = 0, coords[2];

    MPI_Comm cartcomm;
    MPI_Request reqs[2];
    MPI_Status stats[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    dims[0] = numtasks;

    MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periods, reorder, &cartcomm);
    MPI_Comm_rank(cartcomm, &rank);
    MPI_Cart_coords(cartcomm, rank, 1, coords);
    MPI_Cart_shift(cartcomm, 0, 1, &nbrs[LEFT], &nbrs[RIGHT]);

    dest = nbrs[RIGHT];
    source = nbrs[LEFT];

    if (rank == 0)
    {
        for (int i = 0; i < THOUSANDS * STEP; i++)
            outbuf[i] = i;
        for (int i = 0; i < THOUSANDS; i++)
        {
            MPI_Isend(&outbuf[i * STEP], STEP, MPI_INT, dest, tag,
                      MPI_COMM_WORLD, &reqs[1]);
            MPI_Wait(&reqs[1], &stats[1]);
        }
    }
    else
    {

        for (int i = 0; i < THOUSANDS; i++)
        {
            MPI_Irecv(inbuf, STEP, MPI_INT, source, tag,
                      MPI_COMM_WORLD, &reqs[0]);
            MPI_Wait(&reqs[0], &stats[0]);

            for (int j = 0; j < STEP; j++)
                all_data[i * STEP + j] = inbuf[j];

            MPI_Isend(inbuf, STEP, MPI_INT, dest, tag,
                      MPI_COMM_WORLD, &reqs[1]);
            MPI_Wait(&reqs[1], &stats[1]);
        }
    }

    if (rank == numtasks - 1)
    {
        long sum = 0;
        for (int i = 0; i < STEP * THOUSANDS; i++)
        {
            sum += all_data[i];
        }
        gettimeofday(&tm2, NULL);
        unsigned long long time = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec) / 1000;
        printf("Suma wszystkich elementow w procesie %d wynosi %ld \n", rank, sum);
        printf("Czas wykonania się aplikacji dla liczby procesów równej %d wynosi %lld ms \n", numtasks, time);
    }

    MPI_Finalize();
}
