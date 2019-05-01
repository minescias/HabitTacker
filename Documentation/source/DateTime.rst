Data i czas
===============================================================================
Różne notatki dotyczące przechowywania daty i czasu w bazie danych i kodzie C++

Reprezentacja daty w bazie danych
*******************************************************************************
Data będzie przechowywana w kolumnach o typie **Date**

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
