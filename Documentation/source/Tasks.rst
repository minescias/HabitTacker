Lista zadań
===============================================================================

.. toctree::

   tasks/Done
   tasks/Cancelled

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania itp

**[B01]** Budowanie dokumentacji razem z projektem za pomocą polecenia make
    Tak, żeby i kod i dokumentacja były budowane za pomocą jednego polecenia

**[B02]** Budowanie dokumentacji jako osobny target CMake
    Celem jest możliwość zbudowania dokumentacji z
    a pomocą polecenia np.
    "make doc" z folderu, w którym są normalnie budowane pliki cpp

**[B03]** Budowanie jednego modułu

**[B04]** Udostępnianie klas między modułami - makro DLL_EXPORT

**[B06]** Podpięcie mojej dokumentacji do githuba - wydaje mi się, że  da się
    tak zrobić

**[B07]** W przypadku błędy działanie programu często kończy się komunikatem
    Segmnetation fault (Core dumped) - sprawdzić co to za core i co można z
    tego wyciągnąć

**[B08]** Włączenie wszystkic warningów w gcc tak jak są domyślne w MSVC

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C01]** Nowy system zapytań do bazy danych.
 *  Sprawdzić już istniejący kod i zobaczyć co można użyć ponownie
 *  Klasa Dataset2 i polecenie execute2() w klasie Query

**[C02]** Usunięcie folderu utils i Trzymanie wszystkiego bezpośrednio w Core

**[C04]** Poprawki po ostatnich zmianach w module bazy danych.
    Dodałem tam obługę time_t, ale nie robiłem żadnych testów na to. Przydałoby
    się je dodać - ponadto wydaje mi się, że można jakoś uporządkować te bieda
    template, które są w dataset

**[C05]** Funkcja do składania tekstu na wzór boost::format. Mogłaby
    wykorzystywać string literals ()_xx

**[C06]** Funkcja do pobierania nazwy klasy + poprawić komunikat błędu w teście
    DaoFactoryTests::throwsLogicErrorWhenTryingToCastDaoToWrongType
    // https://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object

**[C09]** ...

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT10]** Wydzielenie modułu HtDbTests, w której będą testy korzystające z
    bazy danych - testy dao. Chodzi o to, że testy te zajmują stosunkowo dużo
    czasu i generują sporo bałaganu w komunikatach przez log debugowy

**[HT16]** Oznaczanie od kiedy dany nawyk obowiązuje (data dodania)
 *  Rozszerzenie tabeli, encji i dao
 *  Uwzględnienie tego podczas wyświetlania listy wypełnionych nawyków

**[HT18]** Klasa BaseAction w której byłaby podstawowa implementacja akcji.
    Obecnie kod pobierający daoFactory powtarza się w wielu miejscach

**[HT19]** Jeśli nazwa nawyku kończy się polską literą to tabela z wypełnieniem
    jest przesunięta o jeden znak w lewo :)

**[HT20]** Polecenie Settings
 *  Domyślnie wyświetlana jest aktualna konfiguracja z pliku .rc
 *  Możliwość ustawiania wartości z pomocą polecenia
    **htr settings <name>:<value>**

**[HT22]** Możliwość podawania dnia w opcjonalnych parametrach
 *  OK Rozszerzenie command line parsera tak, żeby przekazywać opcjonalne
    parametry z nazwą i wartością - składnia -<nazwa>=<wartość> (bez spacji)
 *  OK Dodanie opcji -date=<day> do komendy done
 *  OK Parser przetwarzający datę z parametru na datę wpisaną do bazy danych
 *  Przetwarzanie daty formatu DD-MM-YYYY na timestamp
 *  Dokumentacja

**[HT23]** Polecenie edit do poprawiania definicji
 *  Nowa komenda edit
 *  Polecenie update/merge do dao definicji
 *  Dbsługa filtru, parametru name
 *  Dokumentacja

**[HT24]** Wygodniejsze pobieranie wartości z klasy ParserResult
 *  testy na tę klasę
 *  pobieranie domyślnego parametru
 *  pobieranie flagi
 *  pobieranie wartości parametru

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Lista inicjalizacyjna do tworzenia encji habit definition (AddAction.cpp i
    testy tegoż)
 *  Automatyczne generowanie operatora porównania
 *  Namespace tests dla wszystkich testów
 *  AddAction pozwala na przekazanie pustej nazwy.

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

**[T01]** Generator plików
 *  OK pliki \*.cpp i \*.h
 *  pliki CMakeLists.txt

**[T02]** Generator tabel do systemu rst/sphinx

**[T03]** Generator encji

**[T05]** Konwerter sql/cppsql

**[T06]** W trakcie testów wyświetla się wszystko z cout na konsoli. Sprawdzić
    czy można to jakoś wyłączyć na czas testów. Przekierowanie couta?

**[T07]** Polecenie hmk do zarządzania budowaniem projektu. Opcje
 *  <default> - budowanie całego projektu
 *  clean - usunięcie wszystkich plików powstałych podczas budowania projektu
 *  prepare - uruchomienie "cmake .." w folderze builds
 *  docs - budowanie dokumentacji
 *  <module name> - budowanie tylko tego modułu

**[T08]** Polecenie tests do uruchamiania testów
 *  <default> uruchamianie wszystkich testów
 *  <module name> uruchamianie testów z jednego modułu
