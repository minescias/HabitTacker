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
    Dostępna jest opcja cmake --build . --target <nazwa modułu> ale to buduje
    wszystkie moduły, od których zależy ten, który chcemy zbudować (chociaż
    może to i lepiej?

**[B04]** Udostępnianie klas między modułami - makro DLL_EXPORT

**[B06]** Podpięcie mojej dokumentacji do githuba - wydaje mi się, że  da się
    tak zrobić

**[B07]** W przypadku błędy działanie programu często kończy się komunikatem
    Segmnetation fault (Core dumped) - sprawdzić co to za core i co można z
    tego wyciągnąć

**[B08]** Włączenie wszystkic warningów w gcc tak jak są domyślne w MSVC

**[B09]** Uruchomić Valgrinda albo inny program do sprawdzania wycieków pamięci

**[B10]** Sprawdzić co to jest profiler i jak można tego użyć

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C01]** Nowy system zapytań do bazy danych.
 *  Klasa field reprezentująca jedno pole - klasa ta pownna zajmować się
    rzutowaniem wyników na typ, jakiego oczekuje użytkownik
 *  Klasa row/record - wektor pól z dostępem po nazwie kolumny
 *  Klasa Dataset2 - zestaw pól - powinna obdługiwać zakresowe pętle for
 *  Polecenie execute2() i executeCommand() w klasie Query. Jedno powinno
    zwracać dataset a drugie nie
 *  Zamiana starych zapytań na nowe
 *  Opis działania w dokumentacji

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

**[C09]** Zaawansowany mechanizm logujący zmiany
 *  Globalny obiekt do logowania
 *  Flagi/enum do oznaczania co ma być logowane (na początek będą potrzebne:
    SQL, wywoływanie alcji i zwykły log debugowy
 *  Logowanie danych w zależności od tego na jakim poziomie są logowane
 *  Logowanie miejsca logowania (jakkolwiek głupio to brzmi :) __FILE__ i
    __LINE__)
 *  Logowanie czasu
 *  Miejsce logowania - konsola lub plik (lub oba)
 *  Parametry do pliku konfiguracyjnego włączające funkconalności opisane wyżej
 *  Opis działania całości w dokumentacji

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

**[D04]** Struktura pliku CMake (ze względu na narzędzia parsujące)

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT18]** Klasa BaseAction w której byłaby podstawowa implementacja akcji.
 *  Blokowane przez [HT27]
 *  Przeniesienie metody setDaoFactory do klasy bazowej.
 *  Pobieranie dao z fabryki w momencie użycia a nie w metodzie setDaoFactory
 *  Wywoływanie sprawdzania poprwaności danych w klasie bazowej (uzupełnianie
    jakie to dane będzie w klasach pochodnych

**[HT19]** Jeśli nazwa nawyku kończy się polską literą to tabela z
    wypełnieniem jest przesunięta o jeden znak w lewo :)

**[HT20]** Polecenie Settings
 *  Domyślnie wyświetlana jest aktualna konfiguracja z pliku .rc
 *  Możliwość ustawiania wartości z pomocą polecenia
    **htr settings <name>:<value>**

**[HT27]** Walidacja poprawności danych wprowadzonych przez użytkownika
 *  Blokowane przez [HT24]
 *  Nowa klasa walidatora + testy
 *  Walidacja poprawności filtra (tylko sprawdzanie czy wymagany i czy cyfra)
 *  Walidacja poprawności flag
 *  Walidacja poprawności domyślnego parametru
 *  Walidacja poprawności parametrów
 *  Dokumentacja

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Lista inicjalizacyjna do tworzenia encji habit definition (AddAction.cpp i
    testy tegoż)
 *  Automatyczne generowanie operatora porównania
 *  Namespace tests dla wszystkich testów
 *  Uspójnienie kodu testowego przez dodanie metod do pobierania domyślnej
    encji i funkcji do porównywania encji - zmiany w module test tools.
 *  Pozbyć się słowa Entity w nazwie klasy encji - sam namespace na to wskazuje

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

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

**[T09]** Narzędź, który zmieni camesCase na podkreślniki

**[T10]** Zarządzanie plikami CMake
 *  OK Dodawanie plików do CMake
 *  Pytanie o dodanie pliku do CMake po utworzeniu za pomocą gen
 *  Walidacja, czy dany plik jest już dodany
 *  Walidacja rozszerzenia, podpowiadanie tylko plików .cpp po wciśnięciu Tab
 *  Tworzenie nowych grup
 *  Usuwanie plików z kompilacji
