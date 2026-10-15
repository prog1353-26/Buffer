# CMakeLists.txt — PROG1353 starter project
#
# You describe WHAT to build; CMake generates the clang++ commands.
# Rename the project and the target below when you start real work.

cmake_minimum_required(VERSION 4.4)

project(prog1353_starter LANGUAGES CXX)

# The standard this course uses. EXTENSIONS OFF means plain ISO C++20 —
# no compiler-specific extras that would not compile for anyone else.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Writes build/compile_commands.json — the exact flags CMake used for each
# file. The C/C++ extension reads it, so IntelliSense matches the real build.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If nobody chose a build type, build Debug. Debug adds -g, which is what
# lets lldb show your source instead of machine code.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# One executable, built from the sources listed here.
# Add .cpp files to this list as the project grows:
#     add_executable(app src/main.cpp src/greet.cpp)
# Headers are NOT listed — #include finds them.
add_executable(app
    src/main.cpp
    src/Buffer.cpp
)

# So that #include "greet.h" finds src/greet.h.
target_include_directories(app PRIVATE src)

# Warnings are free bug reports. Turn them on for our code and read them.
target_compile_options(app PRIVATE -Wall -Wextra)
