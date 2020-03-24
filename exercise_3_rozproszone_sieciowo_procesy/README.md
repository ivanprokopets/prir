# [Lab] Cwiczenie 3 - rozproszone sieciowo procesy

## Tresc:  
Przetwarzanie równoległe rozproszone bez specjalnych mechanizmów synchronizacji i komunikacji między węzłami. Problem przetwarzania równoległego do rozwiązania - dystrybucja dużego zbioru danych wejściowych.  

## Warto zapoznac sie: 
1. Process (pozwala na tworzenie obiektów nowych procesów),  
2. Queue (klasa kolejki - dzięki której będziemy wymieniać dane pomiędzy procesami),  
3. Manager - obiekty typu Manager zarządzają procesem - serwerem, który udostępnia współdzielone obiekty (np. obiekt kolejki). Inne procesy mogą uzyskać dostęp do obiektów współdzielonych. Obiekty typu Manager pozwalają również na dostęp do kolejki poprzez połączenie sieciowe.  

## Zadanie do wykonania:  
Proszę napisać program realizujący rozproszone zadanie obliczenia iloczynu macierzy i wektora. Program powinien składać się z:  
* serwera - tworzącego obiekt typu Manager udostępniający dwie kolejki - jedną, do której przekazywane są dane do obliczeń oraz drugą - do której przekazywane są cząstkowe rozwiązania.
* klienta - wczytującego dane macierzy i wektora i dzielącego dane na liczbę zadań przekazaną jako argument programu. Klient dodaje zadania do pierwszej kolejki, odbiera wyniki wrzucone do kolejki z wynikami czątkowymi i łączy wynik w wektor w odpowiedniej kolejności.
* programu wykonującego obliczenia (workera) - program pobiera zadania z kolejki, tworzy określoną liczbę podprocesów (może odpowiadać np. liczbie procesorów dostępnych w danej maszynie), wykonuje obliczenia dla kolejnych odebranych zadań, wyniki dodaje do kolejki z wynikami czątkowymi. Program proszę uruchomić również na innej maszynie/ maszynach niż na tej na której znajduje się program serwera.

## Do zbadania eksperymentalnie:  
1. Czas wykonywania mnożenia macierzy przez wektor przy różnych (zaproponowanych przez każdy zespół) strategiach dystrybucji danych do węzłów obliczeniowych.
2. Porównanie czasu wykonywania tego samego zadania na jednej maszynie z wieloma rdzeniami/procesorami z wykonaniem na kilku maszynach.
3. Zbadanie prawa Amdhala dla samodzielnie wygenerowancyh danych testowych.  
*1/((1−P)+P/N).* 
(gdzie P - proporcja programu, która może ulec zrównolegleniu, N - liczba procesorów).  
Należy samodzielnie przeanalizować, która część napisanego programu może być zrównoleglona.

## Pytania: 
1. Jak efektywnie przekazywać dane pomiędzy węzłami obliczeniowymi?  
2. Jakiego typu zadania warto obliczać za pomocą narzędzi “process-based execution”?  
3. Warto porównać z waŧkami.  
4. Porównać uruchamianie na kilku maszych oraz na jednej maszynie z kilkoma rdzeniami? Czy warto stosować algorytm rozproszony sieciowo? Kiedy?  
5. Jak ważna w tym modelu jest prędkość komunikacji miedzy węzłami?  

### Wymagania:
* Tworzenie rozproszonych sieciowo procesow, 
* zapewnienie poprawnego wyniku obliczeń, 
* umiejętność wykorzystania estetyka kodu

### Dodatkowe materiały:  
1. https://wiki.python.org/moin/GlobalInterpreterLock)  
2. https://docs.python.org/2/library/multiprocessing.html  
