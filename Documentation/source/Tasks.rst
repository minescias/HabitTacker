Lista zadań
===============================================================================

.. toctree::

   tasks/Done
   tasks/Cancelled
   tasks/Planned
   tasks/Notes
   tasks/Notes-archive
   tasks/Cpp

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania oraz
różnymi zeznętrznymi narzędziami, które może warto sprawdzić

**[B06]** Podpięcie mojej dokumentacji do githuba - wydaje mi się, że  da się
    tak zrobić https://jefflirion.github.io/sphinx-github-pages.html
    https://daler.github.io/sphinxdoc-test/includeme.html

**[B07]** W przypadku błędu działanie programu często kończy się komunikatem
    Segmnetation fault (Core dumped) - sprawdzić co to za core i co można z
    tego wyciągnąć

**[B08]** Włączenie wszystkich warningów w gcc tak jak są domyślne w MSVC

**[B09]** Uruchomić Valgrinda albo inny program do sprawdzania wycieków pamięci

**[B10]** Sprawdzić co to jest profiler i jak można tego użyć\

**[B11]** Pobieranie gtest z githuba przez CMake. Podobno jest to możliwe

**[B12]** Automatycznie tworznie folderu na dane testowe przy uruchomieniu
testów. Narazie działa to tak, że jeśli jest tworzone nowe repo albo testy są
uruchamiane z nowego folderu to cała operacja zakończy się błędem mówiącym, że
nie można utworzyć bazy testowej.

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C02]** Usunięcie folderu utils i Trzymanie wszystkiego bezpośrednio w Core

**[C04]** Poprawki po ostatnich zmianach w module bazy danych.
    Dodałem tam obługę time_t, ale nie robiłem żadnych testów na to. Przydałoby
    się je dodać - ponadto wydaje mi się, że można jakoś uporządkować te bieda
    template, które są w dataset

**[C06]** Funkcja do pobierania nazwy klasy + poprawić komunikat błędu w teście
    DaoFactoryTests::throwsLogicErrorWhenTryingToCastDaoToWrongType
    // https://stackoverflow.com/questions/3649278/how-can-i-get-the-class-name-from-a-c-object

**[C09]** Zaawansowany mechanizm logujący zmiany
 *  OK Globalny obiekt do logowania
 *  OK Flagi/enum do oznaczania co ma być logowane (na początek będą potrzebne:
    SQL, wywoływanie alcji i zwykły log debugowy
 *  OK Logowanie danych w zależności od tego na jakim poziomie są logowane
 *  Logowanie miejsca logowania (jakkolwiek głupio to brzmi :) __FILE__ i
    __LINE__)
 *  Logowanie czasu
 *  Miejsce logowania - konsola lub plik (lub oba)
 *  Opis działania całości w dokumentacji

**[C10]** Poprawiony plik konfiguracyjny
 *  wybrać format pliku (xml,json, yaml lub coś innego)
 *  klasa do odczytu zawartości pliku konfiguracyjnego
 *  zapis pliku konfiguracyjnego w katalogu domowym użytkownika - tak, żeby był
    dostępny z każdej lokalizacji
 *  ustawienie dot. bazy danych
 *  ustawienie dot. konfiguracji logowania

**[C11]** Poprawki w klasie Dataset2 - zakończenie zmian związanych z db
 *  Zmienić nazwę metody z isEmpty() na empty()
 *  Zmienić nazwę metody z isInitialized() na initialized()
 *  Metoda isInitialized chyba nie ma żadnego sensu. Jeśli zapytanie nie zwraca
    żadnych wierszy to nie zwraca też listy kolumn, dlatego nigdy nie dojdzie
    do sytuacji, że dataset jest initialized i empty. Sprawdzić i jeśli tak
    jest faktycznie usunąć metodę isInitialized
 *  Metoda getFirstRow() jest problematyczna. Zwraca wskaźnik na Row, sam Row
    nie może istnieć bez dataseta, dlatego nie można użyć konstrukcji
    *auto row = query.execute().getFirstRow().* Do rozważenia czy getFirstRow
    nie powinien zwracać klasy innej od Row ale mającej te same działanie.
 *  Jeśli wszystko będzie OK usunąć starą metodę execute() i dataset. Następnie
    usunąć "2" z nazw nowych metod i klas.
 *  Zaktualizować opis w dokumentacji

**[C12]** Przenieść dao factory do core
Mechanizm dao nie realizuje żadnej logiki związanej z nawykami więc może warto
przenieść go do Core. Mechanizm podoba mi się na tyle, że możę użyję go w czymś
innym

