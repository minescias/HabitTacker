Lista wykonanych zadań
===============================================================================

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania itp

**[B01]** Budowanie dokumentacji razem z projektem za pomocą polecenia make
    Tak, żeby i kod i dokumentacja były budowane za pomocą jednego polecenia

**[B02]** Budowanie dokumentacji jako osobny target CMake
    Celem jest możliwość zbudowania dokumentacji z
    a pomocą polecenia np.
    "make doc" z folderu, w którym są normalnie budowane pliki cpp

**[B05]** Sprawdzić czy program wciąż się kompiluje na Linuskie po moich
    ostatnich zmianach w Windowsie

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C03]** Dodanie DateTime do Core programu
 *  OK typedef na time_t
 *  OK klasa datetime obsługująca datę i czas
 *  OK funkja pobierająca dzisiejszą datę

**[C07]** Końcowe porządki z datą i czasem - szczegóły w notatkach
 *  OK Możliwość dodawania/odejmowania dni od daty
 *  OK Pobieranie dnia tygodnia z daty
 *  OK Klasa Duration do reprezentowania różnicy między dwoma datami

**[C08]** Jakaś metoda to łatwiejszego pobietrania unixowej daty przesuniętej o
    n dni

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D01]** Działanie aktualnego systemu zapytań do bazy danych

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT01]** Polecenie init
 *  OK Dodanie modułu main (ht.exe)
 *  OK Dodanie modułu HT (ht.dll)
 *  OK Funkcja AppInit w module HT
 *  OK Podstawowe wywołanie programu
 *  OK Klasa parsera polecenia CLI
 *  OK Klasa akcji polecenia init
 *  OK Parsowanie polecenia init <filename> bez funkcjonalności - tylko
    komunikat o sukcesie
 *  OK Opis pocelenia w dokumentacji

**[HT02]** Kreator pustej bazy danych
 *  OK Klasa do tworzenia pustej bazy danych "Database Creator"
 *  OK Tworzenie tabeli "habit_definition"
 *  OK Tworzenie tabel na polecenie init
 *  OK Sprawdzanie czy plik już istnieje
 *  OK Odporność na błędne parametry (system wyjątków akcji)
 *  OK Opis tabeli w dokumentacji

 **[HT03]** Polecenie Help
 *  OK Parsowanie polecenia Help
 *  OK Wyświetlanie pomocy

 **[HT04]** Dodawanie nawyków
 *  OK Encja tabeli habit_definition
 *  OK Dao do wspomnianej wyżej tabeli (interfejs i testy)
 *  OK Polecenie "add", która pozwala na dodawanie nawyków

**[HT05]** Wyświetlanie listy nawyków
 *  OK Nowa funkcja w dao: getDefinitions + testy
 *  OK Przeniesienie mock dao do wspólnego miejsca
 *  OK Polecenie list, które pozwala na wyświetlanie listy nawyków
 *  OK Aktualizacja dokumentacji Cli

**[HT06]** Dodanie tabeli z realizacją nawyków
 *  OK Nowa tabela "habit" w klasie database creator
 *  OK Opis tabeli w dokumentacji

**[HT07]** Możliwość wypełniania nawyków
 *  OK Encja tabeli habit
 *  OK Dao tabeli habit (interfejs i testy)
 *  OK Polecenie "done" do ustawiania dzisiejszej wartości nawyku
 *  OK Zabezpieczenie przed próbą ustawieniem już wypełnionego nawyku
 *  OK Zabezpieczenie przed próbą ustawienia nieustniejącego nawyku
 *  OK Rozszerzenie command line parsera o filtr prosty i włączenie opcji done
    w appInit()
 *  OK Sprawdzanie przez akcję, czy jest wypełniony filtr
 *  OK Aktualizacja dokumentacji Cli

**[HT08]** Konfiguracja programu - domyślna baza danych
 *  OK Klasa Settings do przechowywania ustawień użytkownika
 *  OK Klasa ConfigFile do obsługi pliku konfiguracyjnego
 *  Init action zakłada domyślny plik konfiguracyjny
     * OK w kalatlogu, w którtym był uruchomiony program (workong directorry)
     * w katalogu, w którym jest plik wykonywalny
     * w katalogu domowym użytkownika
 *  OK Używanie konfiguracji z pliku do połączenia z bazą danych
 *  OK Opis pliku konfiguracyjnego w dokumentacji

**[HT09]** Zmiana nazwy programu, aktualna nazwa koliduje z poleceniem linuksa
 *  OK Tytuł dokumentacji
 *  OK Dokumentacja Cli
 *  OK Help message
 *  OK Akcja list i default - komenda przy pustej bazie danych

**[HT11]** Wyświetlanie wypełniania statusów z ostatnich 14 dni
 *  OK Nowa akcja - default
 *  OK Wyświetlanie listy nawyków
 *  OK Wyświetlanie nagłówka dni tygodnia (Ostatni dzień na dzisiaj)
 *  OK Wyświetlanie tabeli wypełnionych nawyków
 *  OK Dodanie akcji do appInit()
 *  OK Aktualizacja dokumentacji cli
 *  OK Zabezpieczenie przed pustą bazą

**[HT12]** usunąć z tabeli habit kolumnę result. Na razie nie jest ona
    potrzebna. Wpisy do tej tabeli będą oznaczały, że zadanie na dany dzień
    zostało wykonane a brak wpisu to brak niewykonane zadanie

