cmake_minimum_required(VERSION 3.27.7)

project(project)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(./ ./headers)

add_executable(main main.cpp)

add_library(headers cpp/board.cpp cpp/cell.cpp cpp/constants.cpp cpp/ship.cpp cpp/player.cpp cpp/playerstate.cpp cpp/symbol.cpp)

target_link_libraries(main sfml-graphics sfml-window sfml-system headers)

# add_compile_options(-Wall -Wextra -pedantic -Werror -fdiagnostics-color=always)


