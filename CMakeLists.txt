cmake_minimum_required(VERSION 3.10)

project(jklm)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(jklm "jklm.cpp" "game.cpp" "Database/database.cpp" "Dictionary/dictionaryapi.cpp" "Dictionary/dictionaryapi.h" "helpers.cpp" "helpers.h"   "Database/databasestructure.cpp" "Database/databasestructure.h")

target_link_libraries(jklm PRIVATE fmt::fmt)
target_link_libraries(jklm PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(jklm PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(jklm PRIVATE cpr::cpr)