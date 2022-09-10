cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# =========================================================================
# Configuration
# =========================================================================

# project
project(CMakeSandbox LANGUAGES CXX)
set(XRN_${XRN_BIN_NAME}_BIN_NAME xrn)
set(XRN_${XRN_BIN_NAME}_CXX_VERSION 23)

# dependencies
set(XRN_${XRN_BIN_NAME}_LIBS_REQUIRED fmt/8.1.1)
set(XRN_${XRN_BIN_NAME}_LIBRARIES_REQUIREMENTS fmt Threads) # find_package
set(XRN_${XRN_BIN_NAME}_LIBRARIES_DEPENDENCY fmt::fmt Threads::Threads) # target_link_libraries
set(XRN_${XRN_BIN_NAME}_LIBRARIES_HEADERS fmt) # include_directories(${library}_INCLUDE_DIRS)

set(SPDLOG_BUILD_SHARED OFF)
set(SPDLOG_FMT_EXTERNAL ON)
set(SPDLOG_BUILD_EXAMPLE OFF)
set(SPDLOG_BUILD_TESTS OFF)

# paths
set(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR "${CMAKE_SOURCE_DIR}/.toolchain")
set(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DETAILS_DIR "${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/.details")
set(XRN_${XRN_BIN_NAME}_SOURCES_DIR "sources")
set(XRN_${XRN_BIN_NAME}_TESTS_DIR "tests")
set(XRN_${XRN_BIN_NAME}_EXTERNAL_DIR "externals")
set(XRN_${XRN_BIN_NAME}_OUTPUT_DIR "binaries")

set(XRN_${XRN_BIN_NAME}_SHADERS_DIR "shaders")
set(XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR "Fragment")
set(XRN_${XRN_BIN_NAME}_VERTEXES_DIR "Vertex")

# testing
option(ENABLE_TESTING "Enable testing" OFF)
option(ENABLE_UNIT_TESTING "Build unit tests" OFF)
option(RUN_UNIT_TESTS "Run the tests at the end of their compilation" OFF)
option(ENABLE_BENCHMARKS "Build benchmarks" OFF)
option(ENABLE_FUZZ_TESTING "Build fuzzing tests" OFF)

# dev mode
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)
option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)

# static analysis
option(ENABLE_STATIC_ANALYSIS "Enable static analysis" OFF)
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

# sanatizer
option(ENABLE_SANITIZERS "Allow to enable a sanitizer, checks if the compiler supports sanitizers" OFF)
option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ON)
option(ENABLE_SANITIZER_LEAK "Enable leak sanitizer" ON)
option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "Enable undefined behavior sanitizer" ON)
option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)

# compilations
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(ENABLE_C++20_COROUTINES "Enable coroutines supports" OFF)
option(ENABLE_SHADERS "Compiles GLSL shaders to SPV" ON)

# optimization
option(ENABLE_IPO "Enable IterpPocedural Optimization (Link Time Optimization)" OFF)
option(ENABLE_CACHE "Enable cache if available" ON)
option(ENABLE_PCH "Enable personal Precompiled Headers (<pch.hpp>)" OFF)

# others
option(ENABLE_UPDATE_CONAN "Enable updates of the <conan.cmake> file each run" OFF)
option(ENABLE_DOCUMENTATION "Enable doxygen doc builds of source" OFF)
option(ENABLE_CMAKE_DEBUG "Enable debug outputs of cmake's makefiles" ON)

# Binary form
option(ENABLE_OUTPUT_DIR "Puts every ouput binaries in the '${XRN_${XRN_BIN_NAME}_OUTPUT_DIR}' directory" OFF)
option(ENABLE_BINARY "Compile the main program as a binarry" ON)
option(ENABLE_STATIC_LIBRARY "Compile the main program as a static library" OFF)
option(ENABLE_SHARED_LIBRARY "Compile the main program as a shared library" OFF)



# =========================================================================
# Abolute paths
# =========================================================================

set(XRN_${XRN_BIN_NAME}_ROOT_DIR_RELATIVE ${CMAKE_SOURCE_DIR})
set(XRN_${XRN_BIN_NAME}_BUILD_DIR_RELATIVE ${CMAKE_BINARY_DIR})
set(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR})
set(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DETAILS_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DETAILS_DIR})
set(XRN_${XRN_BIN_NAME}_SOURCES_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_SOURCES_DIR})
set(XRN_${XRN_BIN_NAME}_TESTS_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_TESTS_DIR})
set(XRN_${XRN_BIN_NAME}_INCLUDE_DIRS_RELATIVE ${XRN_${XRN_BIN_NAME}_EXTERNAL_DIR})

set(XRN_${XRN_BIN_NAME}_SHADERS_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_SHADERS_DIR})
set(XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/${XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR})
set(XRN_${XRN_BIN_NAME}_VERTEXES_DIR_RELATIVE ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/${XRN_${XRN_BIN_NAME}_VERTEXES_DIR})

