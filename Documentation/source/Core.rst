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

Wykonanie zapytania z przekazaniem parametrów
-------------------------------------------------------------------------------

.. code-block:: cpp

    Db::Query query(db, sql);
    query.setParam(":name", entity.getName());
    query.execute();

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
