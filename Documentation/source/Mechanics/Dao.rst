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
wywołania metody getDao(...) i zwraca je w postaci unique_ptr. W  Wszystkie dao
przed użyciem muszą zostać zarejestrowane.

Rejestrowanie dao do fabryki

.. code-block:: c

   daoFactory->registerDao("habitDefinition", [](Db::Database* db){
      return std::make_unique<Dao::HabitDefinitionDao>(db);});

Tworzenie dao z użyciem DaoFactory

.. code-block:: c

   auto dao = daoFactory->createDao<Dao::IHabitDefinitionDao>("habitDefinition");

Testy
*******************************************************************************

Testy Dao
-------------------------------------------------------------------------------
Przed rozpoczęciem testu utworzyć nową testową bazę danych za pomocą
databaseCreatora. Powinny zostać utworzone tylko te tabele, z których dao
korzysta podczas testów.

Każde zapytanie powino zostać przetestowane w osobnym teście. Jeśli
przygotowanie danych testowych i jest zbyt skomplikowane można pominąć
sprawdzanie wyniku i zostawić samo uruchamianie zapytania


Testy z użyciem dao
-------------------------------------------------------------------------------
Testy klas, które korzystają z dao odbywają się z użyciem mocków dao. Mocki
każdego dao są zdefiniowane w osobnym folderze Mocks

Ponieważ z założenia wszystkie dao są tworzone przez fabrykę trzeba
zarejestrować mocka dao do fabryki zamiast zwykłego dao i taką fabrykę
przekazać do testowanego obiektu. Do rejestrowania służy metoda createDaoMock.

Rejestrowanie mocka dao do fabryki

.. code-block:: c

   // rejestrowanie mocka dao
   definitionDaoMock = new Mocks::HabitDefinitionDaoMock();
   daoFactory.registerDao("habitDefinition", createDaoMock(definitionDaoMock));

   // kod testu
   EXPECT_CALL(*definitionDaoMock, getDefinitions())
      .WillOnce(Return(ByMove(getHabitDefinitions())));

   // pole klasy fixture
   Mocks::HabitDaoMock* habitDaoMock;

Rejestracja odbywa się przez raw pointer, nie ma sekcji delete, ponieważ w
momencie pobierania dao z fabryki przez testowaną mock jest pakowany do
uniqie_ptr
