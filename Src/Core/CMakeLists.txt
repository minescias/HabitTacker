cmake_minimum_required(VERSION 3.0.2)
project(Core)

set(Database_src
    Database/Database.cpp
    Database/Dataset.cpp
    Database/Query.cpp
    Database/Parameters.cpp)

set(Utils_src
    Utils/Exceptions/LogicError.cpp
    Utils/Exceptions/RuntimeError.cpp
    Utils/Logger/Log.cpp
    Utils/Strings/Case.cpp
    Utils/Strings/Compare.cpp
    Utils/Strings/Replace.cpp
    Utils/Types/TypeNames.cpp)


add_library(${PROJECT_NAME}
    ${Database_src}
    ${Utils_src})

target_link_libraries(${PROJECT_NAME} SQLite)
