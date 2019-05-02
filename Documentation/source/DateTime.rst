Data i czas
===============================================================================
Różne notatki dotyczące przechowywania daty i czasu w bazie danych i kodzie C++

Reprezentacja daty w bazie danych
*******************************************************************************
Data będzie przechowywana w kolumnach o typie **Date** jako czas unixowy

Z dokumentacji:
    INTEGER as Unix Time, the number of seconds since 1970-01-01 00:00:00 UTC.

W zapytaniach będzie można wyświetlić datę w ludzkim formacie np. za pomocą
**SELECT date('now');**

Reprezentacja daty w C++
*******************************************************************************
* https://en.cppreference.com/w/cpp/chrono
* https://en.cppreference.com/w/cpp/chrono/time_point
* https://github.com/HowardHinnant/date

Docelowo będę chciał skorzystać z biblioteki znajdującej się na stronie
https://github.com/HowardHinnant/date. Najpierw jednak chciałbym zrobić
uboższą wersję tej biblioteki i samemu sprawdzić jak to działa w C++

Przechowywanie daty:
    using Date = std::chrono::system_clock::time_point;

Użyłbym chrono do przechowywania daty i czasu ale większość fajnych
funkcjonalności jest dopiero od c++20...

