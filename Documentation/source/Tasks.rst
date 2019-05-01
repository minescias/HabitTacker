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

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C01]** Nowy system zapytań do bazy danych.
 *  Sprawdzić już istniejący kod i zobaczyć co można użyć ponownie
 *  Klasa Dataset2 i polecenie execute2() w klasie Query

**[C02]** Usunięcie folderu utils i Trzymanie wszystkiego bezpośrednio w Core

**[C03]** Dodanie DateTime do Core programu
 *  typedef na std::chrono::time_point
 *  pobieranie aktualnej daty

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT07]** Możliwość wypełniania nawyków
 *  OK Encja tabeli habit
 *  Dao tabeli habit (interfejs i testy)
 *  Polecenie "set" do ustawiania dzisiejszej wartości nawyku

**[HT08]** Domyślna baza danych
 *  Znaleźć sposób na przekazywanie bazy danych do porgramy tak, żeby nie
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

**[HT99]** Refaktor - zadanie zbiorcze
 *  Database creator - przekazywane połączenia do bazy z zewnątrz
 *  Lista inicjalizacyjna do tworzenia encji habit definition (AddAction.cpp i
    testy tegoż)
 *  Czy metody w Dao mogą być constowe (czy przekazywanie DB nie przeszkadza w
    tym. Jeśli tak to zamienić
 *  Automatyczne generowanie operatora porównania

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
