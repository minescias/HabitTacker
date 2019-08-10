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

**[C10]** Poprawiony plik konfiguracyjny
 *  wybrać format pliku (xml,json, yaml lub coś innego)
 *  klasa do odczytu zawartości pliku konfiguracyjnego
 *  zapis pliku konfiguracyjnego w katalogu domowym użytkownika - tak, żeby był
    dostępny z każdej lokalizacji
 *  ustawienie dot. bazy danych
 *  ustawienie dot. konfiguracji logowania


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
