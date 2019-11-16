Lista anulowanych zadań
===============================================================================

Project
*******************************************************************************
Wszystko co jest związane z zarządzaniem projektem, systemem budowania oraz
różnymi zeznętrznymi narzędziami, które może warto sprawdzić

**[B04]** Udostępnianie klas między modułami - makro DLL_EXPORT
    Na tym etapie pracy jest to całkowicie niepotrzebne, zbędna praca, która
    nie da żadnego wymiernego rezultatu. Może później wrócę do zadania, jak
    projekt się trochę rozrośnie.

**[B06]** Podpięcie mojej dokumentacji do githuba - wydaje mi się, że  da się
    tak zrobić https://daler.github.io/sphinxdoc-test/includeme.html
    - gitbub nie obsługuje toctrees (przynajmniej wg. tego
    https://github.com/github/markup/issues/534), więc dam sobie z tym spokój,
    Przynajmnniej na razie

Core
********************************************************************************
**[C04]** Poprawki po ostatnich zmianach w module bazy danych.
    Dodałem tam obługę time_t, ale nie robiłem żadnych testów na to. Przydałoby
    się je dodać - ponadto wydaje mi się, że można jakoś uporządkować te bieda
    template, które są w dataset -> stary dataset został usunięty więc to
    zadanie jest już nieaktualne

**[C14]** Castowanie wyników zapytania na odpowiednie typy za pomocą
type_traits - chciałem zrobić jakiś super zaawansowany system do rzutowania
wyników, ale wystarczy to co jest teraz. Używam tt tylko dla optionali

HT
*******************************************************************************
Zadania dotyczące modułu HT

**[HT10]** Wydzielenie modułu HtDbTests, w której będą testy korzystające z
    bazy danych - testy dao. Chodzi o to, że testy te zajmują stosunkowo dużo
    czasu i generują sporo bałaganu w komunikatach przez log debugowy.
    Wyjaśnienie: Istnieje polecenie --gtest_filter, które pozwala na
    filtrowanie restów.

**[HT17]** Rejestrowanie mocków dao za pomocą unique_ptr zamiast raw pointerów.
    Opis błędu oraz próby jego rozwiązania są w plikach DaoFacoryTest.cpp
    i DaoMockCreator.h

Tools
********************************************************************************
**[T06]** W trakcie testów wyświetla się wszystko z cout na konsoli. Sprawdzić
    czy można to jakoś wyłączyć na czas testów. Przekierowanie couta?

**[T07]** Polecenie hmk do zarządzania budowaniem projektu. Opcje
 *  <default> - budowanie całego projektu
 *  clean - usunięcie wszystkich plików powstałych podczas budowania projektu
 *  prepare - uruchomienie "cmake .." w folderze builds
 *  docs - budowanie dokumentacji
 *  <module name> - budowanie tylko tego modułu

**[T08]** Polecenie tests do uruchamiania testów - załatwione przez CTest
 *  <default> uruchamianie wszystkich testów
 *  <module name> uruchamianie testów z jednego modułu

**[T11]** Uruchamianie testów skrótem klawiszowym z poziomu visual studio code
 *  !! Monżna to zrobić z poziomu VS Code za pomocą pliku tasks.json !!
 *  Kompilacja modułu z testami przed uruchomieniem + ew. zależności
 *  Uruchamianie wszystkich testów z modułu
 *  Wszystkie testy z pliku
 *  Jeden konkretny test
 *  Możliwość debugowania
