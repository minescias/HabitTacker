SQLite - notatki
================================================================================

Różne notatki związane z biblioteką SQLite. Obserwacje, testy, wątpliwości itp.

Select, który nie zwraca danych
    W przypadku, gdy select nie zwróci żadanych danych lista kolumn jest cały
    czas dostępna. Metody initialized() = true i emtpy() = true w moim
    datasecie. Potwierdza to test QueryTests_select_that_returns_empty_dataset.

Brak polecenia Merge
    W przeciwieństwie do takiego np. Oracle, SQLite nie obsługuje merge
