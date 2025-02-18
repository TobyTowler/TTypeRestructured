cmake_minimum_required(VERSION 3.27)
project(TType)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
find_package(Threads)

# Include directories (Make headers accessible)
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# Collect all source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create the executable
add_executable(TType ${SRC_FILES})
# Link against the ncurses library
target_link_libraries(TType PRIVATE ${CURSES_LIBRARIES} Threads::Threads)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Install to /usr/local/bin (Linux/macOS) or C:\Program Files (Windows)
install(TARGETS TType DESTINATION /usr/local/bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/text/ DESTINATION /usr/local/share/TType/text FILES_MATCHING PATTERN "*")
