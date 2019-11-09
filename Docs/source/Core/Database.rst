Bazy danych
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

   Db::Query query(database.get(), getDefinitionaSql());
   auto result = query.execute();

Wykonanie zapytania z przekazaniem parametrów.
-------------------------------------------------------------------------------

.. code-block:: cpp

    Db::Query query(db, sql);
    query.setParam(":name", entity.getName());
    auto result = query.execute();

Ustawienie nieistniejącego parametru lub nieustawienie istniejącego spowoduje
rzuceniem wyjątku logic error

Wykonanie zapytania, które nie zwraca wyniku
--------------------------------------------------------------------------------
W przypadku zapytania, które nie zwraca wyniku (np. insert albo update) można
skorzystać z metody Query::executeCommand(). Podczas wywołania tej metody nie
jest tworzony dataset. Ponadto funkjca sprawdzi, czy zapytanie na pewno niczego
nie zwróciło. Przykład:

.. code-block:: cpp

   Db::Query query(database.get(), getInsertDefinitionSql());
   query.executeCommand();

Pobieranie wyniku zapytania - 1 wiersz
-------------------------------------------------------------------------------

.. code-block:: cpp

    Db::Query query(db, sql);
    query.setParam(":id", definitionId);
    auto dataset = query.execute();

    if (dataset.empty())
        return HabitDefinitionEntityPtr();

    auto row = dataset.getFirstRow()
    auto result = std::make_unique<HabitDefinitionEntity>();
    result->setId(row->get<int>("id"));
    result->setName(row->get<std::string>("name"));

UWAGA: W przypadku, gdy pobieramy tylko pierwszy wiersz to funkcja zwróci
wskaźnik na wiersz a nie referencję jak ma to miejsce w przypadku iteratorów.

Pobieranie wyniku zapytania - iterowanie po datasecie
-------------------------------------------------------------------------------
.. code-block:: cpp

    Db::Query query(db, sql);
    auto dataset = query.execute();

    for (const auto& row: dataset)
    {
        result.emplace_back(std::make_unique<Entity::HabitDefinitionEntity>());
        result.back()->setId(row.get<int>("id"));
        result.back()->setName(row.get<std::string>("name"));
    }

Do iterowania po wynikach zapytania można skorzystać z zakresowej pętli for.
Iteratory będą zwracały referencję do kolejnych wierszy.
