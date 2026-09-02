cmake_minimum_required(VERSION 3.16)
project(sbu-euro VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/embedFiglet)

add_library(sbu_core src/sbu.cpp)
target_include_directories(sbu_core PUBLIC src)

add_executable(sbu-euro src/main.cpp)
target_link_libraries(sbu-euro PRIVATE sbu_core embedFiglet::embedFiglet)

enable_testing()
add_executable(test_sbu tests/test_main.cpp)
target_link_libraries(test_sbu PRIVATE sbu_core)
add_test(NAME sbu_tests COMMAND test_sbu)