**[C13]** Poprawki w CommandLineParser
 *  Przenieść, całość do core, CLP nie realizuje żadnej logiki związanej
    z nawykami
 *  Zmienić nazwę z Cli::ParserResult na Cli::Parameters
 *  Przykłady pobierania parametrów w dokumentacji
 *  Ustawiwanie domyślnych wartości mogłoby być constexpr :)

**[C14]** Castowanie wyników zapytania na odpowiednie typy za pomocą
type_traits.

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D02]** Opis akcji, wyjątku ActionError i w ogóle tego co się dzieje po
    podaniu polecenia. Do opisania po wyklarowaniu działania mechanizmu.

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

**[D04]** Struktura pliku CMake (ze względu na narzędzia parsujące)

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT18]** Klasa BaseAction w której byłaby podstawowa implementacja akcji.
 *  Blokowane przez [HT27]
 *  Przeniesienie metody setDaoFactory do klasy bazowej.
 *  Pobieranie dao z fabryki w momencie użycia a nie w metodzie setDaoFactory
 *  Wywoływanie sprawdzania poprwaności danych w klasie bazowej (uzupełnianie
    jakie to dane będzie w klasach pochodnych

**[HT20]** Polecenie Settings
 *  Domyślnie wyświetlana jest aktualna konfiguracja z pliku .rc
 *  Możliwość ustawiania wartości z pomocą polecenia
    **htr settings <name>:<value>**

**[HT27]** Walidacja poprawności danych wprowadzonych przez użytkownika
 *  Blokowane przez [HT24]
 *  Nowa klasa walidatora + testy
 *  Walidacja poprawności filtra (tylko sprawdzanie czy wymagany i czy cyfra)
 *  Walidacja poprawności flag
 *  Walidacja poprawności domyślnego parametru
 *  Walidacja poprawności parametrów
 *  Dokumentacja

**[HT28]** Wywołanie domyślnej komendy (i prawdopodobue każdej innej) przy
    braku bazy skutkuje wywaleniem błędu LogicError. Trzeba dodać sprawdzanie
    czy baza istnieje przed uruchomieniem jakiejkolwiek5 operacji na bazie
    danych

**[HT29]** Każda akcja powinna obsługiwać polecenie --help

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Pozbyć się słowa Entity w nazwie klasy encji - sam namespace na to wskazuje
 *  Help jest bardzo nieczytelny + zawiera literówki :)
 *  Dane testowe powinny być zapisywane w folderze testFiles lub testSamples
    albo najlepiej całkowicie usunięte po zakończeniu testów
 *  Podczas kompilacji całości projektu pojawiło się sporo warningów.
    Prawdopobnie po dodaniu flagi -Wall w pliku głównym CMake

Lib
********************************************************************************
Wszystko co dotyczy zewnętrznych bibliotek używanych w moim projekcie

**[Lib1]** Biblioteka ICU - rozpoznanie, czy i jak mogę jej użyć w moim
    projekcie do poprawnego wyświetlania tekstu na konsoli

**[Lib2]** Sprawdzić czy i jak mogę użyć biblioteki
    https://github.com/HowardHinnant/date do zarządzania datami. Docelowo moje
    funkcje obsługujące czas są do wywalenia albo do zamiany na wrapper do ww
    biblioteki

**[Lib3]** Biblioteka do obsługi formatu JSON lub XML do zapisu/odczytu pliku
    konfiguracyjnego

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże. W tym rozdziale są brane pod uwagę tylko te narzędzia,
które sam napisałem lub napiszę w przyszłości

**[T02]** Generator tabel do systemu rst/sphinx

**[T03]** Generator encji

**[T05]** Konwerter sql/cppsql

**[T06]** W trakcie testów wyświetla się wszystko z cout na konsoli. Sprawdzić
    czy można to jakoś wyłączyć na czas testów. Przekierowanie couta?

**[T07]** Polecenie hmk do zarządzania budowaniem projektu. Opcje
 *  <default> - budowanie całego projektu
 *  clean - usunięcie wszystkich plików powstałych podczas budowania projektu
 *  prepare - uruchomienie "cmake .." w folderze builds
 *  docs - budowanie dokumentacji
 *  <module name> - budowanie tylko tego modułu

**[T08]** Polecenie tests do uruchamiania testów
 *  <default> uruchamianie wszystkich testów
 *  <module name> uruchamianie testów z jednego modułu

**[T09]** Narzędź, który zmieni camesCase na podkreślniki

**[T10]** Zarządzanie plikami CMake
 *  OK Dodawanie plików do CMake
 *  Pytanie o dodanie pliku do CMake po utworzeniu za pomocą gen
 *  Walidacja, czy dany plik jest już dodany
 *  Walidacja rozszerzenia, podpowiadanie tylko plików .cpp po wciśnięciu Tab
 *  Tworzenie nowych grup
 *  Usuwanie plików z kompilacji
