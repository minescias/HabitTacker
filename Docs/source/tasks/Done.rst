Lista wykonanych zadań
===============================================================================

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania itp

**[B01]** Budowanie dokumentacji razem z projektem za pomocą polecenia make
    Tak, żeby i kod i dokumentacja były budowane za pomocą jednego polecenia

**[B02]** Budowanie dokumentacji jako osobny target CMake
    Celem jest możliwość zbudowania dokumentacji za pomocą polecenia np.
    "make doc" z folderu, w którym są normalnie budowane pliki cpp

**[B03]** Budowanie jednego modułu
    Dostępna jest opcja cmake --build . --target <nazwa modułu> ale to buduje
    wszystkie moduły, od których zależy ten, który chcemy zbudować (chociaż
    może to i lepiej?

**[B05]** Sprawdzić czy program wciąż się kompiluje na Linuskie po moich
    ostatnich zmianach w Windowsie

**[B08]** Włączenie wszystkich warningów w gcc tak jak są domyślne w MSVC

**[B09]** Uruchomić Valgrinda albo inny program do sprawdzania wycieków pamięci

**[B13]** Usunięcie wszystkich warningów kompilacji po włączeniu dodatkowych
opcji kompilatora (-Wall, -pedantic)

**[B16]** Uruchomienie testów za pomocą CTest

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C01]** Nowy system zapytań do bazy danych.
 *  Klasa field reprezentująca jedno pole - klasa ta pownna zajmować się
    rzutowaniem wyników na typ, jakiego oczekuje użytkownik
 *  Klasa row/record - wektor pól z dostępem po nazwie kolumny
 *  Klasa Dataset - zestaw pól - powinna obdługiwać zakresowe pętle for
 *  Polecenie execute() i executeCommand() w klasie Query. Jedno powinno
    zwracać dataset a drugie nie
 *  Zamiana starych zapytań na nowe
 *  Opis działania w dokumentacji

**[C02]** Usunięcie folderu utils i Trzymanie wszystkiego bezpośrednio w Core

**[C03]** Dodanie DateTime do Core programu
 *  OK typedef na time_t
 *  OK klasa datetime obsługująca datę i czas
 *  OK funkja pobierająca dzisiejszą datę

**[C05]** Funkcja do składania tekstu na wzór boost::format. Mogłaby
    wykorzystywać string literals ()_xx

**[C06]** Funkcja do pobierania nazwy klasy + poprawić komunikat błędu w teście
    DaoFactoryTests::throwsLogicErrorWhenTryingToCastDaoToWrongType
    // https://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object

**[C07]** Końcowe porządki z datą i czasem - szczegóły w notatkach
 *  OK Możliwość dodawania/odejmowania dni od daty
 *  OK Pobieranie dnia tygodnia z daty
 *  OK Klasa Duration do reprezentowania różnicy między dwoma datami

**[C08]** Jakaś metoda to łatwiejszego pobietrania unixowej daty przesuniętej o
    n dni

**[C09]** Zaawansowany mechanizm logujący zmiany
 *  OK Globalny obiekt do logowania
 *  OK Flagi/enum do oznaczania co ma być logowane (na początek będą potrzebne:
    SQL, wywoływanie alcji i zwykły log debugowy
 *  OK Logowanie danych w zależności od tego na jakim poziomie są logowane

**[C11]** Poprawki w klasie Dataset - zakończenie zmian związanych z db
 *  OK Zmienić nazwę metody z isEmpty() na empty()
 *  OK Zmienić nazwę metody z isInitialized() na initialized()
 *  XX Metoda isInitialized chyba nie ma żadnego sensu. Jeśli zapytanie nie
    zwraca żadnych wierszy to nie zwraca też listy kolumn, dlatego nigdy nie
    dojdzie do sytuacji, że dataset jest initialized i empty. Sprawdzić i jeśli
    tak jest faktycznie usunąć metodę isInitialized >> lista kolumn jest
    zwracana nawet, jeśli zapytanie nic nie wybierze.
 *  XX Metoda getFirstRow() jest problematyczna. Zwraca wskaźnik na Row, sam
    Row nie może istnieć bez dataseta, dlatego nie można użyć konstrukcji
    *auto row = query.execute().getFirstRow().* Do rozważenia czy getFirstRow
    nie powinien zwracać klasy innej od Row ale mającej bte same działanie. >>
    Przed wybraniem jednego wiersza i tak, trzeba sprawdzać czy zapytanie coś
    zwróciło, więc to rozwiązanie nie będzie zbyt uzyteczne
 *  OK Jeśli wszystko będzie OK usunąć starą metodę execute() i dataset.
    Następnie usunąć "2" z nazw nowych metod i klas.
 *  OK Zaktualizować opis w dokumentacji

**[C12]** Przenieść dao factory do core
Mechanizm dao nie realizuje żadnej logiki związanej z nawykami więc może warto
przenieść go do Core. Mechanizm podoba mi się na tyle, że może użyję go w czymś
innym

**[C13]** Poprawki w CommandLineParser
 *  Przenieść, całość do core, CLP nie realizuje żadnej logiki związanej
    z nawykami
 *  Zmienić nazwę z Cli::Parameters na Cli::Parameters
 *  Przykłady pobierania parametrów w dokumentacji
 *  Ustawiwanie domyślnych wartości mogłoby być constexpr :)

