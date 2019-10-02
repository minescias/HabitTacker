cmake_minimum_required(VERSION 3.0.2)
project(HtCli)

set(HT_Actions_src
	Actions/ActionError.cpp
	Actions/ActionRegister.cpp
	Actions/AddAction.cpp
	Actions/BaseAction.cpp
	Actions/DefaultAction.cpp
	Actions/DoneAction.cpp
	Actions/EditAction.cpp
	Actions/InitAction.cpp
	Actions/ListAction.cpp)

set(HT_src
    AppInit.cpp
    AppInit/GetSettings.cpp
    AppInit/Help.cpp
    AppInit/InitDaoFactory.cpp
    AppInit/RegisterActions.cpp
    AppInit/Version.cpp
)

# system dependent libraries
if (UNIX)
    set(SysDependencies stdc++fs)
endif()

add_library(${PROJECT_NAME} ${HT_src} ${HT_Actions_src})
target_link_libraries(${PROJECT_NAME} ${SysDependencies} Core HT)
