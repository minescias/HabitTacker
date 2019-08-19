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
 *  cmake <name> test - tworzy plik projektowy. Opcjonalny parametr <test>
    pozwala na stworzenie pliku cmake do testów

Podczas tworzenia pliku .cpp automatycznie jest dodawany include do pliku
nagłówkowego od katalogu Src\

W przypadku, gdy plik już istnieje nie zostanie nadpidany

addToCmake
********************************************************************************
Dodaje plik do projektu CMake. Użycie ``addToCmake <filename>``

Poszukuje pliku CMake w górę drzewa folderów. Po znalezieniu udpowiedniego
pliku pyta się użytkownika do której grupy dodać plik. Na razie nie ma
możliwości utworzenia nowej grupy, będzie to dodane później.

cart - compile and run tests
********************************************************************************
Składnia cart <nazwa projektu z testami> <filtr>

Kompiluje moduł z testami oraz wszystkie jego zależności, a następnie uruchamia
testy. Możliwe jest przekazanie filtra, którego składnia jest identyczna jak
-gtest_filter
