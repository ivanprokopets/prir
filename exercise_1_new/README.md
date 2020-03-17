# [Lab] Ćwiczenie 1 - Sygnały z pamięcią współdzieloną

## Treść:  
Sygnały pozwalają na proste informowanie procesów, jednak nie pozwalają przekazywać informacji między nimi. Dlatego warto jest korzystać z pamięci współdzielonej. W tym ćwiczeniu należy przetestować mechanizm IPC Shared Memory (http://www.cs.cf.ac.uk/Dave/C/node27.html ).  

## Zadanie do wykonania:  
 Należy napisać program służacy do sumowania elementów w wektorze zapisanym w pliku.
Sumowanie ma przebiegać współbieżnie i ma być wykonywane przez N procesów potomnych.
Procesy potomne korzystają z dwóch przestrzeni pamięci współdzielonej zawierających odpowiednio:
zakresy indeksów, które dany proces ma sumować i tablicę z wynikami cząstkowymi.

 Proces główny tworzy procesy potomne, wczytuje plik z wektorem, inicjalizuje dane w pamięci, a następnie, gdy dane są gotowe, wysyła wszystkim dzieciom sygnał SIGUSR1, informując je przy tym, że dane są już dostępne. Proszę obejrzeć załączony plik add.c pokazujący prawidłowy sposób wczytywania wektorów.
 
 ## Przebieg programu:  
1. proces główny tworzy tyle N dzieci i każdemu z nich ustawia wartość id = 0..(CHILD-1)  
2. dziecko po utworzeniu konfiguruje obsługę sygnału SIGUSR1,  
3. dziecko czeka na sygnał od rodzica,  
4. proces główny po utworzeniu dzieci czyta plik z wektorem i tworzy dwie przestrzenie pamięci współdzielonej,  
5. następnie uzupełniane są elementy wektora z pliku,  
6. ustalane są zakresy indeksów dla poszczególnych procesów potomnych,  
7. inicjowana jest tablica z wynikami cząstkowymi,  
8. poinformowanie sygnałem procesów potomnych, że dane są gotowe,  
9. poczekanie na zakończenie obliczeń,  
10. policzenie ostatecznej sumy na podstawie wyników cząstkowych,  
11. odłączenie i zwolnienie pamięci współdzielonej.  
12. wypisanie wyniku na ekran.  

### Eksperyment:  

mierzyć czas wykonania średniego zadania, zwielokrotnionego (powtórzyć równoległą operację wiele razy aby czas wykonywania był mierzalny dla wektorów o rozmiarach 1000) dla różnej liczby procesów potomnych (N=1, 2, 4, 6, 8, 16). Należy przeanalizować czy wyniki pokrywają się z założeniami teoretycznymi. Wykonaną analizę należy uzasadnić.

### Dodatkowe materiały:  
1. https://web.archive.org/web/20160415124909/http://wazniak.mimuw.edu.pl/index.php?title=Programowanie_wsp%C3%B3%C5%82bie%C5%BCne_i_rozproszone/PWR_%C4%86wiczenia_shm
