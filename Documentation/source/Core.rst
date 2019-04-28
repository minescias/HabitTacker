Core - Dokumentacja techniczna
===============================================================================

Database
*******************************************************************************

Podłączenie do bazy danych
-------------------------------------------------------------------------------

.. code-block:: cpp

   std::unique_ptr<Db::Database> database = std::make_unique<Db::Database>(filename);

W parametrze filename podajemy ścieżkę do pliku bazy danych. Po utworzeniu
obiektu klasa automatycznie łączy się do bazy, w przypadku braku pliku zostanie
utworzony automatycznie. Nie ma sprawdzania czy plik istnieje i czy baza jest w
ogóle poprawna.


Wykonanie prostego zapytania
-------------------------------------------------------------------------------

.. code-block:: cpp

   Db::Query query(database.get(), getCreateHabitDefinitionSql());
   query.execute();

Wykonanie zapytania z przekazaniem parametrów.
-------------------------------------------------------------------------------

.. code-block:: cpp

    Db::Query query(db, sql);
    query.setParam(":name", entity.getName());
    query.execute();

Ustawienie nieistniejącego parametru lub nieustawienie istniejącego spowoduje
rzuceniem wyjątku logic error

Pobieranie wyniku zapytania - 1 wiersz
-------------------------------------------------------------------------------

.. code-block:: cpp

    Db::Query query(db, sql);
    query.setParam(":id", definitionId);
    auto dataset = query.execute();

    if (dataset->empty())
        return HabitDefinitionEntityPtr();

    auto result = std::make_unique<HabitDefinitionEntity>();
    result->setId(dataset->getAs<int>("id"));
    result->setName(dataset->getAs<std::string>("name"));

Pobieranie wyniku zapytania - iterowanie po datasecie
-------------------------------------------------------------------------------
.. code-block:: cpp

    Db::Query query(db, sql);
    auto dataset = query.execute();

    while(dataset->next())
    {
        result.emplace_back(std::make_unique<Entity::HabitDefinitionEntity>());
        result.back()->setId(dataset->getAs<int>("id"));
        result.back()->setName(dataset->getAs<std::string>("name"));
    }

Wywołanie zapytania tak jak w poprzednim przykładzie. Różnicza polega na tym,
że zamykamy pobieranie wyników z bazy danych w pętli
**while(dataset->next())**. Dataset ma swój wewnętrzny iterator, który jest
przestawiany na następny wiersz przy poleceniu **next()**. Słabe, ale tak to
kiedyś zrobiłem i w działa w miarę dobrze...
