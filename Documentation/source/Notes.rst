Notatki
===============================================================================
Notatki, plany na przyszłość, rzeczy do przemyślenia itp.

.. toctree::

   Notes/Notes-archive

Wersjonowanie bazy danych
*******************************************************************************
    Początkowo zakładałem, że stworzę klasę, która będzie tworzyć czystą bazę
    danych. Problem w tym, że planuję uzywać tej aplikacji w takcie jej
    rowzijania i tu pojawia się problem przenoszenia moich danych do nowej
    wersji. Do przemyślenia system upgrade lub przenoszenia danych między
    różnymi wersjami baz danych.

Nowy system połączenia do bazy danych
*******************************************************************************
Obecny system jest wzorowany na jakimś borlandowym badziewiu. Sama klasa bazy
danych i tworzenie wywoływanie zapytań jest ok. Problemem jest zwracanie wyniku
zapytania. Obecnie korzystam z klasy dataset która ma wewnętrzny iterator i
sama zarządza tym, który wiersz zapytania aktualnie zwraca. Docelowo chciałbym,
żeby to działało z zakresową pętlą for np **for (auto const& row: dataset){}**

Typy danych, które musi uwzględniać nowa klasa dataset
 *  typy podstawowe - int, float, bool
 *  std::string
 *  time_t do zapisu i odczytu daty

Polecenie init i plik konfiguracyjny
*******************************************************************************
Propozycja zmian do inicjowania i używania pliku konfiguracyjnego:

Init:
 *  Podczas tworzenia nowej bazy sprawdzanie, czy plik z taką nazwą już
    istnieje. Jeśli tak to pytanie czy nadpisać (aktualnie używany plik
    powinien zostać nadpisany z inną nazwą np: <name>-old<number>.db)
 *  Po utworzeniu bazy danych pytanie, czy ta baza ma być domyślną. Jeśli tak
    to nadpisywanie ustawienia pliku konfiguracyjnego (lub tworzenie nowego)
 *  Polecenie init powinno dopisywać ustawienia bazy do już istniejącego pliku
    zamiast całkowicie go nadpisywać

Wybór bazy danych
 *  Po inicjalizacji programu próba odczytu pliku konfiguracyjnego z katalogu,
    w którym znajduje się plik \*.exe
 *  Po udanym odczytaniu pliku sprawdzenie czy plik istnieje przed próbą
    otwarcia (w klasie Db::Database)
 *  W przypadku błędu odpowiedni komunikat, jeśli wszystko jest ok zapis do
    logu programu, która baza i kiedy była otwarta
 *  polecenie -database=<filename> do opcjonalnego przekazywania bazy danych

Polecenie settings do ustawiania konfiguracji programu

Dao
*******************************************************************************
Obecnie DaoFactory zwraca unique_ptr, zamiast tego mógłby zwracać shared_ptr.
Dodatkowo zamist tworzyć dao za każdym pobraniem, fabryka mogłaby przechowywać
wskaźnik na utworzoną wcześniej klasę i zwracać wskaźnik do niej tak, żeby w
całym projekcie była dokładnie jedna klasa dao danego typu.

Będzie to odczuwalne w działaniu programu dopiero wtedy kiedy dodam możliwość
wykonywania wielu komend za jednym uruchomieniem programu

Dodatkowo uprościłoby to kod testów. Zamiast tworzenia surowych wskaźników,
można tworzyć shared_ptr na dao mock i za pomocą tego rejestrować mocki do
fabryki

Rejestrowanie dao (zwykłych, nie mock) można bardzo uprościć tworząc metdodkę
template (albo lambda template :) ). Być może w tym momencie udałoby się dodać
validację na typ dao za pomocą type_traits (np. is_base_of czy jakoś tak)

Notatki nt sqlite
*******************************************************************************
SQLite nie obsługuje komendy merge

Log debugowy
*******************************************************************************
Potrzebny będzie log debugowy, który pozwoli na wyświetlenie różnych danych
podczas pracy programu.

Potrzebne opcje:
 *  Możliwość włączenia, wyłączenia logu w pliku tekstowym
 *  Określenie poziomów logowania - CLI (parsowanie polecenia), SQL (zapytania,
    parametry i błędy bazy danych), pozostałe
 *  Określenie gdzie mają być zapisywane dane (plik, konsola, baza danych)
 *  Logowanie czasu

Uwagi
 *  Dostęp z dowolnego miejsca w kodzie - zmienna globalna zamiast singletona
 *  Dwie metody - setLoggerConfig() - log()
 *  Docelowo globalne parametry pozwalające na zmianę konfiguracji logowania z
    wiersza poleceń

CLI parser
*******************************************************************************
Potrzebne będą nowe zmiany do parsera wiersza poleceń:
 *  Walidacja czy wprowadzone parametry są poprawne - chodzi o sprawdzenie czy
    użytkownik podał poprawne nazwy parametrów - czy wszystkie wymagane dane są
    wypełnione i czy nie ma niczego nadmiarowego
 *  Globalne parametry (nazwa bazy danych, informacje o logowaniu itp)
 *  Poprawione pobieranie danych z wyniku parsowania (klasy parser result)
 *  Sprawdzanie czy filtr jest cyfrą :)

Podpowiadanie składni
*******************************************************************************
Dobrze byłoby, gdyby program podowiadał składnie - autouzupełnianie komendy
i parametrów
