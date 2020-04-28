# [Lab] Ćwiczenie 7 - MPI (MapReduce)

## Ogólny opis idei MapReduce:  
1. http://en.wikipedia.org/wiki/MapReduce  

MapReduce jest szeroko stosowane przy przetwarzaniu dużych zbiorów danych. Nazwa pochodzi od dwóch klasycznych w funkcyjnych językach programowania operacji. Obliczenia realizowane są podczas dwóch głównych etapów:  

etap mapowania, podczas którego na podstawie danych wejściowych obliczane są wyniki pośrednie.
etap redukcji, w którym z wyników pośrednich obliczany jest wynik końcowy.  
Szczegółowy opis, który powinniście Państwo przeczytać i przyswoić, znajduje się pod adresem:  
2. http://research.google.com/archive/mapreduce-osdi04-slides/index.html  

Przykładowy program wykorzystuje model MapReduce do zliczania wystąpień poszczególnych słów w dokumencie.  
Ogólny przebieg działania programu:  
Faza map:  
1. Proces główny wczytuje dokument w postaci listy słów:  
[‘one’, ‘two’, ‘three’, ‘four’, ‘five’, ‘one’]  
2. Proces główny rozdziela listę między procesy:  
p0: [‘one’, ‘two’]  

p1: [‘three’, ‘four’]  

p2: [‘five’, ‘one’]  

Każdy proces w wyniku przetwarzania tworzy przyporządkowanie, w którym dla każdego słowa napotkanego w przetwarzanej części dokumentu przypisana jest lista wystąpień tego słowa:  
p0: {‘one’: [1], ‘two’: [1]}  

p1: {‘three’: [1], ‘four’: [1]}  

p2: {‘five’: [1], ‘one’: [1]}  


Faza reduce:  
1. Proces główny zbiera słowniki i łączy je w jeden globalny słownik.
{‘one’: [2], ‘two’: [1], ‘three’: [1], ‘four’: [1], ‘five’: [1]}  
Proces główny prezentuje wyniki.  
Państwa zadaniem będzie rozwiązanie podobnego problemu w oparciu o program przykładowy.  

## Zadanie do wykonania:  
### Zad 1  

Każda usługa działająca w systemie pozostawia ślad po swojej działalności w postaci wpisów w dzienniku (ang. log). Wraz z upływem czasu pliki dziennika rozrastają się zajmując pokaźną ilość miejsca na dysku. Rozsądna analiza takich danych ułatwia (czasem umożliwia) administratorom rozpoznawanie przyczyn błędów czy też przewidywanie przyszłych zagrożeń. Jednak wymaga to przetworzenia olbrzymiej ilości danych historycznych, co stanowi jedno z pól zastosowań obliczeń równoległych.  

Proszę napisać program, który przetwarza pliki z logami (przykładowo “access-log”serwera WWW). Dla uproszczenia przyjmujemy, że struktura dziennika jest następująca:  
2013-03-27 21:47:14,021 83.6.229.4 “POST /result HTTP/1.1” 500  

2013-03-27 21:47:20,035 83.6.229.4 “GET /favicon.ico HTTP/1.1” 404  

2013-03-27 23:27:25,299 107.21.253.204 “POST /result HTTP/1.1” 200  

2013-03-27 23:27:25,373 107.21.253.204 “GET /favicon.ico HTTP/1.1” 404  

2013-03-27 23:47:35,052 194.29.146.3 “GET /favicon.ico HTTP/1.1” 404  

2013-03-27 23:47:35,330 194.29.146.3 “POST /result HTTP/1.1” 200  

2013-03-27 23:48:46,443 91.231.138.27 “GET /favicon.ico HTTP/1.1” 404  

Każdy wpis zajmuje jeden wiersz dziennika, poszczególne pola odzielone znakami odstępu.  
Program w oparciu o wzorzec MapReduce (przybliżony w programie przykładowym), powinien umożliwiać generowanie statystyk (rozkład liczby żądań w czasie, rozkład liczby żądań z poszczególnych adresów IP).  
Program powinien mieć następujący interfejs:  

`./program –(addr|stat|time) path/to/logfile`  

Dla opcji grupowania po adresie - załóżmy, że plik dziennika ma zawartość taką jak zaprezentowana powyżej i chcemy wykryć adresy, które najbardziej obciążają nasz serwer WWW:  

83.6.229.4 2  

107.21.253.204 2  

194.29.146.3 2  

91.231.138.27 1  


Dla opcji grupowanie po czasie - załóżmy, że plik dziennika ma zawartość taką jak zaprezentowana powyżej. Chcemy wygenerować wykres obciążenia serwera w czasie z dokładnością do minut:  


2013-03-27 21:47 2  

2013-03-27 23:27 2  

2013-03-27 23:47 2  

2013-03-27 23:48 1  

Program powinien umożliwiać łatwe wprowadzenie poprawek (np zmiana formatu linii lub dodanie grupowania po innym polu).  


### Wymagania:
* Obsługa środowiska MPI  
* odpowiedni podział liczby punktów oraz przedziałów   
* poprawność wyniku  
* estetyka kodu.  

### Dodatkowe materiały:  
1. http://en.wikipedia.org/wiki/MapReduce  
2. http://research.google.com/archive/mapreduce-osdi04-slides/index.html  
