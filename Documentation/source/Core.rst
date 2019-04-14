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

