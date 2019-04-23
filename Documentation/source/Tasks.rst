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

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D01]** Działanie aktualnego systemu zapytań do bazy danych

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT05]** Wyświetlanie listy nawyków
 *  Polecenie list, które pozwala na wyświetlanie listy nawyków

**[HT06]** Dodanie tabeli z realizacją nawyków
 *  Nowa tabela "habit" w klasie database creator
 *  Opis tabeli w dokumentacji

**[HT07]** Możliwość wypełniania nawyków
 *  Encja tabeli habit
 *  Dao tabeli habit (interfejs i testy)
 *  Polecenie "set" do ustawiania dzisiejszej wartości nawyku

**[HT08]** Domyślna baza danych
 *  Znaleźć sposób na przekazywanie bazy danych do porgramy tak, żeby nie
    przekazywać go w każdej komendzie. Do rozważenia plik .htrc lub plik
    konfiguracyjny w katalogu z programem

**[HT99]** Refaktor - zadanie zbiorcze
 *  Database creator - przekazywane połączenia do bazy z zewnątrz

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
