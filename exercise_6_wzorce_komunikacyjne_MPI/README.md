# [Lab] Ćwiczenie 6 - Wzorce komunikacyjne MPI

## Kompilacja programu z wykorzystaniem MPI:
1. mpicc integral_MPI.c  
Uruchomienie:   
mpiexec -n num_procs integrate begin end num_points  
2. mpiexec -n 4 ./a.out -100 100 1000  

## Zadanie do wykonania:  
### Zad 1  

Proszę policzyć największy wspólny dzielnik (NWD) poszczególnych liczb całkowitych przechowywanych w różnych procesach używając opisanego poniżej wzorca komunikacyjnego. (W każdym z procesów należy zainicjować lokalną przechowywaną przez niego wartość).  

Wzorzec komunikacyjny „upowszechnianie” (dissemination pattern) pozwala każdemu z procesów wyliczyć wartość rozwiązania w maksimum log p krokach komunikacyjnych, gdzie każdy z procesów otrzymuje częściowe wyniki aby wykonać ostateczną ich redukcję na koniec ostatniego przebiegu przesyłu danych.  
  
Jak widać na rys1. (załącznik) zakładamy komunikację pomiędzy procesami po jednokierunkowym okręgu (tzn. prawym sąsiadem n-1 procesu jest proces 0). W pierwszym kroku dane są przesyłane do procesu o 1 większego od procesu wysyłającego, następnie wykonywana jest operacja na danych cząstkowych, w kolejnych krokach do procesu o 2 większego itd. (przesunięcie jest z każdym kolejnym krokiem zwiększane dwukrotnie), aż do pełnej wymiany informacji.  

Dla uproszczenia implementacja może ograniczać się do l. procesów będących potęgą 2.  

### Zad 2  

W wypadku rozsyłania dużych danych często efektywniej jest zastosować wzorzec potokowego przesyłania danych (*pipeline),* gdzie dane (wysyłana wiadomość) są rozdzielane na n fragmentów. W zadaniu tym rozważmy jedno-wymiarową topologię komunikacyjną, gdzie każdy proces wysyła dane tylko do swojego prawego sąsiada. W momencie gdy zostanie otrzymany fragment danych od lewego sąsada jest przesyłany dalej do prawego sąsiada procesu który otrzymał dane, w tym samym momencie zaczyna się odbiór następnej porcji danych. (rys2 - zalacznik).  

Proszę:  

1) Utworzyć jednowymiarowy komunikator z wirtualną topologią kartezjańską (O toplogiach wirtualnych w MPI możecie Państwo przeczytać np. tu: https://computing.llnl.gov/tutorials/mpi/#Virtual_Topologies).  

2) Proszę rozesłać wektor int o rozmiarze 1000000 (podział danych na części po 1000 elementów) z procesu 0 do pozostałych procesów przy użyciu potokowego przesyłania danych (rys). Proszę w tym celu użyć stworzonego przez Państwa komunikatora Kartezjańskiego i funkcji MPI_Cart_shift w celu określenia sąsiedniego procesu. (Procedura ułatwi obsługę warunków brzegowych – dla procesu 0 i n-1 zwracając dla ich sąsiadów wartość MPI_PROC_NULL). (Wysyłanie i odbiór danych z MPI_PROC_NULL jest dozwolony i pozwoli uprościć program).  

### Wymagania:
* Obsługa środowiska MPI 
* odpowiedni podział liczby punktów oraz przedziałów 
* umiejętność korzystania z funkcji MPI_Recv, MPI_Send  
* poprawność wyniku  
* estetyka kodu.  

### Dodatkowe materiały:  
1. https://computing.llnl.gov/tutorials/mpi/#Virtual_Topologies
