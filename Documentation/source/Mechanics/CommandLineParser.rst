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
    tylko przez "Done". W pozostąłuch akcjach ignorowane

**command name**
    Aktualne polecenie, nie ma tutaj wielkiej filozofii

**Optional parameters**
    Opcjonalne parametry np. nazwa bazy danych. Jest to wszystko to co znajduje
    się za poleceniem command.

Wynik parsowania jest zapisywany do struktury ParserResult, który przechowuje
każdą z wyżej wymienionych sekcji w osobnym polu.
