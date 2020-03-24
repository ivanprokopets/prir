# [Lab] Ćwiczenie 2 - wątki (C, Java, Python)

## Zadanie do wykonania:  
Proszę napisać program, który:  
* wykonuje mnożenie dwóch macierzy lub (wg decyzji prowadzącego)
* oblicza sumę elementów macierzy wyjściowej,
* wyznacza normę Frobeniusa wyjściowej (pierwiastek sumy kwadratów wszystkich elementów macierzy  

Program wczytuje z plików dwie macierze, a następnie wykonuje ich mnożenie. Mnożenie powinno przebiegać współbieżnie i ma być wykonywane przez N utworzonych w programie wątków. Podział obliczeń najwydajniej jest przeprowadzić według macierzy wynikowej. Należy unikać niepotrzebnej alokacji i kopiowania pamięci (każdy wątek operuje na tych samych danych (używając wskaźników) i zapisuje wyniki do współdzielonego miejsca w pamięci. Każdy z wątków powinien ponadto obliczać sumę elementów wyliczonego fragmentu macierzy i dodawać ją do zmiennej globalnej przechowującej całkowitą sumę.

 ## Przebieg programu:  
1. Wczytanie macierzy z pliku oraz inicjalizacja macierzy wynikowej.  
2. Stworzenie indeksów określających podział danych obliczeniowych  
3. Utworzenie N wątków potomnych  
4. Obliczenie cząstkowych wyników mnożenia przez poszczególne wątki.  
5. Obliczenie w poszczególnych wątkach sumy elementów fragmentów macierzy i zapisanie ich do zmiennej globalnej.  
6. Zebranie statusów zakończenia wątków.  
7. Wypisanie wyniku na ekran. (macierzy wynikowej oraz sumy elementów)  
8. Zwolnienie pamięci.  


Proszę napisać dwa programy realizujące powyższe zadanie:  

* jeden program ma wykorzystywać wątki POSIX (pthread) a drugi język Java włącznie z synchronizacją dostępu do danych, lub
* jeden program ma wykorzystywać wątki POSIX (pthread) a drugi język Python włącznie z synchronizacją dostępu do danych.

### Wymagania:

* Tworzenie wątków, 
* funkcji wątku, 
* podział danych na elementy obliczeniowe, 
* zapewnienie poprawnego wyniku obliczeń, 
* umiejętność wykorzystania estetyka kodu

### Dodatkowe materiały:  
1. http://wazniak.mimuw.edu.pl/index.php?title=Programowanie_wsp%C3%B3%C5%82bie%C5%BCne_i_rozproszone/PWR_%C4%86wiczenia_9
2. http://www.ibm.com/developerworks/library/l-posix2/
3. http://www.tutorialspoint.com/python/python_multithreading.htm
4. http://en.wikipedia.org/wiki/Matrix_norm#Frobenius_norm
