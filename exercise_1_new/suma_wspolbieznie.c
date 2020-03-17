#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <time.h>
#include "err.h"
#define BUFFOR_SIZE 80

void catch_usr1( int signal ) {
	printf( "PID dziecka jest rowny: %d. Otrzymalem sygnal USR1, rozpoczynam obliczenia.\n", getpid() );
}



double sum(double* vector, int n) {
	int i;
	double sum = 0.0f;
	for(i=0; i<n; i++) {
		sum += vector[0];
		vector += sizeof( double );
	}
	return sum;
}

void wypiszTab( double* vector, int n ) {
	int i;
	printf("v = [ ");
	for(i=0; i<n; i++) {
		printf("%f ", vector[0]);
		vector += sizeof( double );
	}
	printf("]\n");
}
int main ( int argc, char **argv )
{
	/* do pomiaru czsu wykonywania sie programu */
	clock_t start;
	start = clock();

	pid_t pid;
	int lprocesow, i, rangeid, resultid, vectorid;
	int *rangeaddr;
	double *resultaddr, *vectoraddr;
	key_t rangekey, resultkey, vectorkey;
	rangekey = 456789;
	resultkey = 123456;
	vectorkey = 456123;



	/* liczba procesow potomnych */
	lprocesow = 4;
	if ( argc > 1 ) 
		if ( atoi( argv[1] ) > 0 )
			lprocesow = atoi( argv[1] );
	
	printf( "Liczba procesow potomnych, ktore utworze: %d\n", lprocesow );

	/* tablica do zapisu pid dzieci */
	int dzieci[lprocesow]; 

	/* wypisuje identyfikator procesu */
		printf("Moj PID = %d\n", getpid());

	/* wczytanie wektora z pliku w wpisanie do pamieci wspoldzielonej */
	FILE* f = fopen("vector.dat", "r");
 	char buffor[BUFFOR_SIZE+1];
	int n;
	fgets(buffor, BUFFOR_SIZE, f);
 	n = atoi(buffor);
	printf("Vector has %d elements\n", n);

	/* tworzenie przestrzeni pamieci wspoldzielonej na vector */
	if ( ( vectorid = shmget ( vectorkey, n * sizeof( double ), 0666|IPC_CREAT) ) == -1 )  /* Stworzenie segementu */
		syserr ("blad");  
	if ( ( vectoraddr = shmat( vectorid, 0, 0 ) ) < 0 ) /* Przyłączenie */
		syserr ("blad");

	double *sdouble;	
	for(i=0; i<n; i++) {
		fgets(buffor, BUFFOR_SIZE, f);
		sdouble = (double*) vectoraddr + i * sizeof( double );
		*sdouble = (double) atof(buffor);
	}
	fclose(f);

	/* tworzy nowe procesy */
	for( i = 0; i < lprocesow; i++ ) {
		pid = fork();
		if ( pid == -1 ) {
			syserr( "Error in fork\n" );
		} else if ( pid == 0 ) { 
			/* proces potomny */

			/* konfiguarcja obslugi sygnalu SIGUSR1 */

			struct sigaction usr1;
			sigset_t maska;
			sigemptyset (&maska);
			usr1.sa_handler = catch_usr1;
			usr1.sa_mask = maska;
			usr1.sa_flags = 0;
			sigaction(SIGUSR1, &usr1, NULL);

			/* czeka na sygnal */
			pause();

			/* podlaczenie do range i result */
			if ( ( rangeid = shmget ( rangekey, lprocesow * 2 * sizeof( int ), 0666|IPC_CREAT) ) == -1 )
				syserr ("blad range get");  
			if ( ( rangeaddr = shmat( rangeid, 0, 0 ) ) < 0 )
				syserr ("blad range at");
			if ( ( resultid = shmget ( resultkey, lprocesow * sizeof( double ), 0666|IPC_CREAT) ) == -1 )
				syserr ("blad result get");  
			if ( ( resultaddr = shmat( resultid, 0, 0 ) ) < 0 )
				syserr ("blad result at");

			/* wczytnie wartosci z range */
			int pocz, kon, n;	/* pocztek i koniec zakresu, wielkosc podwektora */
			int *sint;
			double *svector, *sresult;
			sint = (int*) rangeaddr + i * sizeof( int );
			pocz = *sint;
			sint += sizeof( int );
			kon = *sint;
			n = kon - pocz;
			printf( "Podwektor %d ma %d elements\n", i + 1, n );
			sleep(1);

			svector = (double*) vectoraddr + pocz * sizeof( double );

			wypiszTab( svector, n );		/* do testowania czy dobre podwektory przypisuje */

			/* sumowanie i zapisanie wartosci w result */
			sresult = (double*) resultaddr + i * sizeof( double );
			for ( int i = 0; i <50000000/lprocesow; i++) { //////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				getpid();
				*sresult = sum( svector, n );
			}
			printf( "Podwektor %d sum = %g\n", i + 1, *sresult );

			return 0;
		} else { 
			/* proces macierzysty */
			/* zapisuje pid nowego dziecka */
			dzieci[i] = pid;
		}	
	}
	sleep(1);


	/* tworzenie przestrzeni pamieci wspoldzielonej na range */
	if ( ( rangeid = shmget ( rangekey, lprocesow * 2 * sizeof( int ), 0666|IPC_CREAT) ) == -1 )  /* Stworzenie segementu */
		syserr ("blad");  
	if ( ( rangeaddr = shmat( rangeid, 0, 0 ) ) < 0 ) /* Przyłączenie */
		syserr ("blad");

	/* przypisanie wartosci range */
	int *sint;
	for ( i = 0; i < lprocesow; i++ ) {
		sint = rangeaddr + i * sizeof( int );
		*sint = n / lprocesow * i;
		sint += sizeof( int );
		if( i == lprocesow - 1 )
			*sint = n;
		else
			*sint = n / lprocesow * ( i + 1 );
	}

	/* tworzenie przestrzeni pamieci wspoldzielonej na result */
	if ( ( resultid = shmget ( resultkey, lprocesow * sizeof( double ), 0666|IPC_CREAT) ) == -1 )  /* Stworzenie segementu */
		syserr ("blad");  
	if ( ( resultaddr = shmat( resultid, 0, 0 ) ) < 0 ) /* Przyłączenie */
		syserr ("blad");

	/* wyslanie dzieciom wygnalu o gotowych danych */
	for ( i = 0; i < lprocesow; i++ )
		kill( dzieci[i], SIGUSR1 );
	
	/* czekanie na koniec dzialania dzieci */
	for ( i = 0; i < lprocesow; i++ ) 
		if( pid != 0 && wait(0) == -1)
			syserr( "Error in wait\n" );

	/* zwolnienie pamieci wspoldzielonej range */
	if( shmctl( rangeid, IPC_RMID, 0 ) < 0 )
		syserr("range shmctl error");
	printf("Wspolna pamiec for range removed\n");

	/* zwolnienie pamieci wspoldzielonej wektora */
	if( shmctl( vectorid, IPC_RMID, 0 ) < 0 )
		syserr("vector shmctl error");
	printf("Wspolna pamiec for vector removed\n");

	printf( "Sum of elements in vector = %g\n", sum( resultaddr, lprocesow ) );

	/* zwolnienie pamieci wspoldzielonej result */
	if( shmctl( resultid, IPC_RMID, 0 ) < 0 )
		syserr("result shmctl error");

	printf("Wspolna pamiec for result removed\n");

			// printf( "Czas wykonania programu: %f s \n", (double)( clock() - start ) / CLOCKS_PER_SEC );
	return 0;
}
