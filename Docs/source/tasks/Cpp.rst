C++
===============================================================================
Różne notatki na temat c++ o których często zapominam

Throw by value, catch by reference (or by const&)
http://www.informit.com/articles/article.aspx?p=373339


Lista rzeczy do sprawdzenia
*******************************************************************************
#.  Dlaczego unique_ptr wymaga pełnych danych o klasie, dlaczego nie wystarczy
    sam forward?
#.  Czy intefejsy powinny mieć wirtualny destruktor
#.  stringview co to i jak to można użyć
#.  Kiedy używać wskaźników a kiedy referencji?
#.  Przekazywanie zmiennej przez refencje a tworzenie zmiennej w momencie
    wywołania funkcji
#.  Wołanie konstruktorów i metod klas bazowych
#.  Zwracanie klasy przez metody tej klasy (return \*this)
#.  Unique_ptr a płytka i głęboka kopia obiektu
#.  Czy dwie różne lambdy mające tę samą sygnaturę mają ten sam typ (mogą być
    zapisane w jednym kontenerze)
#.  Wykorzystanie is_same() albo czegoś podobnego do sprawdzenia jakiego typu
    jest interfejs
#.  Gdzieś wyczytałem, żeby używać enum class z typem (poszukać i sprawdzić
    czemu tak a nie inaczej)
#.  Używanie string_view z mapą, która przechowuje wewnętrznie stringa
    (raczej niemożliwe ze względu na dedukcje typów w template ale sprawdzić)
#.  Czy w momencie, gdy przekazuję obiekt przez referencję do kontruktora a
    zapisuję w klasie przez wartość następuje kopiowanie obiektu?
#.  RVO

Modern Cpp
********************************************************************************
1. string_view zamiast zwykłego stringa tam, gdzie to możliwe
