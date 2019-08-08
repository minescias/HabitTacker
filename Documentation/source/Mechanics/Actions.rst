Akcje
================================================================================

Akcje odpowiadają poleceniom z command line. Każdemu poleceniu typu add, edit
towarzyszy jedna akcja, która realizuje dane polecenie.

Rejestrowanie, wywoływanie akcji
********************************************************************************
Akcje można podzielić z grubsza na dwie grupy: zwykłe i specjalne.

Zwykłe akcje
--------------------------------------------------------------------------------

Zwykłe akcje to akcje typu add, edit, list, które wymagają połączenia do
istniejącej bazy danych i wykonują jakieś operacje na danych.

Akcje te są rejestrowane do specjalnego rejestru i uruchamiane za jego pomocą
bazując na komendzie wpisanej przez użytkownika.

Każda akcja powinna dziedziczyć z interfejsu IAction i implementować zawarte
w nim metody. Wykonanie akcji powinno najpierw sprawdzić poprawność poleceń
z command line, potem poprawność danych w bazie i na koniec wykonać zadaną
operację

.. code-block:: c
   :caption: Rejetrowanie akcji

    actionRegister->reg("add", []()->std::unique_ptr<Actions::IAction>
        {return std::make_unique<Actions::AddAction>();});

Akcje są rejestrowne za pomocą lambd tworzących dany obiekt. Dzięki temu akcja
jest tworzona tylko w momencie użycia

Zarejestrowaną akcję można pobrać za pomocą metody get. Przykład:

.. code-block:: c
   :caption: Pobieranie i wywołanie akcji

    auto action = actionRegister->get(commandName);
    action->setDaoFactory(daoFactory.get());
    action->execute(parserResult);

Akcje specjalne
--------------------------------------------------------------------------------
Nie wszystkie akcje wymagają działania wg opisu powyżej. Przykładowo akcja
``help`` i ``version`` wypisuje tylko tekst na ekranie, dlatego nie jest
potrzebne połączenie do bazy danych. Dlatego też wywołanie tych akcji
sprawdzane jest na samym początku działania programu

Innym przykładem akcji specjalnej jest init. Akcja ta tworzy nową bazę danych,
dlatego trzeba sprawdzić czy ta akcja nie została wykonana jeszcze przed
połączeniem z bazą danych.

Zwracanie wyników - action error
********************************************************************************
Generalnie akcje nie powinny niczego zwracać. Wynik działania jest zapisywany
do bazy lub wyświetlany na ekranie (albo jedno i drugie). Jednak w przypadku
błędu akcja powinna rzucić wyjątkiem typu ``Actions::ActionError`` z treścią
błędy. 
