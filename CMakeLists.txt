cmake_minimum_required(VERSION 3.15)

# Project name and C++ standard
project(MacrosBinary LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Ensure static linking of the C++ runtime
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

# Set target properties to make the executable portable
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "MacrosBinary"       # Optional: Rename the output binary
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin # Output location
)

# Specify Windows target version (optional)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "_WIN32_WINNT=0x0601") # Windows 7+
endif()

# Include any additional libraries (optional)
# Example: target_link_libraries(${PROJECT_NAME} PRIVATE some_library)

# Pack dependencies (only if needed)
# Example using CPack to generate a ZIP package
include(CPack)
set(CPACK_GENERATOR "ZIP")
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}_portable")