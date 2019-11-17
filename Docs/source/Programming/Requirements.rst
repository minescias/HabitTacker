Wymagane biblioteki, narzędzia
================================================================================

Narzędzia
********************************************************************************

Wymagane
 *  **cmake** - minimalna wersja 3.12
 *  **gcc** - minimalna wersja 8.3.0 - na chwilę obecną nie wspieram innych
    kompilatorów. W przyszłości planuję dodać obsługę MSVC i Clanga

Opcjonalnle
 *  **clang-format**
 *  **sphinx** - budowanie dokumentacji
 *  **python** - uruchomienie wewnętrznych narzędzi


Biblioteki
********************************************************************************

Używane biblioteki
 *  googletest - 1.8.1
 *  fmt - 6.0.0
 *  date - 2.4.1
 *  sqlite

Wszystkie bibliteki poza sqlite można pobrać z githuba. W katalogu libraries
znajduje się skrypt **DownloadLibraries.py**, który automatycznie pobierze
wymagane bibliteki umieści je w odpowiednich folderach i zauktualizuje do
wymaganej wersji.

Sqlite nie jest udostępniany na githubie więc trzeba go pobrać ręcznie i dodać
w katalogu Libraies/Sqlite pliki sqlite.h i sqlite.c tak, żeby CMake był
zadowolony :)