**[HT13]** Interfejs akcji
 *  OK Uspójnione przekazywanie dao i innych danych wymaganych do działania
 *  OK Uspójnione przekazywanie sparsowanych danych z wiersza poleceń
 *  OK Usunięcie akcji help na rzecz zwykłej funkcji lub dodanie nowej akcji
    Version tak, żeby cała obsługa akcji była spójna
 *  OK Rejestrowanie akcji i iterowanie po dostępnych akcjach zamiast serii
    else if

**[HT14]** Mechanizm tworzenia Dao - DaoFactory
 *  OK Klasa dao facory
 *  OK Rejestrowanie akcji (funkcja tworząca dao?)
 *  OK Wywołanie zarejestrowanej akcji
 *  OK Rejestrowanie mocków dao zamiast normalnych na czas testów
 *  OK Zabezpieczenie przed błędnym użyciem, podwójna rejestracja, użycie
    niezarejestrowanego dao itp
 *  OK Opis działania DaoFactory i testów z jego użyciem po zakończeniu
    powyższych
 *  Odrzucone - Zabezpieczenie przed próbą zarejetrowania czegoś, czego nie da
    się skonwertować do Dao::UnknownDao
 *  OK Przekazywanie bazy danych do nowo utworzonego dao

**[HT15]** Zaawansowany parser command line
 *  OK Klasa wyniku działania parsera - filtr , komenda i argumenty dodatkowe
 *  OK Pobieranie prostego polecenia
 *  OK Pobieranie polecenia z argumentami
 *  OK Pobieranie polecenia z filtrem
 *  Opis działania całości w dokumentacji

**[HT16]** Oznaczanie od kiedy dany nawyk obowiązuje (data dodania)
 *  OK Rozszerzenie tabeli, encji i dao
 *  OK Uwzględnienie tego podczas wyświetlania listy wypełnionych nawyków

**[HT19]** Jeśli nazwa nawyku kończy się polską literą to tabela z
    wypełnieniem jest przesunięta o jeden znak w lewo :)

**[HT21]** Możliwość resetowania
 *  OK Rozszerzenie command line parsera tak, żeby przekazywać opcjonalne
    parametry z nazwą - składnia -<nazwa>
 *  OK Opis powyższego w dokumentacji
 *  OK Rozszerzenie dao o usuwanie wpisów z tabeli habit + testy
 *  OK Dodanie opcji -reset do akcji done - usuwanie wpisu za dzisiaj + testy
    dodanie opisu do dokumentacji

**[HT22] v0.2** Możliwość podawania dnia w opcjonalnych parametrach
 *  OK Rozszerzenie command line parsera tak, żeby przekazywać opcjonalne
    parametry z nazwą i wartością - składnia -<nazwa>=<wartość> (bez spacji)
 *  OK Dodanie opcji -date=<day> do komendy done
 *  OK Parser przetwarzający datę z parametru na datę wpisaną do bazy danych
 *  OK Przetwarzanie daty formatu DD-MM-YYYY na timestamp
 *  OK Zabezpieczenie przed dodaniem daty w przyszłości lub daty przed
    rozpoczęciem nawyku
 *  OK Dokumentacja

**[HT23]** Polecenie edit do poprawiania definicji
 *  OK Nowa komenda edit
 *  OK Polecenie update/merge do dao definicji
 *  OK Dbsługa filtru, parametru name
 *  OK Dokumentacja

**[HT24]** Wygodniejsze pobieranie wartości z klasy ParserResult
 *  OK testy na tę klasę
 *  OK pobieranie filtra
 *  OK pobieranie domyślnego parametru
 *  OK pobieranie flagi
 *  OK pobieranie wartości parametru
 *  OK zamiana użycia na nowe w akcjach i parserze command line
 *  OK usunięcie starych wywołań

**[Ht25] v0.2** Poprawki w działaniu AddAction
 *  OK AddAction pozwala na przekazanie pustej nazwy
 *  OK AddAction nie sprawdza czy nawyk o takiej nazwie już istnieje

**[HT26]** Nowe DaoFactory
 *  OK Zwracanie shared_ptr przez daoFactory
 *  OK Dao factory wewnętrzenie przechowuje weak_ptr do przechowywania dao
 *  OK Jeśli dao zostało wcześniej utworzone to będzie zwracane istniejące
    zamiast tworzenia nowego
 *  OK Jeśli wszystkie instance dao zostaną zniszczone, zniszczona zostanie
    kopia w dao
 *  OK Zamiana kodu tak, żeby korzystał z nowego factory
 *  OK Poprawa testów
 *  OK Aktualizacja dokumentacji
 *  OK Prawdobodobnie metoda createDaoMock stanie się zbędna i można ją usunąć

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Przerobić database creatora na buildera, który będzie zwracał połączenie
    handlera do nowo utworzonej bazy danych
 *  W przypadku, gdy użytkownik poda błędną nazwę akcji program wysypie się
    wyjątkiem, który nie jest nigdzie przechwytywany
 *  Czy metody w Dao mogą być constowe (czy przekazywanie DB nie przeszkadza w
    tym. Jeśli tak to zamienić
 *  ActionError powinno być w namespace Actions

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

**[T01]** Generator plików
 *  OK pliki \*.cpp i \*.h
 *  OK pliki CMakeLists.txt

**[T04]** VSCode - Osobne ustawienia dla plików \*.rst - spacje zamiast tabów
