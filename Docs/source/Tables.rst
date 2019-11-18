Tabele
===============================================================================
Opis tabel występujących w bazie danych

habit_definition
*******************************************************************************
Tabela z definicją nawyku. W tym momencie zawiera tylko nazwę ale przyszłości
będzie rozwijana o inne opcje takie jak status aktywności, typ itp.

========== ============= ======================================================
Nazwa      Typ           Opis
---------- ------------- ------------------------------------------------------
id         integer (PK)  Id nawyku
name       varchar(40)   Nazwa
begin_date date          Data, od kiedy obowiązuje dany nawyk
========== ============= ======================================================

habit
*******************************************************************************
Tabela z wynikami wykonywania nawyków na poszczególne dni. Wpis w tej tabeli
oznacza, że dany nawyk został wykonany na dany dzień

============ ============= ====================================================
Nazwa        Typ           Opis
------------ ------------- ----------------------------------------------------
habit_id     integer (PK)  Id nawyku
date         date (PK)     Data wypełnienia nawyku
============ ============= ====================================================

requirement
********************************************************************************
Tabela warunkami wymaganymi do wypełnienia nawyku na dany dzień

============ ============ =====================================================
Nazwa        Typ          Opis
------------ ------------ -----------------------------------------------------
id           integer (PK) Id
habit_id     integer (FK) Id nawyku
begin_date   date         Czas rozpoczęcia
end_date     date         Czas zakończenia
daily_target integer      Dzienny cel
============ ============ =====================================================

Aktualne wymagania mają wartość null w polu end_date
