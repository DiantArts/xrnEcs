# =========================================================================
# extern
# =========================================================================

foreach(library IN LISTS XRN_${XRN_BIN_NAME}_LIBRARIES_REQUIREMENTS)
    find_package(${library} REQUIRED)
endforeach()


# =========================================================================
# setup
# =========================================================================

# basic tests
set(XRN_${XRN_BIN_NAME}_BTESTS_BIN xrnTests)
set(XRN_${XRN_BIN_NAME}_BTESTS_DIR basic)

# constexpr tests
set(XRN_${XRN_BIN_NAME}_CTESTS_BIN xrnConstexprTests)
set(XRN_${XRN_BIN_NAME}_CTESTS_DIR constexpr)

# relaxed constexpr tests
set(XRN_${XRN_BIN_NAME}_RCTESTS_BIN xrnRelaxedConstexprTests)

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

include(ProcessorCount)
ProcessorCount(XRN_${XRN_BIN_NAME}_NPROC)
if (NOT XRN_${XRN_BIN_NAME}_NPROC EQUAL 0)
    set(CTEST_BUILD_FLAGS -j${XRN_${XRN_BIN_NAME}_NPROC})
    set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${XRN_${XRN_BIN_NAME}_NPROC})
endif ()

# auto-runners
if (RUN_UNIT_TESTS)
    add_custom_target(tests_run ALL DEPENDS ${XRN_${XRN_BIN_NAME}_BTESTS_BIN} ${XRN_${XRN_BIN_NAME}_CTESTS_BIN} ${XRN_${XRN_BIN_NAME}_RCTESTS_BIN})
    add_custom_command(
        TARGET tests_run
        COMMENT "Run tests..."
        POST_BUILD
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ctest -C $<CONFIGURATION> --output-on-failures
    )
endif ()



# =========================================================================
# Configuration definition
# =========================================================================

# Define binary
add_library(test_configs OBJECT main.cpp ${XRN_${XRN_BIN_NAME}_SOURCES} ${XRN_${XRN_BIN_NAME}_FRAGMENT} ${XRN_${XRN_BIN_NAME}_VERTEX} ${XRN_${XRN_BIN_NAME}_HEADERS})
target_link_libraries(
    test_configs
    PRIVATE
        project_dependencies
)
target_link_libraries(
    test_configs
    PUBLIC
        project_options
        project_warnings
        Catch2::Catch2
        ${XRN_${XRN_BIN_NAME}_LIBRARIES_DEPENDENCY}
)

foreach(library IN LISTS XRN_${XRN_BIN_NAME}_LIBRARIES_HEADERS)
    include_directories(
        ${${library}_INCLUDE_DIRS}
    )
endforeach()



# =========================================================================
# basic tests
# =========================================================================

file(GLOB_RECURSE XRN_${XRN_BIN_NAME}_TESTS_SRC ${XRN_${XRN_BIN_NAME}_BTESTS_DIR}/*.cpp ${XRN_${XRN_BIN_NAME}_BTESTS_DIR}/*.cxx)

message(${XRN_${XRN_BIN_NAME}_TESTS_SRC})

add_executable(${XRN_${XRN_BIN_NAME}_BTESTS_BIN} ${XRN_${XRN_BIN_NAME}_TESTS_SRC})
target_link_libraries(${XRN_${XRN_BIN_NAME}_BTESTS_BIN} PRIVATE test_configs)
# automatically discover tests that are defined in catch based test files you can modify the tests.
catch_discover_tests(
    ${XRN_${XRN_BIN_NAME}_BTESTS_BIN}
    TEST_PREFIX "tests :: "
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "tests :: "
    OUTPUT_SUFFIX .xml
)



# =========================================================================
# constexpr tests
# =========================================================================

file(GLOB_RECURSE XRN_${XRN_BIN_NAME}_CTESTS_SRC ${XRN_${XRN_BIN_NAME}_CTESTS_DIR}/*.cpp ${XRN_${XRN_BIN_NAME}_CTESTS_DIR}/*.cxx)

# normal constexpr
add_executable(${XRN_${XRN_BIN_NAME}_CTESTS_BIN} ${XRN_${XRN_BIN_NAME}_CTESTS_SRC})
target_link_libraries(${XRN_${XRN_BIN_NAME}_CTESTS_BIN} PRIVATE test_configs)
catch_discover_tests(
    ${XRN_${XRN_BIN_NAME}_CTESTS_BIN}
    TEST_PREFIX "constrexprTests :: "
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "constrexprTests :: "
    OUTPUT_SUFFIX .xml
)

# relaxed constexpr: Disable the constexpr portion of the test, and build again this allows us to have an
# executable that we can debug when things go wrong with the constexpr testing
add_executable(${XRN_${XRN_BIN_NAME}_RCTESTS_BIN} ${XRN_${XRN_BIN_NAME}_CTESTS_SRC})
target_link_libraries(${XRN_${XRN_BIN_NAME}_RCTESTS_BIN} PRIVATE test_configs)
target_compile_definitions(${XRN_${XRN_BIN_NAME}_RCTESTS_BIN} PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
catch_discover_tests(
    ${XRN_${XRN_BIN_NAME}_RCTESTS_BIN}
    TEST_PREFIX "relaxedConstrexprTests :: "
    REPORTER xml
    OUTPUT_DIR .
    OUTPUT_PREFIX "relaxedConstrexprTests :: "
    OUTPUT_SUFFIX .xml
)



# =========================================================================
# functionnal tests
# =========================================================================

# Provide a simple smoke test to make sure that the CLI works and can display a --help message
# add_test(NAME cli.has_help COMMAND intro --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
# add_test(NAME cli.version_matches COMMAND intro --version)
# set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")
