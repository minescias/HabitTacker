Notatki
===============================================================================
Notatki, plany na przyszłość, rzeczy do przemyślenia itp.

Wersjonowanie bazy danych
*******************************************************************************
    Początkowo zakładałem, że stworzę klasę, która będzie tworzyć czystą bazę
    danych. Problem w tym, że planuję uzywać tej aplikacji w takcie jej
    rowzijania i tu pojawia się problem przenoszenia moich danych do nowej
    wersji. Do przemyślenia system upgrade lub przenoszenia danych między
    różnymi wersjami baz danych.

Cross compilation
********************************************************************************
Dodałem funckję Core::getDemangledTypeName(), która bazuje na funkcji
dostępnej tylko w GCC. Jeśli kiedykowliek chciałbym przejść na inny kompilator
trzeba będzie ją zmienić. Nazwy zmiennych są zależne od kompilatora, więc
nawet jeśli poprawię działanie tak, żeby kompilowało się niezależnie od
kompilatora to mogę mieć problem z testami, które od tego zależą.

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

Log debugowy
*******************************************************************************
Sprawy, dotyczące logowania, których nie udało się zakończyć w poprzednim
zadaniu:

*  Logowanie miejsca logowania (jakkolwiek głupio to brzmi :) __FILE__ i
    __LINE__)
*  Logowanie czasu
*  Miejsce logowania - konsola lub plik (lub oba)

Jeśli do logowania jest przekazany np. string format to olbiczenia zostaną
wykonane niezależnie od tego, czy logowanie jest włączone czy nie :(

Kilka spraw zależnych od od innych zadanek
 * Możliwość ustawiania konfiguracji w pliku konfiguracyjnym
 * Kolowanie logu na inny kolor w konsoli
 * Konfiguracja logowania z wiersza poleceń

CLI parser
*******************************************************************************
Potrzebne będą nowe zmiany do parsera wiersza poleceń:
 *  Walidacja czy wprowadzone parametry są poprawne - chodzi o sprawdzenie czy
    użytkownik podał poprawne nazwy parametrów - czy wszystkie wymagane dane są
    wypełnione i czy nie ma niczego nadmiarowego
 *  Globalne parametry (nazwa bazy danych, informacje o logowaniu itp)
 *  Poprawione pobieranie danych z wyniku parsowania (klasy parser result)
 *  Sprawdzanie czy filtr jest cyfrą :)

Zarządzanie procesem budowania - luźne notatki
*******************************************************************************
Dostępne komendy:
 *  prepare - przygotowanie projektu do kompilacji, w tym:
     *  założenie wymaganych folderów
     *  sprawdzenie czy zostały pobrane odpowiednie biblioteki (gtest)
     *  pobranie odpowiednich bibliotek
     *  uruchomienie CMake
     *  sprawdzenie czy istnieje sphinx - jeśli nie warning, że budowanie
        dokumentacji nie będzie możliwe
 *  build - budowanie całego projektu

Obsługa locale
********************************************************************************
Do ustalenia kiedy i jak miałoby to działać

Reprezentacja daty w C++
*******************************************************************************
* https://en.cppreference.com/w/cpp/chrono
* https://en.cppreference.com/w/cpp/chrono/time_point
* https://github.com/HowardHinnant/date

Docelowo będę chciał skorzystać z biblioteki znajdującej się na stronie
https://github.com/HowardHinnant/date. Najpierw jednak chciałbym zrobić
uboższą wersję tej biblioteki i samemu sprawdzić jak to działa w C++

Przechowywanie daty:
    using Date = std::chrono::system_clock::time_point;

Użyłbym chrono do przechowywania daty i czasu ale większość fajnych
funkcjonalności jest dopiero od c++20...

