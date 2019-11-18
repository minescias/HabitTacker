SQLite - notatki
================================================================================

Różne notatki związane z biblioteką SQLite. Obserwacje, testy, wątpliwości itp.

Select, który nie zwraca danych
    W przypadku, gdy select nie zwróci żadanych danych lista kolumn jest cały
    czas dostępna. Metody initialized() = true i emtpy() = true w moim
    datasecie. Potwierdza to test QueryTests_select_that_returns_empty_dataset.

Brak polecenia Merge
    W przeciwieństwie do takiego np. Oracle, SQLite nie obsługuje merge

Foreign key
    Żeby foreign key działał poprawinie trzeba go najpierw włączyć w bazie
    danych. Trzeba to zrobić za pomocą polecenia "PRAGMA foreign_keys = ON".
    Żeby było śmieszniej jak testowałem działanie w SQLiteStudio to tam
    foreign key jest domyślnie włączony
