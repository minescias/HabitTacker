cmake_minimum_required(VERSION 3.0.2)
project(Core)

set(Config_src
    Config/ConfigFile.cpp
    Config/Settings.cpp)

set(Datetime_src
    DateTime/DateLiteral.cpp
    DateTime/DateTime.cpp
    DateTime/DateTimeGetter.cpp
    DateTime/Duration.cpp)

set(Database_src
	Database/Database.cpp
	Database/Dataset.cpp
	Database/Parameters.cpp
	Database/Query.cpp
	Database/Row.cpp
	Database/ValueGetter.cpp)

set(Logger_src
	Logger/Log.cpp
	Logger/Logger.cpp)

set(Strings_src
	Strings/Case.cpp
	Strings/Compare.cpp
	Strings/Replace.cpp)

set(Utils_src
    Exceptions/LogicError.cpp
    Exceptions/RuntimeError.cpp
    Types/TypeNames.cpp)

add_library(${PROJECT_NAME}
    ${Config_src}
    ${Datetime_src}
    ${Database_src}
    ${Logger_src}
    ${Strings_src}
    ${Utils_src})

target_link_libraries(${PROJECT_NAME} SQLite)
