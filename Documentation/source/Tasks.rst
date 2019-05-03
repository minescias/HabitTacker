Lista zadań
===============================================================================

.. toctree::

   tasks/Done

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania itp

**[B01]** Budowanie dokumentacji razem z projektem za pomocą polecenia make
    Tak, żeby i kod i dokumentacja były budowane za pomocą jednego polecenia

**[B02]** Budowanie dokumentacji jako osobny target CMake
    Celem jest możliwość zbudowania dokumentacji za pomocą polecenia np.
    "make doc" z folderu, w którym są normalnie budowane pliki cpp

**[B03]** Budowanie jednego modułu

**[B04]** Udostępnianie klas między modułami - makro DLL_EXPORT

**[B05]** Sprawdzić czy program wciąż się kompiluje na Linuskie po moich
    ostatnich zmianach w Windowsie

**[B06]** Podpięcie mojej dokumentacji do githuba - wydaje mi się, że  da się
    tak zrobić

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C01]** Nowy system zapytań do bazy danych.
 *  Sprawdzić już istniejący kod i zobaczyć co można użyć ponownie
 *  Klasa Dataset2 i polecenie execute2() w klasie Query

**[C02]** Usunięcie folderu utils i Trzymanie wszystkiego bezpośrednio w Core

**[C03]** Dodanie DateTime do Core programu
 *  typedef na time_t
 *  funkcja do pobierania aktualnej daty
 *  funkcja pozwalająca tworzyć datę w jakiś bardziej czytelny sposób niż jest
    to robione aktualnie

**[C04]** Poprawki po ostatnich zmianach w module bazy danych.
    Dodałem tam obługę time_t, ale nie robiłem żadnych testów na to. Przydałoby
    się je dodać - ponadto wydaje mi się, że można jakoś uporządkować te bieda
    template, które są w dataset

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT08]** Domyślna baza danych
 *  Znaleźć sposób na przekazywanie bazy danych do porgramu tak, żeby nie
    przekazywać go w każdej komendzie. Do rozważenia plik .htrc lub plik
    konfiguracyjny w katalogu z programem

**[HT09]** Zmiana nazwy programu, aktualna nazwa koliduje z poleceniem linuksa
 *  Tytuł dokumentacji
 *  Dokumentacja Cli
 *  Help message
 *  Akcja list - komenda przy pustej bazie danych

**[HT10]** Wydzielenie modułu HtDbTests, w której będą testy korzystające z
    bazy danych - testy dao. Chodzi o to, że testy te zajmują stosunkowo dużo
    czasu i generują sporo bałaganu w komunikatach przez log debugowy

**[HT11]** Wyświetlanie wypełniania statusów z ostatnich 14 dni
 *  OK Nowa akcja - default
 *  OK Wyświetlanie listy nawyków
 *  OK Wyświetlanie nagłówka dni tygodnia (Ostatni dzień na dzisiaj)
 *  OK Wyświetlanie tabeli wypełnionych nawyków
 *  Dodanie akcji do appInit()
 *  Aktualizacja dokumentacji cli
 *  Zabezpieczenie przed pustą bazą

**[HT13]** Interfejs akcji
 *  Uspójnione przekazywanie dao i innych danych wymaganych do działania
 *  Uspójnione przekazywanie sparsowanych danych z wiersza poleceń

**[HT14]** Mechanizm tworzenia Dao - DaoFactory
 *  Klasa dao facory
 *  Rejestrowanie akcji (funkcja tworząca dao?)
 *  Wywołanie zarejestrowanej akcji

**[HT15]** Zaawansowany parser command line
 *  Klasa wyniku działania parsera - filtr, komenda i argumenty dodatkowe
 *  Pobieranie prostego polecenia
 *  Pobieranie polecenia z argumentami
 *  Pobieranie polecenia z filrem
 *  Opis działania całości w dokumentacji

**[HT16]** Oznaczanie od kiedy dany nawyk obowiązuje (data dodania)
 *  Rozszerzenie tabeli, encji i dao
 *  Uwzględnienie tego podczas wyświetlania listy wypełnionych nawyków

**[HT99]** Refaktor - zadanie zbiorcze
 *  Database creator - przekazywane połączenia do bazy z zewnątrz
 *  Lista inicjalizacyjna do tworzenia encji habit definition (AddAction.cpp i
    testy tegoż)
 *  Czy metody w Dao mogą być constowe (czy przekazywanie DB nie przeszkadza w
    tym. Jeśli tak to zamienić
 *  Automatyczne generowanie operatora porównania
 *  Przerobić database creatora na buildera, który będzie zwracał połączenie
    handlera do nowo utworzonej bazy danych (ale to będzie zajebiste :))
 *  Namespace tests dla wszystkich testów
 *  ActionError powinno być w namespace Actions

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

**[T01]** Generator plików
 *  pliki \*.cpp i \*.h
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
