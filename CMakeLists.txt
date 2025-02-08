cmake_minimum_required(VERSION 3.27)
project(TTypeRestructured)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
find_package(Threads)

# Include directories (Make headers accessible)
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# Collect all source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create the executable
add_executable(TTypeRestructured ${SRC_FILES})
# Link against the ncurses library
target_link_libraries(TTypeRestructured PRIVATE ${CURSES_LIBRARIES} Threads::Threads)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

