Lista anulowanych zadań
===============================================================================

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
