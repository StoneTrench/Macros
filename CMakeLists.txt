cmake_minimum_required(VERSION 3.31)
project(
    Macros
    VERSION 1.0
    LANGUAGES CXX
)

# Set output directories for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(MacrosBinary src/main.cpp)

# Install target and runtime dependencies
install(TARGETS MacrosBinary RUNTIME DESTINATION .)
