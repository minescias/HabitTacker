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
	Database/Dataset2.cpp
	Database/Parameters.cpp
	Database/Query.cpp
	Database/Row.cpp
	Database/ValueGetter.cpp)

set(Logger_src
	Logger/Log.cpp
	Logger/Logger.cpp)

set(Strings_src
	Utils/Strings/Case.cpp
	Utils/Strings/Compare.cpp
	Utils/Strings/Replace.cpp)

set(Utils_src
    Utils/Exceptions/LogicError.cpp
    Utils/Exceptions/RuntimeError.cpp
    Utils/Types/TypeNames.cpp)

add_library(${PROJECT_NAME}
    ${Config_src}
    ${Datetime_src}
    ${Database_src}
    ${Logger_src}
    ${Strings_src}
    ${Utils_src})

target_link_libraries(${PROJECT_NAME} SQLite)
