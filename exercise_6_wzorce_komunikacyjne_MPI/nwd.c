#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#include<unistd.h>


int NWD(int a, int b){
	int tmp;
	while(b != 0){
		tmp = b;
		b = a%b;
		a = tmp;
	}
	return a;
}

void wypisz(int liczba_proc, int liczby[], int liczba){
	printf("NWD dla liczb\n");
	int i;
	for (i=0; i<liczba_proc; i++){
		printf("%d\n", liczby[i]);
		}
	printf("Wynosi : %d\n",liczba);
}

int main(int argc, char **argv){

	int i, numer_procesu, liczba_procesow, liczba, otrzymany;
	MPI_Init(NULL, NULL); //inicjalizacja MPI
	MPI_Comm_size(MPI_COMM_WORLD, &liczba_procesow); //ustalenie liczby procesów
	MPI_Comm_rank(MPI_COMM_WORLD, &numer_procesu); //nadanie numerów procesom
	double logarytm = log2(liczba_procesow);
	if((logarytm - (int)logarytm) != 0){
		printf("Liczba procesow musi byc potega 2\n");
		MPI_Finalize();
		return (EXIT_FAILURE);
	}
	//czytanie liczb do liczenia NWD z argumentow
	int liczby[liczba_procesow];
	for(i=1; i<liczba_procesow+1; i++){
                liczby[i-1] = atoi(argv[i]);
        }
	liczba = liczby[numer_procesu]; //przydzielenie liczb do procesow
	int ile = log2(liczba_procesow);

	if (argc-1 != liczba_procesow) {
        if (numer_procesu == 0)
            printf("Liczba argumentów nie odpowiada liczbie procesów.\n"
                   "Oczekiwane %d, Otrzymane %d\n", liczba_procesow, argc-1);
        return -1;
    }
	for (int i = 0; i < argc-1; i++) {
        int liczby = atoi(argv[i+1]);
        if (liczby <= 0) {
            if (numer_procesu == 0)
                printf("Numer argumentu %d nie jest poprawny. Musi byc dodatni.\n", i+1);
            return -1;
        }
    }
	for(i = 1; i <= ile; i++){
		int przesuniecie = pow(2,(i-1));
		if(numer_procesu + przesuniecie < liczba_procesow){
			MPI_Send(&liczba, 1, MPI_INT, numer_procesu + przesuniecie, 0, MPI_COMM_WORLD); //wysylanie liczb
		}
		else{
			MPI_Send(&liczba, 1, MPI_INT, numer_procesu + przesuniecie - liczba_procesow, 0, MPI_COMM_WORLD); 	//wysylanie liczb	
		}
		if(numer_procesu - przesuniecie >= 0){
			MPI_Recv(&otrzymany, 1, MPI_INT, numer_procesu - przesuniecie, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //odbior liczb
		}
		else{
			MPI_Recv(&otrzymany, 1, MPI_INT, numer_procesu - przesuniecie + liczba_procesow, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); //odbior liczb
		}
		liczba=NWD(liczba,otrzymany);
		printf("Jestem %d, przesuniecie: %d,  moje NWD(%d,%d) = %d\n", numer_procesu, przesuniecie, liczba, otrzymany, NWD(liczba, otrzymany));		
	}
	usleep(50000);
	if(numer_procesu == 0){
		wypisz(liczba_procesow, liczby,liczba);
	}
	MPI_Finalize(); //czyszczenie procesów
	return 0;
}

