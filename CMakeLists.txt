cmake_minimum_required(VERSION 3.27)
project(TTypeRestructured)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_executable(TTypeRestructured main.cpp
        TType.cpp
        TType.h
        nCursesConfig.cpp
        nCursesConfig.h
        Printer.cpp
        Printer.h
        Calculate.cpp
        Calculate.h)


# Link against the ncurses library
target_link_libraries(TTypeRestructured PRIVATE ${CURSES_LIBRARIES})