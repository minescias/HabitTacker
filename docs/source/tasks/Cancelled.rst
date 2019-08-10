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

Core
********************************************************************************
**[C04]** Poprawki po ostatnich zmianach w module bazy danych.
    Dodałem tam obługę time_t, ale nie robiłem żadnych testów na to. Przydałoby
    się je dodać - ponadto wydaje mi się, że można jakoś uporządkować te bieda
    template, które są w dataset -> stary dataset został usunięty więc to 
    zadanie jest już nieaktualne 

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
