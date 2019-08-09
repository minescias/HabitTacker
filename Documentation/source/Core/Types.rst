Typy zmiennych
================================================================================
W tym folderze znajdują się (będą znajdować) wszystkie funckje związane
z typami. W tym momencie jest to tylko pobieranie pełnej nazwy typu.
W przyszłości planuję dodać tutaj m.in funckje pomocnicze dla type_traits jak
np. isOptional() lub isAction()

**void getDemangledTypeName()**
    Funkcja zwracająca pełną nazwę zmiennej przekazaną jako argument template.
    Korzysta wewnętrznie z abi gcc, dlatego działa tylko na tym kompilatorze.
    Nie rozwija aliasów, tylko zwraca pierwotne typy.
