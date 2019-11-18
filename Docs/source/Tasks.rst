Lista zadań
===============================================================================

.. toctree::
   :maxdepth: 19
   :caption: Spis treści:

   tasks/Done
   tasks/Cancelled
   tasks/Planned
   tasks/Notes
   tasks/Cpp

Build system
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania oraz
różnymi zeznętrznymi narzędziami, które może warto sprawdzić

**[B07]** W przypadku błędu działanie programu często kończy się komunikatem
    Segmnetation fault (Core dumped) - sprawdzić co to za core i co można z
    tego wyciągnąć

**[B10]** Sprawdzić co to jest profiler i jak można tego użyć

**[B11]** Pobieranie bibliotek z githuba przez CMake. Podobno jest to możliwe

**[B12]** Automatycznie tworznie folderu na dane testowe przy uruchomieniu
testów. Narazie działa to tak, że jeśli jest tworzone nowe repo albo testy są
uruchamiane z nowego folderu to cała operacja zakończy się błędem mówiącym, że
nie można utworzyć bazy testowej.

**[B15]** Plik compile_commands.json tworzy sie w katalogu, z którego jest
budowany projekt. W moim przypadku jest to folder build. Ccls wymaga, żeby plik
ten był tworzony w katalogu głównym żeby np. poprawnie odczytywać ścieżki
include. Sprawdzić na ile możliwe jest tworzenie tego pliku w katalogu głównym.
Ostatecznie będzie potrzebny skrypt, który po kompilacji przeniesie ten plik
w odpowiednie miejsce

**[B17]** Użycie target_include_directory i target_link_directories

**[B18]** Aktualizacja clanga i/lub clang formata do najnowszych wersji

Core
*******************************************************************************
Co trzeba dodać/poprawić w Core programu

**[C10]** Poprawiony plik konfiguracyjny
 *  wybrać format pliku (xml,json, yaml lub coś innego)
 *  klasa do odczytu zawartości pliku konfiguracyjnego
 *  zapis pliku konfiguracyjnego w katalogu domowym użytkownika - tak, żeby był
    dostępny z każdej lokalizacji (~/config/ht)
 *  ustawienie dot. bazy danych
 *  ustawienie dot. konfiguracji logowania

**[C16]** Poprawki po wprowadzeniu nowego formatu daty
 *  Funkcja do porównywania dat uwzględniająca to, że daty mogą być
    niezainicjowane/błędne (.ok() == false)
 *  Pobieranie dnia tygodnia z daty
 *  Odejmowanie dat

**[C17]** Dodać obsługę string_view w mechaniźmie zapytań do bazy danych

**[C18]** Rozszerzyć interfejs bazy danych o zwracanie ID ostatnio dodanego
    wiersza https://www.sqlite.org/c3ref/last_insert_rowid.html

**[C19]** Rozszerzyć interfejs baz danych o zapytania zwracające jeden wiersza
 *  dodać metodę selectSingleRow() do klasy Query, któa będzie wykonywała
    zapytanie i zwracała pierwszy wiersz
 *  W przypadku, gdy zapytanie zwróci więcej niż jeden wiersz powinien polecieć
    odpowiedni wyjątek
 *  Klasa Row nie może istnieć bez klasy dataset, należy dodać nową klasę
    (dziedziczącą z Row lub mającą ten sam interfejs) która będzie niezależna
    od datasetu (kopiuje wszystkie istotne informacje do wewnątrz siebie).

Docs
*******************************************************************************
Lista rzeczy do opisania

**[D03]** Dodawanie nowego polecenia - wszystko co trzeba uwzględnić

**[D04]** Struktura pliku CMake (ze względu na narzędzia parsujące)

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT20]** Poprawiona konfiguracja programu
 *  Odczyt pliku konfiguracyjnego z globalnej lokalizacji
 *  W wersji testowej odczyt z hardkodowanego folderu
 *  Nowa stronka - różnice między wersją testową a stabilną - co trzeba
    sprawdzać przy generowaniu
 *  Konfiguracja logowania przekazywana w pliku konfiguracyjnym
 *  Polecenie 'settings' wyświetlające aktualne ustawienia - wynikowe suma
    domyślnych i z pliku konfiguracyjnego

**[HT28]** Wywołanie domyślnej komendy (i prawdopodobue każdej innej) przy
    braku bazy skutkuje wywaleniem błędu LogicError. Trzeba dodać sprawdzanie
    czy baza istnieje przed uruchomieniem jakiejkolwiej operacji na bazie
    danych

