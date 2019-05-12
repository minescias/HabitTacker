Narzędzia
===============================================================================

Lista narzędzi i przydatnych skryptów

Wstep
*******************************************************************************
Wszystkie skrypty znajdują się w folderze Tools. Żeby móc je uruchamiać z
dowolnego katalogu trzeba dodać katalog do zmiennej systemowej PATH. Tymczasowo
nie chcę dodawać tego katalogu na stałe, dlatego powstał skrypt **init.sh**,
który dodaje ww. katalog do ścieżki systemowej.

Skrypt musi być uruchomiony w trybie *source* (source command - nie wiem czy
jest jakiś oficjalny polski odpowiednik tej nazwy)

gen
*******************************************************************************
Skrypt, który pozwala na dodawanie plików c++ do projektu. Dostępne są 3 opcje:
 *  file <name> - zwykły plik .h i .cpp
 *  class <name> - plik .h i .cpp z pustą klasą
 *  test <name> - plik z testami .cpp zawierający pusty fixture zawierający
    wymagane includy, usingi i namespace.

Podczas tworzenia pliku .cpp automatycznie jest dodawany include do pliku
nagłówkowego od katalogu Src\

W przypadku, gdy plik już istnieje nie zostanie nadpidany
