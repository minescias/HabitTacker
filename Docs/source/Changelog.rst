Wersje programu - pseudo changelog
===============================================================================

Wersja 0.4 - Nawyki liczbowe, raporty i podsumowania (w trakcie)
*******************************************************************************

Zmiany w logice biznesowej
 *  Dodano możliwość ustawienia celu podczas dodawania nawyku

Zmiany w działaniu programu
 *  Lib.fmt - Formatowanie tekstu za popocą biblioteki fmt
 *  Lib.date - Obsługa daty i czasu za pomocą biblioteki Date
 *  Core.Query - Obsługa błędów rzuconych w trakcie wykonywania zapytania
 *  Core.Log - Wywoływanie flush po każdym logowaniu
 *  Ht.Db - Włączenie foreign key po utworzeniu bazy danych

Poprawki błędów

Inne
 *  Formatowanie plików źródłowych za pomocą clang-format

Wersja 0.3 - Nadrobienie długu technologicznego
*******************************************************************************
*   Poprawienie DaoFactory zgodnie z opisem w notatkach
*   Poprawki działania CLI - klasa Parameters i walidacja poprawności
    wprowadzanych danych - opis w notatkach
*   Zaawansowany mechanizm logujący
*   Nowe narzędzia ułatwiające pracę
*   Nowy system obsługi baz danych
*   Uruchomienie statycznej analizy kodu (valgrind?)
*   Pozostały refaktor

Wersja 0.2 - Trochę bardziej przyjazna użytkownikowi
*******************************************************************************
*   Możliwość odznaczenia nawyku
*   Obsługa znacznika dni np. day:yesterday do wpisania nawyku za wczoraj
*   Obsługa pliku konfiguracyjnego z przekazaniem domyślnej bazy danych
*   Możliwość wycofywania i poprawiania nawyków

Wersja 0.1 - Pierwsza jako tako użyteczna wersja
*******************************************************************************
*   Podstawowe działanie: dodawanie nawyków, wypełnianie, wyświetlanie itp)
*   Obsługa nawyków tylko na dzień dzisiejszy
*   Tylko nawyki typu bool
