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

**Dao**
*******************************************************************************
Obecnie DaoFactory zwraca unique_ptr, zamiast tego mógłby zwracać shared_ptr.
Dodatkowo zamist tworzyć dao za każdym pobraniem, fabryka mogłaby przechowywać
wskaźnik na utworzoną wcześniej klasę i zwracać wskaźnik do niej tak, żeby w
całym projekcie była dokładnie jedna klasa dao danego typu.

Będzie to odczuwalne w działaniu programu dopiero wtedy kiedy dodam możliwość
wykonywania wielu komend za jednym uruchomieniem programu

Dodatkowo uprościłoby to kod testów. Zamiast tworzenia surowych wskaźników,
można tworzyć shared_ptr na dao mock i za pomocą tego rejestrować mocki do
fabryki

Rejestrowanie dao (zwykłych, nie mock) można bardzo uprościć tworząc metdodkę
template (albo lambda template :) ). Być może w tym momencie udałoby się dodać
validację na typ dao za pomocą type_traits (np. is_base_of czy jakoś tak)