get_filename_component(XRN_${XRN_BIN_NAME}_ROOT_DIR ${CMAKE_SOURCE_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_BUILD_DIR ${CMAKE_BINARY_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR ${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_TOOLCHAIN_DETAILS_DIR ${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DETAILS_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_SOURCES_DIR ${XRN_${XRN_BIN_NAME}_SOURCES_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_TESTS_DIR ${XRN_${XRN_BIN_NAME}_TESTS_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_EXTERNAL_DIR ${XRN_${XRN_BIN_NAME}_EXTERNAL_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_OUTPUT_DIR ${XRN_${XRN_BIN_NAME}_BUILD_DIR}/${XRN_${XRN_BIN_NAME}_OUTPUT_DIR} REALPATH)

get_filename_component(XRN_${XRN_BIN_NAME}_SHADERS_DIR ${XRN_${XRN_BIN_NAME}_SHADERS_DIR} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_VERTEXES_DIR ${XRN_${XRN_BIN_NAME}_VERTEXES_DIR_RELATIVE} REALPATH)
get_filename_component(XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR ${XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR_RELATIVE} REALPATH)



# =========================================================================
# Sources
# =========================================================================

get_filename_component(XRN_${XRN_BIN_NAME}_MAIN ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/main.cpp REALPATH)
file(
    GLOB_RECURSE
    XRN_${XRN_BIN_NAME}_SOURCES
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.cpp
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.cxx
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.c
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.CC
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_${XRN_BIN_NAME}_HEADERS
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.hpp
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.hxx
    ${XRN_${XRN_BIN_NAME}_SOURCES_DIR}/*.h
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_${XRN_BIN_NAME}_FRAGMENTS
    ${XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR}/*.glsl
    ${XRN_${XRN_BIN_NAME}_FRAGMENTS_DIR}/*.shader
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.vert
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.vertex
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.vs
    PARENT_SCOPE
)
file(
    GLOB_RECURSE
    XRN_${XRN_BIN_NAME}_VERTEXES
    ${XRN_${XRN_BIN_NAME}_VERTEXES_DIR}/*.glsl
    ${XRN_${XRN_BIN_NAME}_VERTEXES_DIR}/*.shader
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.vert
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.vertex
    ${XRN_${XRN_BIN_NAME}_SHADERS_DIR}/*.fs
    PARENT_SCOPE
)



# =========================================================================
# Setup interfaces and configurations
# =========================================================================

# debug
if (ENABLE_CMAKE_DEBUG)
    SET(CMAKE_VERBOSE_MAKEFILE TRUE)
endif ()

# generate sources list without the main
list(REMOVE_ITEM XRN_${XRN_BIN_NAME}_SOURCES "${XRN_${XRN_BIN_NAME}_MAIN}")

# includes
include_directories(${XRN_${XRN_BIN_NAME}_SOURCES_DIR})
include_directories(${XRN_${XRN_BIN_NAME}_EXTERNAL_DIR})



# =========================================================================
# Options
# =========================================================================

add_library(project_options INTERFACE)

# basic useful actions controlled by the options/
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/StandardProjectSettings.cmake)
set_standard_project_settings(project_options ${XRN_${XRN_BIN_NAME}_CXX_VERSION})

# sanitizer options if supported by compiler
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Sanitizers.cmake)
enable_sanitizers(project_options)



# =========================================================================
# Warnings and flags
# =========================================================================

add_library(project_warnings INTERFACE)

# compiler warnings
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/CompilerWarnings.cmake)
set_compiler_warnings(project_warnings)

# compiler flags
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/CompilerFlags.cmake)
set_compiler_flags(project_warnings)



# =========================================================================
# Dependencies
# =========================================================================

add_library(project_dependencies INTERFACE)

# compile shaders
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Shaders.cmake)
compile_shaders(project_dependencies)



# =========================================================================
# Others
# =========================================================================

# checks the build directory if it points to the sources, aborts if it does
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/PreventInSourceBuilds.cmake)
prevent_in_source_builds()

# cache if supported by compiler
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Cache.cmake)
enable_cache()

# enable documentation
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Documentation.cmake) # documentation configuration in the file
extract_documentation()

# allow for static analysis options
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/StaticAnalyzers.cmake) # possible to add more static analyzers in the file
run_static_analysis()

# download dependencies
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Dependencies.cmake)
download_dependencies("${XRN_${XRN_BIN_NAME}_LIBS_REQUIRED}") # isn't check whether the dowloaded failed or not



# =========================================================================
# Sub directories
# =========================================================================

# sub projects
add_subdirectory(${XRN_${XRN_BIN_NAME}_SOURCES_DIR})



# =========================================================================
# Tests
# =========================================================================

# tests
include(${XRN_${XRN_BIN_NAME}_TOOLCHAIN_DIR}/Tests.cmake)
enable_tests()
