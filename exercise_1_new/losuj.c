#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double losuj(int min, int max)
{
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ? (rand() % max + min) : min;
}



int main ( int argc, char **argv ) {
	if( argc > 1 ) {

	int i, n, zarodek;
	FILE* f = fopen( argv[1], "w" );
	n = atoi( argv[2] );
	zarodek = time(NULL);

	if ( f == NULL ) {
		printf( "Nie udalo sie utworzyc pliku." );
		return -1;
	}
	
	fprintf( f, "%d\n", n );
	for( i = 0; i < n; i++ ) {
		srand( zarodek / (i + 1) );
		fprintf( f, "%g\n", losuj( 0, 10000 ) / 100 );
	}
	
	return 0;
	} else {
		printf( "Program losuje liczby double 0-100 i zapisuje do pliku.\nPierwszy argument - sciezka do pliku.\nDrugi argument - ile liczb\n" );
		return -1;
	}
}
