Planowane
================================================================================

Czego to ja nie planuję :) Jest to lista rzeczy, które planuje dodać w
przyszłości ale na razie jest za wcześnie, żeby pisać o tym w Task.rst

**Różne**
 #. W jednym z konstruktorów DateTime rzucam wyjątkiem. Wydaje mi się,
    że nie powinno się tego robić. Do sprawdzenia.

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

**Wyświetlanie znaków unicode w konsoli**

**Kolorowanie outputu konsoli**

**Polecenie undo**
    każda akcja byłaby logowana w ten sposób, żeby na jej podstawie utworzyć
    akcję, która będzie wycofywała ostatnią operację

**Podpowiadanie składni**
    Dobrze byłoby, gdyby program podpowiadał składnię - autouzupełnianie
    komendy i parametrów

**Skrótowe nazwy jako filtr**
    Wpisywanie ID jako nazwy nie jest za przyjemne dobrze byłoby, gdyby była
    możliwość podania 3-4 literowego skrótowca, który pozwoliłby na łatwiejsze
    filtrowanie. Problematyczne może być przerobienie parsera command line tak,
    żeby działał zarówno z cyframi jak i nazwami w formie tekstu.
