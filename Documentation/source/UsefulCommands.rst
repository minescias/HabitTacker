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
    zaleźnościami
