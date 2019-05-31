CommandLineParser
===============================================================================

Klasa parsująca to co wpisał użytkownik i pakująca wyjście do struktury
ParserResult. Parser sprawdza poprawność pod względem składniowym a nie
logiczym. To czy komenda wpisana przez użytkownika ma sens ma miejsce dopiero
wewnątrz konkretnej akcji

Podstawowa składnia

** htr <filter> <command name> <optional parameters>

Gdzie

**filter**
    Jest to cyfra oznaczająca, którego nawyku dotyczy akcja. Aktualnie używane
    tylko przez "Done". W pozostałych akcjach ignorowane

**command name**
    Aktualne polecenie, nie ma tutaj wielkiej filozofii

**Optional parameters**
    Opcjonalne parametry np. nazwa bazy danych. Jest to wszystko to co znajduje
    się za poleceniem command. W opcjonalych parametravch może się znaleźć
    jeden parametr domyślny i wiele parametrów typu flag (z myślnikiem)

Wynik parsowania jest zapisywany do struktury ParserResult, który przechowuje
każdą z wyżej wymienionych sekcji w osobnym polu.

Przykłady:
 #. **htr command foo -bar -bar2**, gdzie:
     *  htr - nazwa programu
     *  command - nazwa komendy
     *  foo - parametr domyślny (bez myślnika)
     *  -bar, -bar2 - flagi (przechowują tylko wartość typu bool)

ParserResult
*******************************************************************************
Klasa z wynikami parsowania wiersza poleceń. Argumenty są zapisywane w formie
mapy. Nazwy parametrów są przechowywane bez myślnika
