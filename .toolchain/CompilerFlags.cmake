function(set_compiler_flags interface)

    # =========================================================================
    # -f flags
    # =========================================================================

    # coroutines
    if (20_COROUTINES)
        add_compile_definitions(${interface} INTERFACE -fcoroutines)
    endif ()

    # ftrace
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
            add_compile_definitions(${interface} INTERFACE -ftime-trace)
        else ()
            message(WARNING "ftrace option enabled but not using Clang compiler. Option ignored")
        endif ()
    endif ()

    # color
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options(-fdiagnostics-color=always)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-fcolor-diagnostics)
    endif()


    if (ENABLE_COVERAGE)
        if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
            add_compile_options(-O0 -g3 -fprofile-instr-generate -fcoverage-mapping -fPIC --coverage -fno-inline)
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            add_compile_options(-O0 -g3 -fprofile-arcs -ftest-coverage -fPIC --coverage -fno-inline -fno-inline-small-functions -fno-default-inline)
        endif ()
    endif ()

endfunction()
