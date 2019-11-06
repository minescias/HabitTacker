Przydatne komendy
================================================================================

Budowanie projektu i uruchamianie testów
********************************************************************************

Wszystkie komendy podane poniżej powinny być uruchamiane z folderu builds

``cmake --build . --target Doc``
    Budowanie dokumentacji bezpośrednio z folderu builds. Dokumentacja jest
    budowana do tego samego folderu co użycie komendy ``make html`` w folderze
    Documents

``cmake --build . --target <nazwa modułu>``
    Budowanie konkretnego modułu w projekcie razerm z wszystkimi jego
    zależnościami

``../bin/<nazwa modułu> --gtest_filter=<test fixture>*``
    Uruchomienie testów z konkretnego modułu pasujących do filtra

Valgrind
********************************************************************************
``valgrind --leak-check=yes --track-origins=yes <program>``
    Podstawowe wywołanie valgrinda. Na razie wystarcza :)

CTest
********************************************************************************
``GTEST_COLOR=1 ctest --output-on-failure``
    Uruchomienie wszystkich testów z wypisaniem tych, które nie przeszły.
    GTEST_COLOR wymagane do tego, żeby poprawnie kolorować output gtesta
