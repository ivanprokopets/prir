# [Lab] Ćwiczenie 4 - OpenMP

## Tresc:  
Proszę zrównoleglić przy pomocy OpenMP program poszukujący liczb pierwszych.



## Opis programu sekwencyjnego:
1. Program znajduje liczby pierwsze z przedziału [2..n].   
2. Program do znajdowania liczb pierwszych korzysta z obserwacji, że do wyznaczania liczb pierwszych z przedziału   
`B = [floor[sqrt(n)]+1..n]` wystarczy znajomość liczb pierwszych z przedziału `A = [2…floor[sqrt(n)]]`.   
3. Każda liczba złożona należąca do przedziału *B* dzieli się przez jedną lub więcej liczb pierwszych z przedziału *A*.   
4. Liczby z przedziału *A* nazwijmy _podzielnikami_.  
5. Aby sprawdzić czy dowolna liczba *j* z przedziału *B* jest złożona, wystarczy sprawdzić czy dzieli się bez reszty przez któryś z podzielników.  
* np. Jeśli chcemy znaleźć liczby pierwsze z przedziału `[2… 10 000]`, to najpierw znajdujemy liczby pierwsze z przedziału `[2..100]` stosując 
* np. sito Eratostenesa. Podzielników takich jest 25 ( liczby: 2,3, 5.. 97). Nastepnie dla dowolnej liczby j nalezącej do B nalezy sprawdzić czy dzieli się przez któryś z podzielników. 


### Program składa się z dwóch faz:
1) Wylicza liczby pierwsze z przedziału `A = 2..floor[sqrt(n)]` zwane podzielnikami stosując sito Eratostenesa.  
2) Poszukuje liczb pierwszych w przedziale `B = [floor[sqrt(n)]+1..n]`. Dowolna liczba j należąca do B jest liczbą pierwszą jeśli nie dzieli się bez reszty przez żaden z podzielników z przedziału A.  
## Zadanie do wykonania:  
1. Proszę zrówoleglić wykonanie programu z wykorzystaniem OpenMP (na początku zastanówcie się Państwo które sekcje programu można zrównoleglić, co powinno zostać wykonane sekwencyjnie, gdzie powinna zostać użyta sekcja krytyczna)  
2. Proszę obliczyć czas wykonania programu sekwencyjnego i zrównoleglonengo `(dla l. wątków 2-8)` dla rozmiaru zadania   
`n=10^5, n=10^6, n=10^7 ` 
3. Dla zrównoleglonego programu dla rozmiaru zadania `n=10^5, n=10^6, n=10^7 (dla l. wątków 2-8)` proszę obliczyć przyspieszenie programu i jego efektywność `(E(p,n) = S(p,n)/p)`.  
