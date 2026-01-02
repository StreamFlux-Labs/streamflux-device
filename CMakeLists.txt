cmake_minimum_required(VERSION 3.15)

# Project Information
project(StreamFluxDevice
    VERSION 0.1.0
    DESCRIPTION "Embedded V4L2 capture and SRT streaming client"
    LANGUAGES CXX C
)

# ------------------------------------------------------------------------------
# 1. Project Options
# ------------------------------------------------------------------------------
option(BUILD_FOR_EMBEDDED "Build for Rockchip Target (ARM64)" OFF)
option(BUILD_TESTS        "Build GoogleTest Unit Tests"       ON)
option(BUILD_DOCS         "Build Documentation"               OFF)

# ------------------------------------------------------------------------------
# 2. C++ Standard & Compiler Settings
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Enforce ISO C++

# ------------------------------------------------------------------------------
# 3. Build Type Configuration (Debug vs Release)
# ------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Compiler Flags Base
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow")

# Debug Specific Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG_MODE")

# Release Specific Flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# ------------------------------------------------------------------------------
# 4. Output Directory Configuration
# ------------------------------------------------------------------------------
# All binaries go to ./build/bin and libraries to ./build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------------------------------------------------------------------------------
# 5. Cross-Compilation Logic
# ------------------------------------------------------------------------------
if(BUILD_FOR_EMBEDDED)
    message(STATUS ">> Building for TARGET: Rockchip (Embedded)")
    add_definitions(-DTARGET_ROCKCHIP)
    
    # Load toolchain settings if not passed via command line
    # include(cmake/Toolchain-Rockchip.cmake) 
else()
    message(STATUS ">> Building for HOST: Ubuntu/PC (x86_64)")
    add_definitions(-DTARGET_PC)
endif()

# ------------------------------------------------------------------------------
# 6. Global Include Directories
# ------------------------------------------------------------------------------
# Allows including headers via <interfaces/IVideoSource.h> or <common/Types.h>
include_directories(include)

# Main Source Code
add_subdirectory(src)

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------
# End of Configuration
# ------------------------------------------------------------------------------
message(STATUS "------------------------------------------------")
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "------------------------------------------------")
