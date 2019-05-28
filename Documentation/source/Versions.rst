Wersje programu - pseudo changelog
===============================================================================

Wersja 0.2 - Trochę bardziej przyjazna użytkownikowi (w trakcie)
*******************************************************************************
*   Polecenie setall do masowego wypełniania wszystkich nawyków
*   Możliwość odznaczenia nawyku
*   Obsługa znacznika dni np. day:yesterday do wpisania nawyku za wczoraj
*   Obsługa pliku konfiguracyjnego z przekazaniem domyślnej bazy danych
*   Możliwość wycofywania i poprawiania nawyków

Wersja 0.1 - Pierwsza jako tako użyteczna wersja
*******************************************************************************
*   Podstawowe działanie: dodawanie nawyków, wypełnianie, wyświetlanie itp)
*   Obsługa nawyków tylko na dzień dzisiejszy
*   Tylko nawyki typu bool

Planowane
*******************************************************************************
Czego to ja nie planuję :) Jest to lista rzeczy, które planuje dodać w
przyszłości ale na razie jest za wcześnie, żeby pisać o tym w Task.rst

**Grupownaie nawyków**
    Np. poranne aktywności są zazwyczaj wykonywane razem dobrze byłoby je
    pogrupować tak, żeby zaznaczać wszystkie jako wykonane za jednym poleceniem

**Zaawansowane oznaczanie kiedy zadania mają być wykonywane**
    Różne typy w stylu "tylko w poniedziałki i środy" lub dwa razy w tygodniu

**Szyfrowanie bazy danych i konieczność podawania hasła**

**Tester czcionki używanej w konsoli**
    W przyszłości będę potrzebował serii dziwnych znaków z unicode do
    wyświetlania różnych danych. Problem w tym, że nie wszystkie czcionki
    wyświetlane w konsoli obsługują wszystkie znaki, których chciałbym użyć
    (np Consolas). Trzeba dodać nową akcję wyświetlającą wszystkie używane
    znaki tak, żeby móc sprawdzić czy wszystko będzie OK

**Sprawdzanie integralności bazy danych**
    Coś co mogłoby sprawdzać czy z bazą jest wszystko w
    porządku. Poprawna definicja tabel itp

**Zwracanie ID przez funkcje zapisujące w dao**
    Jak w temacie, uprości to trochę kod testów

**Logowanie zapytań**
    Zapisywane lib wyświetlanie aktualnie wykonywanych zapytań i parametrów z
    jakimi zostają wywoływane

**I w ogóle jakaś zaaawansowana klasa logująca**

**Wyświetlanie znaków unicode w konsoli**

**Plik konfiguracyjny**
    domyślna baza danych
    informacje o poziomach logwania

**Zaawansowany system logowania**
    Określenie czy logować na konsoli czy do pliku, nazwa pliku z logiem,
    poziomy logowania lub co ma być logowane

**Kolorowanie outputu konsoli**

**Polecenie undo**
    każda akcja byłaby logowana w ten sposób, żeby na jej podstawie utworzyć
    akcję, która będzie wycofywała ostatnią operację
