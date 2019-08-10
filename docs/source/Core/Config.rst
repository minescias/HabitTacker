Config
===============================================================================
Opis klas używanych do obsługi pliku konfiguracyjnego

Klasa Settings
*******************************************************************************
Cała klasa to tak na prawdę obudowana mapa z nazwy atrybutu na wartość z
dodanym zabezpieczeniem przed pobraniem niestniejącego atrybutu.

Przed użyciem należy zarejestrować wszystkie cechy które mają być używane.
Rejestracja osbywa się za pomocą map<string,string>. W mapie powinny się
znajdować nazwa atrubutu i domyślna wartość. Przykład rejestracji:

.. code-block:: c

    auto settings = std::make_unique<Config::Settings>();
    settings->registerSettings(Config::SettingsMap{{"database", ""}});

Klasa ConfigFile
*******************************************************************************
Klasa, która służy do odczytu konfiguracji z pliku. Wymaga podania nazwy pliku
i zainicjowanej klasy settings. Nie jest właścicielem klasy Settings, tylko
wypełnia go danymi odczytanymi z pliku
