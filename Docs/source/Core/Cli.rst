Cli
###############################################################################

W folderze Cli znajdują się klasy, które pozwalają na pracę z wierszem poleceń,
w tym odczyt i validacja danych wprowadzonych przez użytkownika.

Wstęp, informacje ogólne
********************************************************************************

**Podstawowa sładnia wiersza poleceń**

``htr <filter> <command name> <default parameter> <optional parameters>``

Gdzie:

**filter**
    Niektóre akcje mogą zostać wykonane na jednym lub wielu obiektach. Filtr
    pozwala na określenie, którego obiektu dotyczy akcja.

**command name**
    Polecenie (akcja) wykonywana przez użytkownika.

**default parameter**
    Domyślny parametr (choć może lepiej byłoby nazwać go głównym). Jest to
    parametr, który nie wymaga podawania nazwy z myślnikiem na początku.
    Powinien to być często używany parametr ścisle związany z danym poleceniem,
    np. nazwa pliku w poleceniu tworzącym pliki.

**optional parameters**
    Opcjonalne parametry np. nazwa bazy danych. Jest to wszystko to co znajduje
    się za poleceniem command i zaczyna od myślnika. Parametry mogą mieć postać
    flag (np. -<flag name>), które przekazują wartość boolowską lub parametrów
    (-<name>=<value>), w którym można przekazać jakąś wartość.

Przykład:
    **htr command foo -bar -bar2 -par=one -par2=two**, gdzie:
     *  htr - nazwa programu
     *  command - nazwa komendy
     *  foo - parametr domyślny (bez myślnika)
     *  -bar, -bar2 - flagi (przechowują tylko wartość typu bool)
     *  -par, -par2 - parametry (one, two - wartości tych parametóww

Współpraca między klasami Cli
================================================================================
#.  Parametry przekazane przez użytkownika są przekazyne do klasy
    ``CommandLineParser``, gdzie jest sprawdzana poprawność składni.
#.  Wynik parsowania jest zapisywany do klasy Parameters. Klasa ta jest
    przekazywana do klasy akcji wywołanej przez użytkownika.
#.  W klasie używającej parametrów (akcji) powinien znajdować się uprzednio
    zdefiniowany Validator, w którym są określone wszystkie dostępne parametry.
#.  Validator porównuje zapisane dane z tymi przekazanymi przez użytkownika.
#.  Po poprawnej walidacji parametów te mogą być użyte dalej w programie.

Opis klas
********************************************************************************

Klasa CommandLineParser
================================================================================
Klasa sprawdzająca poprawność wprowadzonych danych pod względem składniowym.
Sprawdzane jest przede wszystkim, czy parametry są poprawnie przypisanie oraz
czy nie na danych, których nie można przypisać do jakiegoś fragmentu
podstawowej składni (każdy element musi być gdzieś przypisany).

Klasa nie sprawdza natomiast czy to, co wpisał uzytkownik ma jakikolwiek sens,
czy wpisane parametry istnieją itp.

.. code-block:: c
   :caption: Przykład użycia

    auto parametes = Cli::CommandLineParser().parse(argc, argv);

Wynik zapytania jest zapisywany do klasy ``Parameters``

Klasa Parameters
================================================================================
Klasa z wynikami parsowania wiersza poleceń. Zapisywane są wszystkie dane jakie
udało się wyciągnąć z wiersza poleceń, w tym nazwa polecenia, argumenty, filtr
itp. Klasa ta pozwala na wygodniejsze przekazywanie i używanie parametrów
wiersza poleceń

Klasa to prosty kontener na wszystkie ww. dane. Każdy element polecenia ma
metody do zapisu i odczytu. Wszystkie wartości są przechowywane w formie
tekstowej

Klasa Validator
================================================================================
Klasa służąca do sprawdzania, czy parametry przekazane przez użytkownika są
zgodne z tym czego oczekuje program.

Validator jest przewidziany do używania przed rozpoczęciem wykonywania akcji.
Przed użyciem należy stworzyć validator i zarejestrować w nim wszystkie
informacje o paramerach, które mają zostać sprawdzane.

.. code-block:: c
   :caption: Tworzenie i użycie validatora

    auto validator = Cli::Validator();                      // utworzenie nowego walidatora
    validator.addFilter();                                  // włączenie filtra
    validator.addParam("foo");                              // dodanie opcjonalnej flagi foo
    validator.validate(parameters);                         // uruchomienie walidacji

Walidator pozwala na ustawienie trzech rodzajów elementów:
 *  **filtr** - domyślnie wyłączony. Po użyciu metody ``addFilter()`` staje się
    opcjonalny
 *  **parametr domyślny** - domyślnie wyłączony. Po użyciu metody
    ``addDefaultParameter()`` staje się opcjonalny
 *  **pozostałe parametry** - dodawane za pomocą metody ``addParam()``.
    Parametry dodane w ten sposób są typu opcjonalne i mają typ bool.

Wszystkie metody zaczynające się do add... zwracają referencję klasy
``ParamProperties``, w której można ustalić szczegóły jak dany parametr ma być
sprawdzany.

Klasa ParamProperties
================================================================================
Określa szczegóły walidacji parametru. Dostępne metody:
 *  ``requirement()`` - stopnień wymagalności parametru
 *  ``type()`` - typ parametru (bool, int) używane tylko w zwykłych parametrach
 *  ``errorMessage()`` - wiadomość, która ma zostać wyświetlona w przypadku
    błędu. Używana tylko w parametrze domyślnym ze względu na to, że
    parametr ten bardzo zależy od kontekstu w jakim jest używany

Każda z ww. metod zwraca referencję na samą siebie, co pozwala na ustawienie
wszystkich parametrów w jednym poleceniu.

.. code-block:: c
   :caption: Definiowane parametru

    auto validator = Cli::Validator();
    validator.addParam("foo")
        .type(Cli::ParamType::Date)
        .requirement(Cli::RequirementLevel::Required);
