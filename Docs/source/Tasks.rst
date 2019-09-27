Lista zadań
===============================================================================

.. toctree::
   :maxdepth: 19
   :caption: Spis treści:

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

**[B10]** Sprawdzić co to jest profiler i jak można tego użyć

**[B11]** Pobieranie gtest z githuba przez CMake. Podobno jest to możliwe

**[B12]** Automatycznie tworznie folderu na dane testowe przy uruchomieniu
testów. Narazie działa to tak, że jeśli jest tworzone nowe repo albo testy są
uruchamiane z nowego folderu to cała operacja zakończy się błędem mówiącym, że
nie można utworzyć bazy testowej.

**[B14]** Wprowadzenie clang-formata - przygotowanie formatki pliku

**[B15]** Plik compile_commands.json tworzy sie w katalogu, z którego jest
budowany projekt. W moim przypadku jest to folder build. Ccls wymaga, żeby plik
ten był tworzony w katalogu głównym żeby np. poprawnie odczytywać ścieżki
include. Sprawdzić na ile możliwe jest tworzenie tego pliku w katalogu głównym.
Ostatecznie będzie potrzebny skrypt, który po kompilacji przeniesie ten plik
w odpowiednie miejsce

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

**[C14]** Castowanie wyników zapytania na odpowiednie typy za pomocą
type_traits.

**[C16]** Poprawki po wprowadzeniu nowego formatu daty
 *  Funkcja do porównywania dat uwzględniająca to, że daty mogą być
    niezainicjowane/błędne (.ok() == false)
 *  Pobieranie dnia tygodnia z daty
 *  Odejmowanie dat

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

**[HT31]** Możliwość dodawania nawyków liczbowych
 *  Nowa kolumna w tabeli habit_definition określająca cel na dany dzień
 *  Rozszerzenie dao i encji o nową kolumnę
 *  Możliwość dodawania celu w trakcie dodawania nawyku

**[HT32]** Wypełnianie nawyków liczbowych
 *  Nowa kolumna w tabeli habit do wpisywania celu za dany dzień
 *  Rozszerzenie dao i encji o nową kolumnę
 *  Nowy parametr do akcji done
 *  Określanie wykonania na podstawie porównania z definicją i wyświetlanie
    w tabeli

**[HT33]** Poprawione wyświetlanie nawyków z listy
 *  Wyświetlanie celu w tabeli wyników (nowa kolumna)
 *  Wyświetlanie przybliżonego procentu wykonania (za pomocą znaków unicode)

**[HT34]** Z jakiegoś powodu działa wyświetlanie nagłówka w tabelce (choć nie
powinno) W trakcie zamiany Timestamp na Date wpisałem tam jakąś wartość na
sztywno

**[HT99]** Refaktor i drobne poprawki - zadanie zbiorcze
 *  Pozbyć się słowa Entity w nazwie klasy encji - sam namespace na to wskazuje

Lib
********************************************************************************
Wszystko co dotyczy zewnętrznych bibliotek używanych w moim projekcie

**[Lib1]** Biblioteka ICU - rozpoznanie, czy i jak mogę jej użyć w moim
    projekcie do poprawnego wyświetlania tekstu na konsoli

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

**[T11]** Uruchamianie testów skrótem klawiszowym z poziomu visual studio code
 *  Kompilacja modułu z testami przed uruchomieniem + ew. zależności
 *  Uruchamianie wszystkich testów z modułu
 *  Wszystkie testy z pliku
 *  Jeden konkretny test
 *  Możliwość debugowania
