#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

double **A;
double **B;
double **C;

double *sums;
double *square_sums;

struct v
{
    int na;
    int mb;
    int nb;
    int lenA;
    int *rowsA;
    int thread_id;
};

static void *multiplication(void *arg)
{
    struct v *data = (struct v *)arg;
    int i, j, k;
    double sum;

    for (i = 0; i < data->lenA; i++)
    {
        for (j = 0; j < data->nb; j++)
        {
            sum = 0.0;
            for (k = 0; k < data->na; k++)
            {
                sum += A[data->rowsA[i]][k] * B[k][j];
            }
            C[data->rowsA[i]][j] = sum;
            sums[data->thread_id] += sum;
            square_sums[data->thread_id] += sum * sum;
        }
    }
}

void print_matrix(double **A, int m, int n)
{
    int i, j;
    printf("[\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }
    printf("]\n");
}

int main(int argc, char **argv)
{
    static struct timeval tm1;
    gettimeofday(&tm1, NULL);
    int N;
    if (argc > 1)
    {
        N = atoi(argv[1]);
    }
    else
    {
        N = 2;
    }
    printf("Ilosc N watkow potomnych:%d\n", N);
    FILE *fpa;
    FILE *fpb;

    int ma, mb, na, nb;
    int i, j;
    double x;

    fpa = fopen("A.txt", "r");
    fpb = fopen("B.txt", "r");
    if (fpa == NULL || fpb == NULL)
    {
        perror("błąd otwarcia pliku");
        exit(-10);
    }

    fscanf(fpa, "%d", &ma);
    fscanf(fpa, "%d", &na);

    fscanf(fpb, "%d", &mb);
    fscanf(fpb, "%d", &nb);

    printf("pierwsza macierz ma wymiar %d x %d, a druga %d x %d\n", ma, na, mb, nb);

    if (na != mb)
    {
        printf("Złe wymiary macierzy!\n");
        return EXIT_FAILURE;
    }

    A = malloc(ma * sizeof(double));
    for (i = 0; i < ma; i++)
    {
        A[i] = malloc(na * sizeof(double));
    }

    B = malloc(mb * sizeof(double));
    for (i = 0; i < mb; i++)
    {
        B[i] = malloc(nb * sizeof(double));
    }

    C = malloc(ma * sizeof(double));
    for (i = 0; i < ma; i++)
    {
        C[i] = malloc(nb * sizeof(double));
    }

    printf("Rozmiar C: %dx%d\n", ma, nb);
    for (i = 0; i < ma; i++)
    {
        for (j = 0; j < na; j++)
        {
            fscanf(fpa, "%lf", &x);
            A[i][j] = x;
        }
    }

    printf("A:\n");
    print_matrix(A, ma, mb);

    for (i = 0; i < mb; i++)
    {
        for (j = 0; j < nb; j++)
        {
            fscanf(fpb, "%lf", &x);
            B[i][j] = x;
        }
    }

    printf("B:\n");
    print_matrix(B, mb, nb);

    sums = malloc(N * sizeof(double));
    square_sums = malloc(N * sizeof(double));

    if (N > ma)
        N = ma;

    pthread_t *threads = malloc(N * sizeof(pthread_t));
    size_t col, row;

    struct v **data;
    data = (struct v **)malloc(N * sizeof(struct v *));
    int t, q;
    for (t = 0; t < N; t++)
    { 
        data[t] = (struct v *)malloc(sizeof(struct v *));
        data[t]->rowsA = malloc(ma * sizeof(int));
        int counter = 0;
        for (q = t; q < ma; q += N)
        {
            data[t]->rowsA[counter] = q;
            counter++;
        }
        data[t]->lenA = counter;
        data[t]->na = na;
        data[t]->mb = mb;
        data[t]->nb = nb;
        data[t]->thread_id = t;        
        pthread_create(&threads[t], NULL, multiplication, data[t]);
    }

    double suma_sum = 0.0;
    double suma_frobenius_sum = 0.0;
    for (t = 0; t < N; t++)
    {
        pthread_join(threads[t], NULL);
        suma_sum += sums[t];
        suma_frobenius_sum += square_sums[t];
    }
    suma_frobenius_sum = sqrt(suma_frobenius_sum);

    printf("Wynik mnozenia C = A * B:\n");
    print_matrix(C, ma, nb);
    printf("Suma sum = %lf\n", suma_sum);
    printf("Norma Forbeniusa = %lf\n", suma_frobenius_sum);

    for (i = 0; i < na; i++)
    {
        free(A[i]);
    }
    free(A);

    for (i = 0; i < nb; i++)
    {
        free(B[i]);
    }
    free(B);

    for (i = 0; i < nb; i++)
    {
        free(C[i]);
    }
    free(C);

    free(sums);
    free(square_sums);
    free(threads);
    free(data);
    fclose(fpa);
    fclose(fpb);

    struct timeval tm2;
    gettimeofday(&tm2, NULL);
    unsigned long long time = 1000 * (tm2.tv_sec - tm1.tv_sec) + (tm2.tv_usec - tm1.tv_usec)/1000;
    printf("Execution time: %llu ms\n", time);
    return 0;
}
