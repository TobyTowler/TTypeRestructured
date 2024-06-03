cmake_minimum_required(VERSION 3.27)
project(TTypeRestructured)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
find_package(Threads)

add_executable(TTypeRestructured src/main.cpp
        src/TType.cpp
        src/include/TType.h
        src/nCursesConfig.cpp
        src/include/nCursesConfig.h
        src/Printer.cpp
        src/include/Printer.h
        src/include/Colours.h
        )

# Link against the ncurses library
target_link_libraries(TTypeRestructured PRIVATE ${CURSES_LIBRARIES} Threads::Threads)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

