add_executable(HtCliTests
    Actions/ActionRegisterTests.cpp
    Actions/AddActionTests.cpp
    Actions/DefaultActionTests.cpp
    Actions/DoneActionTests.cpp
    Actions/EditActionTests.cpp
    Actions/InitActionTests.cpp
    Actions/ListActionTests.cpp
    main.cpp
)

target_link_libraries(HtCliTests
    Core
    date_interface
    gmock
    gtest
    Ht
    HtCli
    pthread
    stdc++fs
    nlohmann_json
)

add_test(NAME HtCliTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND HtCliTests)