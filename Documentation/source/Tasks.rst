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

**[HT04]** Dodawanie nawyków
 *  Encja tabeli habit_definition
 *  Dao do wspomnianej wyżej tabeli
 *  Akcja add, która pozwala na dodawanie nawyków

**[HT05]** Wyświetlanie listy nawyków
 *  Polecenie list, które pozwala na wyświetlanie listy nawyków

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi

**[T01]** Generator plików
 *  pliki \*.cpp i \*.h
 *  pliki CMakeLists.txt

**[T02]** Generator tabel do systemu rst/sphinx
