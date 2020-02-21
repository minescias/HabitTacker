add_executable(HtCliTests
    Commands/CommandRegisterTests.cpp
    Commands/AddCommandTests.cpp
    Commands/DefaultCommandTests.cpp
    Commands/DoneCommandTests.cpp
    Commands/EditCommandTests.cpp
    Commands/InitCommandTests.cpp
    Commands/ListCommandTests.cpp
    main.cpp
	Tools/CliTestTools.cpp
)

target_link_libraries(HtCliTests
    CLI11
    date_interface
    gmock
    gtest
    nlohmann_json
    pthread
    stdc++fs
    Core
    Ht
    HtCli
)

add_test(NAME HtCliTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND HtCliTests)