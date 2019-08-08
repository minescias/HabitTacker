Data i czas
===============================================================================
Różne notatki dotyczące przechowywania daty i czasu w bazie danych i kodzie C++

Dt::Timestamp
*******************************************************************************
Jest to nic innego jak alias na std::time_t. Jest używany do przechowywania
daty w encjach oraz do przekazywania daty/czasu między funkcjmi, do zapytań
itp.

Klasa Dt::DateTime
*******************************************************************************
Klasa reprezentująca datę i czas. Nie powinna być używana do przechowywania dat
(do tego służy Dt::Timestamp). Klasa powinna być używana raczej do operacji na
datach takich jak tworzenie daty z stringa, konwersja do stringa.

Odejmowanie dwóch klas typu Dt::DateTime skutkuje powstaniem klasy Dt::Duration

Dt::Duration
*******************************************************************************
Klasa reprezentuje różnicę w czasie między dwoma datami. Pozwala na pobranie
liczby dni.

Klasa docelowo będzie używana tam, gdzie będzie potrzebna różnica między dwoma
czasami.

Wszystkie metody klasy będą zwracały wartość całkowitą zaokrągloną w dół. Np.
przy różnicy 5,5 dnia funkcja getDays zwróci 5

Funkcja Dt::getCurrentDate()
*******************************************************************************
Zwraca aktualną datę (lokalną z komputera na którym jest uruchomiony program)
a formacie unixowym (Dt::Timestamp) zaokrągloną do jednego dnia.

Funkcja Dt::getCurrentDateShiftByDays(int nrOfDays)
*******************************************************************************
Funckja zwraca unixową datę przesuniętą o n dni od dzisiaj

Reprezentacja daty w bazie danych
*******************************************************************************
Data będzie przechowywana w kolumnach o typie **Date** jako czas unixowy

Z dokumentacji:
    INTEGER as Unix Time, the number of seconds since 1970-01-01 00:00:00 UTC.

W zapytaniach będzie można wyświetlić datę w ludzkim formacie np. za pomocą
**SELECT date('now');**