**[HT29]** Poprawki w help message
 *  Poprawić czytelność i błędy w ogólnym help message
 *  Każda akcja powinna obsługiwać polecenie --help (funkcja w klasie bazowej)

**[HT32]** Wypełnianie nawyków liczbowych
 *  Nowa kolumna w tabeli habit do wpisywania celu za dany dzień
 *  Rozszerzenie dao i encji o nową kolumnę
 *  Nowy parametr do akcji done określający stopień wypełnienia nawyku
 *  Domyślnie jeśli nie podano ilości jest wpisywana wartość celu

**[HT33]** Wyświetlanie wypełnienia nawyków w tabeli
 *  Wyświetlanie celu w tabeli wyników (nowa kolumna)
 *  Wyświetlanie przybliżonego procentu wykonania (za pomocą znaków unicode)

**[HT34]** Z jakiegoś powodu działa wyświetlanie nagłówka w tabelce (choć nie
    powinno) W trakcie zamiany Timestamp na Date wpisałem tam jakąś wartość na
    sztywno

**[HT35]** Gui: Odczyt listy ostatnich baz danych z pliku konfiguracyjnego
    Niemożliwe do zrealizowania do czasu zakończenia prac nad nowym plikiem
    konfiguracyjnym

**[HT36]** Gui: Otwieranie istniejącej bazy danych z listy ostatnio otwieranych
    baz. Do obsłużenia opcje dwukliku na liście i przycisk "Open". Ostatnio
    otwarta baza danych powinna zostać przeniesiona na początek listy

**[HT37]** Gui: Otwieranie istniejącej bazy za pomocą przyciku "Browse" +
    dopisanie do ostatnio otwartych baz danych

**[HT38]** Gui: Tworzenie nowej bazy za pomocą przycisku "Create". Nowo postała
    baza danych jest dopisywna do listy ostatnio otwarych baz

**[HT39]** Inserty do bazy danych muszą zwracać id dodanej encji. Bez tego
    testy działają na założeniu, że dodana encja będzie miała zawsze ten sam id

**[HT40]** Edycja nawyku: możliwość zmniany celu
 *  funkcja/klasa do zarządzania celami - w module HT.
    Powinna obsługiwać wyłączenie aktualnego celu i dodanie nowego
 *  Dodanie nowej opcji w poleceniu edit

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Pozbyć się słowa Entity w nazwie klasy encji - sam namespace na to wskazuje

Lib
********************************************************************************
Wszystko co dotyczy zewnętrznych bibliotek używanych w moim projekcie

**[Lib1]** Biblioteka ICU - rozpoznanie, czy i jak mogę jej użyć w moim
    projekcie do poprawnego wyświetlania tekstu na konsoli

**[Lib3]** Biblioteka do obsługi formatu JSON lub XML do zapisu/odczytu pliku
    konfiguracyjnego

**[Lib5]** Dodatkowe testy biblioteki Sqlite
 *  Chodzi o sprawdzenie, jak zachowuje się bibliteka w nietypowych sytuacjach
 *  Odczyt kolumny typu int do stringa,
 *  Próba zapisanaia wartości wykraczającej poza zakres kolumny (przekroczenie
    rozmiaru inta i długości tekstu)

Tools
*******************************************************************************
Lista narzędzi do zrobienia, lista poprawek do już istniejących narzędzi lub
konfiguracji tychże. W tym rozdziale są brane pod uwagę tylko te narzędzia,
które sam napisałem lub napiszę w przyszłości

**[T02]** Generator tabel do systemu rst/sphinx

**[T03]** Generator encji

**[T05]** Konwerter sql/cppsql

**[T09]** Narzędź, który zmieni camesCase na podkreślniki

**[T10]** Zarządzanie plikami CMake
 *  OK Dodawanie plików do CMake
 *  OK Pytanie o dodanie pliku do CMake po utworzeniu za pomocą gen
 *  OK Walidacja, czy dany plik jest już dodany
 *  Walidacja rozszerzenia, podpowiadanie tylko plików .cpp po wciśnięciu Tab
 *  Tworzenie nowych grup
 *  Usuwanie plików z kompilacji

**[T12]** Automatyczne dodanie testu do podczas tworzenia nowego pliku wklei
    całą ścieżkę do pliku w nazwie klasy :D
