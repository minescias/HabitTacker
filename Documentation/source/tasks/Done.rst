Lista wykonanych zadań
===============================================================================

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania itp

**[B05]** Sprawdzić czy program wciąż się kompiluje na Linuskie po moich
    ostatnich zmianach w Windowsie

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D01]** Działanie aktualnego systemu zapytań do bazy danych

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT01]** Polecenie init
 *  OK Dodanie modułu main (ht.exe)
 *  OK Dodanie modułu HT (ht.dll)
 *  OK Funkcja AppInit w module HT
 *  OK Podstawowe wywołanie programu
 *  OK Klasa parsera polecenia CLI
 *  OK Klasa akcji polecenia init
 *  OK Parsowanie polecenia init <filename> bez funkcjonalności - tylko
    komunikat o sukcesie
 *  OK Opis pocelenia w dokumentacji

**[HT02]** Kreator pustej bazy danych
 *  OK Klasa do tworzenia pustej bazy danych "Database Creator"
 *  OK Tworzenie tabeli "habit_definition"
 *  OK Tworzenie tabel na polecenie init
 *  OK Sprawdzanie czy plik już istnieje
 *  OK Odporność na błędne parametry (system wyjątków akcji)
 *  OK Opis tabeli w dokumentacji

 **[HT03]** Polecenie Help
 *  OK Parsowanie polecenia Help
 *  OK Wyświetlanie pomocy

 **[HT04]** Dodawanie nawyków
 *  OK Encja tabeli habit_definition
 *  OK Dao do wspomnianej wyżej tabeli (interfejs i testy)
 *  OK Polecenie "add", która pozwala na dodawanie nawyków

**[HT05]** Wyświetlanie listy nawyków
 *  OK Nowa funkcja w dao: getDefinitions + testy
 *  OK Przeniesienie mock dao do wspólnego miejsca
 *  OK Polecenie list, które pozwala na wyświetlanie listy nawyków
 *  OK Aktualizacja dokumentacji Cli

**[HT06]** Dodanie tabeli z realizacją nawyków
 *  OK Nowa tabela "habit" w klasie database creator
 *  OK Opis tabeli w dokumentacji

**[HT07]** Możliwość wypełniania nawyków
 *  OK Encja tabeli habit
 *  OK Dao tabeli habit (interfejs i testy)
 *  OK Polecenie "done" do ustawiania dzisiejszej wartości nawyku
 *  OK Zabezpieczenie przed próbą ustawieniem już wypełnionego nawyku
 *  OK Zabezpieczenie przed próbą ustawienia nieustniejącego nawyku
 *  OK Rozszerzenie command line parsera o filtr prosty i włączenie opcji done
    w appInit()
 *  OK Sprawdzanie przez akcję, czy jest wypełniony filtr
 *  OK Aktualizacja dokumentacji Cli

**[HT11]** Wyświetlanie wypełniania statusów z ostatnich 14 dni
 *  OK Nowa akcja - default
 *  OK Wyświetlanie listy nawyków
 *  OK Wyświetlanie nagłówka dni tygodnia (Ostatni dzień na dzisiaj)
 *  OK Wyświetlanie tabeli wypełnionych nawyków
 *  OK Dodanie akcji do appInit()
 *  OK Aktualizacja dokumentacji cli
 *  OK Zabezpieczenie przed pustą bazą

**[HT12]** usunąć z tabeli habit kolumnę result. Na razie nie jest ona
    potrzebna. Wpisy do tej tabeli będą oznaczały, że zadanie na dany dzień
    zostało wykonane a brak wpisu to brak niewykonane zadanie

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

**[T04]** VSCode - Osobne ustawienia dla plików \*.rst - spacje zamiast tabów