**[C15]** Wprowadzenie nowego formatu daty i czasu (w tym momencie są używane
 *  Na początek wystarczy jedynie obsługa dat (nie używam czasu, jeszcze)
 *  Zapis/odczyt z bazy danych
 *  Odczyt danych z linii poleceń
 *  Pobieranie aktualnej daty

**[C17]** Obsługa std::optional w zapytaniach sql (powiązane trochę z C14)
 *  OK Możliwość zapisywania nullowej wartości do bazy
 *  OK Zapis optionala do bazy (null jeśli niezainicjowany, w przeciwnym
    wypadku wartość
 *  OK Odczyt nulla z bazy - wyjątek jeśli następuje próba przepisania nullowej
    wartości do nie-optionala
 *  OK Odczyt nulla z bazy - nullopt jeśli zapis do optionala
 *  OK Odczyt wartości do optionala


Docs
*******************************************************************************
Lista rzeczy do opisania

**[D01]** Działanie aktualnego systemu zapytań do bazy danych

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D05]** Opis działania odczytu i walidacji parametrów z wiersza poleceń
    Po zakończeniu zadania HT30

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

**[HT18]** Klasa BaseAction w której byłaby podstawowa implementacja akcji.
 *  Blokowane przez [HT27]
 *  Przeniesienie metody setDaoFactory do klasy bazowej.
 *  Pobieranie dao z fabryki w momencie użycia a nie w metodzie setDaoFactory
 *  Wywoływanie sprawdzania poprwaności danych w klasie bazowej (uzupełnianie
    jakie to dane będzie w klasach pochodnych

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

**[HT27]** Walidacja poprawności danych wprowadzonych przez użytkownika
 *  Blokowane przez [HT24]
 *  Nowa klasa walidatora + testy
 *  Walidacja poprawności filtra (tylko sprawdzanie czy wymagany i czy cyfra)
 *  Walidacja poprawności flag
 *  Walidacja poprawności parametrów
 *  Dokumentacja

**[HT30]** Poprawki po dodaniu walidatora:
 *  OK Sprawdzanie czy domyślny parametr jest wymagany
 *  OK w momencie dodania walidatora rozdział parametrów na parametry i flagi
    straci chyba rację bytu. Wcześniej zostało to dodane, żeby nie było
    problemu z sprawdzaniem odpowiedniego typu podczas pobierania wartości.
    Po zmianach sprawdzaniem typu zajmie się walidator, więc wszystko może
    siedzieć w jednej strukturze
 *  OK Enum do okreslenia poziomnu wymagalności
 *  OK Refaktor, przeniesienie całości do odpowiednich folderów

**[HT31]** Możliwość dodawania nawyków liczbowych
 *  OK Nowa tabela *Requirements*, w której będą znajdowały się wszystkie
    wymagania dotyczące nawyku. Wymagania mogą się zmieniać w czasie, dlatego
    nie można ich zapisać w tabeli habitDefinition
 *  OK Encja i dao do nowej kolumny
 *  OK Możliwość dodawania celu w trakcie dodawania nawyku - domyślnie 1, ale
    można nadpisać dowolną wartością

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Przerobić database creatora na buildera, który będzie zwracał połączenie
    handlera do nowo utworzonej bazy danych
 *  W przypadku, gdy użytkownik poda błędną nazwę akcji program wysypie się
    wyjątkiem, który nie jest nigdzie przechwytywany
 *  Czy metody w Dao mogą być constowe (czy przekazywanie DB nie przeszkadza w
    tym. Jeśli tak to zamienić
 *  ActionError powinno być w namespace Actions

Lib
********************************************************************************
**[Lib2]** Sprawdzić czy i jak mogę użyć biblioteki
    https://github.com/HowardHinnant/date do zarządzania datami. Docelowo moje
    funkcje obsługujące czas są do wywalenia albo do zamiany na wrapper do ww
    biblioteki

**[Lib4]** Biblioteka do formatowania stringa

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże

**[T01]** Generator plików
 *  OK pliki \*.cpp i \*.h
 *  OK pliki CMakeLists.txt

**[T04]** VSCode - Osobne ustawienia dla plików \*.rst - spacje zamiast tabów
