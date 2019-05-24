Plik konfiguracyjny
===============================================================================

Przykładowy plik konfiguracyjny:

.. code-block:: text

    # nazwa domyślnej bazy danych
    database=myDatabase.tdb

Linie rozpoczynające się od a'#' są komentarzem. Ustawienia są zapisywane w
formie <nazwa>=<wartość> (bez spacji)

Plik konfiguracyjny jest tworzony w podczas polecenia init, w katalogu
roboczym. Jeśli wcześniej istniał plik konfiguracyjny to zostanie nadpisany
