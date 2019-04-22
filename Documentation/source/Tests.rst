Testy
===============================================================================

Testy bazodanowe
*******************************************************************************
Testy bazodanowe obejmują takie zagadnienia jak: Tworzenie nowej bazy danych,
tworzenie tabel oraz dao.

Podstawowe założenia:
 *  Tworzenie bazy danych (sprawdzanie poprawności utworzenia pliku) jest
    zrobione w obrębie testów polecenia "init" - brak sprawdzania poprawności
    samej bazy
 *  Poprawność utworzonej bazy - brak testów na poprawność utworzonej bazy.
    Bazy danych i tak będą tworzone na potrzeby testów poszczególnych dao, więc
    nie ma sesnu robić osobnych testów na to.
 *  Testy dao mają za zadanie sprawdzić głównie poprawność zapytań, wywołać
    każde zapytanie w różnej konfiguracji
