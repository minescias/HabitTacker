Log
================================================================================
Log debugowy to mechanizm, który pozwala na zapisanie przebioegu działania
programu.

Konfiguracja
********************************************************************************

.. code-block:: c
   :caption: Inicjowanie klasy logującej

    auto logConfig = std::make_unique<Log::Config>();
    logConfig->enabled = true;
    logConfig->levels = {Log::Levels::Error, Log::Levels::Sql};

    auto logger = std::make_unique<Log::Logger>(std::move(logConfig));

Przed utworzeniem loggera trzeba utworzyć konfigurację logowania. Można w niej
określić czy logowanie ma być włączone i co ma być logowane.
Następnie można utworzyć obiekt loggera.

.. code-block:: c
   :caption: Ustawienie globalnego loggera

    // ustawienie globalnego loggera
    Log::setLogger(logger.get());

    // logowanie za pomocą globalnego obiektu
    log("jakiś tekst do zalogowania");

Logger może być ustawiony jako globalny za pomocą metody Log::SetLogger().
Logowanie za pomocą tego obiektu jest możliwe za pomocą funkcji
log(std::string).

Globalnie dostępny jest tylko wskaźnik na klasę loggera, natiomiast sama klasa
log jest przechowywana w innym miejscu (na przykład w funckji main). Pozwala to
na dowolną konfigurację, lub wyłączenie logowania w testach.

Poziomy logowania
********************************************************************************
Możliwe jest określenie poziomu logowania. Aktualnie dotępne poziomy
 *  common - log wspólny, domyślny, jeśli nie podano żadnego
 *  sql - logowanie wszystkiego co jest związane z bazami danych
 *  error - logowanie treści wyjątków

Każdy poziom jest dostępny niezależnie od innych. Oznacza to, że można włączyć
logowanie tylko zapytań sql.

Poziom logowania jest podawany jako drugi parametr funkcji logującej. Np:

.. code-block:: c
   :caption: Logowanie z przekazaniem poziomu

    log("Wykonywanie zapytania: 'select ...'", Log::Levels::Sql);

Zapisywanie logu
********************************************************************************
W tym momencie możliwe jest tylko wyśiwetlenie logu w konsoli. Docelowo będzie
możliwość zapisu do pliku lub bazy danych
