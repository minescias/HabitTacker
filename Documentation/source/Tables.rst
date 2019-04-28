Tabele
===============================================================================
Opis tabel występujących w bazie danych

habit_definition
*******************************************************************************
Tabela z definicją nawyku. W tym momencie zawiera tylko nazwę ale przyszłości
będzie rozwijana o inne opcje takie jak status aktywności, typ itp.

===== ============= ===========================================================
Nazwa Typ (PK)      Opis
----- ------------- -----------------------------------------------------------
id    integer       Id nawyku
name  varchar(40)   Nazwa
===== ============= ===========================================================

habit
*******************************************************************************
Tabela z wynikami wykonywania wyników na poszczególne dni

============ ============= ====================================================
Nazwa        Typ           Opis
------------ ------------- ----------------------------------------------------
habit_id     integer (PK)  Id nawyku
date         date (PK)     Data wypełnienia nawyku
result       integer       Czy udało się wypełnić nawyk na dany dzień
============ ============= ====================================================
