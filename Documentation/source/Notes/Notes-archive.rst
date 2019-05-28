Archiwum
===============================================================================
Notatki, które sie trochę zdeaktualizowały

**Cel wersji 0.1**
 *	Zakładanie nowej bazy
 *	Zadadanie nawyków typu boolowskiego
 *	Określanie czy nawyk wykonany - tylko w tym dniu
 *	Proste wyświetlanie wyników

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
