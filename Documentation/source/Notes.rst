Notatki
===============================================================================
Notatki, plany na przyszłość, rzeczy do przemyślenia itp.

**Cel wersji 0.1**
 *	Zakładanie nowej bazy
 *	Zadadanie nawyków typu boolowskiego
 *	Określanie czy nawyk wykonany - tylko w tym dniu
 *	Proste wyświetlanie wyników

**Wersjonowanie bazy danych**
    Początkowo zakładałem, że stworzę klasę, która będzie tworzyć czystą bazę
    danych. Problem w tym, że planuję uzywać tej aplikacji w takcie jej
    rowzijania i tu pojawia się problem przenoszenia moich danych do nowej
    wersji. Do przemyślenia system upgrade lub przenoszenia danych między
    różnymi wersjami baz danych.

**Nowy system połączenia do bazy danych**
*******************************************************************************
Obecny system jest wzorowany na jakimś borlandowym badziewiu. Sama klasa bazy
danych i tworzenie wywoływanie zapytań jest ok. Problemem jest zwracanie wyniku
zapytania. Obecnie korzystam z klasy dataset która ma wewnętrzny iterator i
sama zarządza tym, który wiersz zapytania aktualnie zwraca. Docelowo chciałbym,
żeby to działało z zakresową pętlą for np **for (auto const& row: dataset){}**

Typy danych, które musi uwzględniać nowa klasa dataset
 *  typy podstawowe - int, float, bool
 *  std::string
 *  time_t do zapisu i odczytu daty

**Porządki z datami**
*******************************************************************************
*   DefaultActionTest.cpp - tworzenie daty starym sposobem i tworzenie daty na
    poszczególne dni przez odejmowanie ilości sekund w dniach
*   Podobnie w pliku HabitDaoTests.cpp
*   W DefaultAction::getWeekDaysHeaderEndingWithDate pobieranie dnia tygodnia
    za pomocą time_t. Dodać odpowiednią metodę do DateTime i zamienić
*   W DefaultAction::fillCompletionTable odejmowanie od siebie unixowych dat
    i dzielenie tego przez ilość sekund w dniu. Dodać nową klasę Duration,
    która będzie wynikiem odejmowania dwóch dat i pobieranie różnicy w dniach
    z tej klasy
*   HabitDao::getHabitsFromLastTwoWeeks - znowu różnica w dniach prez
    odejmowanie dat unixowych
