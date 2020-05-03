# [Lab] Ćwiczenie 5 - MPI (całkowanie - C) 

## Tresc:  
Proszę policzyć przy pomocy metody prostokątów/trapezów/simpsona (możecie Państwo wybrać metodę) całkę oznaczoną funkcji jednej zmiennej. Procedura całkowania powinna przyjmować: wskaźnik na całkowaną funkcję, początek i koniec przedziału całkowania oraz liczbę punktów dla których obliczana jest wartość funkcji. Oto jej nagłówek:

` double integrate(double (*func)(double), double begin, double end, int num_points);`   
Całkowanie powinno być wykonane równolegle przy użyciu standardu MPI. Wybrany proces główny rozdziela przedział całkowania oraz liczbę punktów, w których będą wykonywane obliczenia pomiędzy siebie i pozostałe procesy. Rozsyła potrzebne informacje do pozostałych procesów oraz wykonuje swoją część obliczeń. Następnie zbiera wyniki od pozostałych procesów i sumuje je ze swoim wynikiem cząstkowym. Ostatecznie wypisuje wynik całkowity na standardowe wyjście. Proszę zwrócić uwagę na to, że każdy z procesów powinien liczyć całkę dla pewnej liczby punktów, która została mu przydzielona przez proces główny (suma punktów z wszystkich procesów powinna być równa liczbie podanej jako argument wejściowy) – zatem proces główny powinien dokonać rozsądnego podziału danych wejściowych pomiędzy procesy.  

Program powinien pozwalać na ustawienie początku i końca przedziału całkowania oraz całkowitej liczby punktów. Program powinien działać poprawnie dla dowolnej, zadanej przez prowadzącego, liczby procesów oraz liczby punktów. Komunikacja pomiędzy procesami powinna zostać zrealizowana jedynie przy użyciu funkcji (MPI_Send, MPI_Recv).  


## Kompilacja programu z wykorzystaniem MPI:
1. mpicc integral_MPI.c  
Uruchomienie:   
mpiexec -n num_procs integrate begin end num_points  
2. mpiexec -n 4 ./a.out -100 100 1000  

## Zadanie do wykonania:  
1. Napisanie procedury całkowania  
2. Podział liczby punktów na poszczególne procesy (możliwie równy!)  
3. Podział przedziałów całkowania dla poszczególnych procesów  
4. Rozesłanie do procesów „robotników” danych umożliwiających obliczenia cząstkowe.  
5. Odbiór danych przez procesy.  
6. Wykonanie obliczeń w procesie głównym.  
7. Wykonanie obliczeń w procesach „robotnikach”  
8. Przesłanie obliczeń cząstkowych do procesu głównego.  
9. Zsumowanie wszystkich wyników i wyświetlenie wyniku końcowego.  

## Dodatkowe zadania do wykonania:
TEGO NIE MA  
1. Napisanie programu z wykorzystaniem komunikacji grupowej (MPI_Scatter, MPI_Gather/MPI_Reduce)  

2. Napisanie programu z wykorzystaniem komunikacji nieblokującej (MPI_Isend, MPI_Irecv)  

3. Uruchomienie programu na dwóch maszynach.  

### Wymagania:
* Obsługa środowiska MPI 
* odpowiedni podział liczby punktów oraz przedziałów 
* umiejętność korzystania z funkcji MPI_Recv, MPI_Send  
* poprawność wyniku  
* estetyka kodu.  

### Dodatkowe materiały:  
1. http://mpitutorial.com/tutorials/mpi-hello-world/﻿

2. http://mpitutorial.com/tutorials/mpi-send-and-receive/﻿

### DO zrobienia:
W ramach ćwiczenia proszę stworzyć 3 programy wykonujące operację całkowania:	
* Program wykorzystuje do komunikacji tylko  funkcje MPI_Send, MPI_Recv
* Program wykorzystuje do komunikacji funkcje komunikacji kolektywnej (MPI_Scatter, MPI_Gather/MPI_Reduce)
* Program wykorzystuje komunikację nieblokującą (MPI_Isend, MPI_Irecv)