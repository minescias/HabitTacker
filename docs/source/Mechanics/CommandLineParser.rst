CommandLineParser
===============================================================================

Klasa parsująca to co wpisał użytkownik i pakująca wyjście do struktury
ParserResult. Parser sprawdza poprawność pod względem składniowym a nie
logiczym. To czy komenda wpisana przez użytkownika ma sens jest sprawdzanie
dopiero wewnątrz konkretnej akcji

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
    lub param (-<param>=<wartosc>)

Wynik parsowania jest zapisywany do struktury ParserResult, który przechowuje
każdą z wyżej wymienionych sekcji w osobnym polu.

Przykłady:
 #. **htr command foo -bar -bar2 -par=one -par2=two**, gdzie:
     *  htr - nazwa programu
     *  command - nazwa komendy
     *  foo - parametr domyślny (bez myślnika)a
     *  -bar, -bar2 - flagi (przechowują tylko wartość typu bool)
     *  -par, -par2 - parametry (one, two - wartości tych parametóww

ParserResult
*******************************************************************************
Klasa z wynikami parsowania wiersza poleceń. Argumenty są zapisywane w formie
mapy. Nazwy parametrów są przechowywane bez myślnika
