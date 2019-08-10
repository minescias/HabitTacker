Dao
===============================================================================
Dao są to obiekty służące do zapisu odczytu danych z bazy. Z założenia są to
jedyne obiekty, które mogą wykonywać zapytania do bazy danych.

Podstawowe założenia:
 *  Każde dao ma zdefiniowany interfejs
 *  Klasy Dao nie są tworzone bezpośrednio, zamiast tego są tworzone przez
    fabrykę
 *  Interfejs dao musi dziedziczyć z Dao::UnknownDao

Klasa DaoFactory
*******************************************************************************
Klasa, która zajmuje sie tworzeniem dao. Tworzy klasy typu dao w momencie
wywołania metody getDao(...) i zwraca je w postaci shared_ptr według ponizszych
reguł:

*  w danym momencie może istnieć tylko jedna instancja danego dao. W przypadku
   gdy gdzieś w programie istnieje dao stworzone przez fabrykę, próba
   stworzenia dao w innym miejscu zwróci wskaźnik do już istniejącego dao
*  Nieużywane dao zostaje zniszczone. Próba pobrania dao stworzy nową instancję
   klasy

Wszystkie dao przed użyciem muszą zostać zarejestrowane.

.. code-block:: c
   :caption: Rejestrowanie dao do fabryki

   daoFactory->registerDao("habitDefinition", [](Db::Database* db){
      return std::make_unique<Dao::HabitDefinitionDao>(db);});

.. code-block:: c
   :caption: Tworzenie dao z użyciem DaoFactory

   auto dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

Testy
*******************************************************************************

Testy Dao
-------------------------------------------------------------------------------
Przed rozpoczęciem testu należy utworzyć nową testową bazę danych za pomocą
databaseCreatora. Powinny zostać utworzone tylko te tabele, z których dao
korzysta podczas testów.

Każde zapytanie powino zostać przetestowane w osobnym teście. Jeśli
przygotowanie danych testowych i jest zbyt skomplikowane można pominąć
sprawdzanie wyniku i zostawić samo uruchamianie zapytania

Testy z użyciem dao
-------------------------------------------------------------------------------
Testy klas, które korzystają z dao odbywają się z użyciem mocków dao. Mocki
każdego dao są zdefiniowane w osobnym folderze Mocks

Mock dao rejestruje się tak jak każde inne dao. Wystarczy zarejestrować mocka
dao z taką nazwą jak dao używane w testowanej klasie

.. code-block:: c
   :caption: Rejestrowanie mocka dao do fabryki

   factory->registerDao("daoName", [](Db::Database* db) -> Dao::UnknownDaoPtr
      {return std::make_shared<Dao::DaoMock>(db);});

Po zarestrowaniu należy pobrać mocka. Jest to niemal identyczne z pobieraniem
zwykłego dao, tylko zamiast interfejsu należy przekazać pełną klasę mocka.
Na tak pobranym dao ustawiamy jakie funkcje powinny zostać wywołane.
UWAGA: Mock dao musi istnieć przez cały czas trwania testu, inaczej zostanie
usunięty zanim zostanie użyty przez testowaną klasę, dlatego najlepiej jest
przechowywać mocka jako pole w klasie fixture

.. code-block:: c
   :caption: Pobieranie mocka dao z fabryki

   daoMock =  factory->createDao<Dao::DaoMock>("daoName");

Ponieważ bardzo często będzie potrzeba zarejestrowania i pobrania dao dodano
funkcję ``registerAndGetDaoMock``, która pozwala na wykonanie powyższych
czynności w jednym poleceniu

.. code-block:: c
   :caption: Przykład użycia registerAndGetDaoMock

   daoMock = registerAndGetDaoMock<Mocks::HabitDefinitionDaoMock>(
      &factory, "habitDefinition");
