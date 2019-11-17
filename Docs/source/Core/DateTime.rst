Data i czas
===============================================================================
Opis dotyczy tylko dat. Obsługa czasu nie jest jeszcze zaimplementowana

Obsługa daty jes realizowana za pomocą biblioteki `date` napisanej przez
Howarda Hinnanta.

*   Dokumentacja: https://howardhinnant.github.io/date/date.html
*   Github: https://github.com/HowardHinnant/date
*   Wykład: https://www.youtube.com/watch?v=tzyGjOm8AKo

**Reprezentacja danych w kodzie C++:**
 *  date::year_month_day - służy do przechowywania daty m. in w encjach. Jest
    postawowym typem używanym do przekazywania dat między funkcjami. Dla wygody
    wprowadzono alias Dt::Date.
 *  date::sys_days - reprezentacja daty w formacie inta liczącego liczbę dni od
    01.01.1970. Używane przy zapisie/odczycie danych z bazy.

**Preprezentacja daty w bazie danych:**
    Daty w sqlite będą przechowywane jako liczba dni od 1.01.1970. Przykładowo
    liczba 18144 odpowiada dacie 2019-09-05. Typ zmiennej przechowującej datę
    to 'DATE' (czyli numeric)

**Reprezentacja daty w formacie tekstu**
    W tym momencie obsługiwany jest tylko jeden format dat, i jest to
    DD.MM.YYYY. Format ten jest używany przy konwersji daty na tekst i
    odwrotnie

Biblioteka `date` nie rozwiązuje wszystkich problemów jakie można napotkać w
pracy z datami. Wg wykładu z linku powyżej część funkcji musi być
zaimplementowana przez użytkownika. Poniżej znajduje się opis i lista funkcji
uzupełniających w.w. bibliotekę

Dt::getCurrentDate()
*******************************************************************************
Zwraca aktualną datę (lokalną z komputera na którym jest uruchomiony program)
a formacie Dt::Date.

Dt::parseDate()
********************************************************************************
Konwertuje tekst na datę. Tekst musi być w formacie DD.MM.YYYY. Zwraca datę w
formacie Dt::Date. W przypadku błędnej konwersji rzuca wyjątkiem typu
RuntimeError.

Dt::formatDate()
********************************************************************************
Konwertuje datę na tekst w formacie DD.MM.YYYY.

Dt::addDays()
********************************************************************************
Dodaje określoną liczbę dni do daty. Biblioteka `date` nie ma tego
zaimplementowanego ze względu na wydajność (było o tym w wykładzie albo na
gicie)

Dt::DateLiteral
********************************************************************************
Klasa konwertująca tekst na datę. W przeciwieństwie do funckji Dt::parseDate()
obsługuje również określenia dat w forme słownej, np. 'today', 'yesterday'
