foreach(library IN LISTS XRN_${XRN_BIN_NAME}_LIBRARIES_REQUIREMENTS)
    find_package(${library} REQUIRED)
endforeach()

add_library(XRN_${XRN_BIN_NAME}_BIN_OBJECTS OBJECT ${XRN_${XRN_BIN_NAME}_MAIN} ${XRN_${XRN_BIN_NAME}_SOURCES} ${XRN_${XRN_BIN_NAME}_FRAGMENT} ${XRN_${XRN_BIN_NAME}_VERTEX} ${XRN_${XRN_BIN_NAME}_HEADERS})
target_link_libraries(
    project_dependencies
    INTERFACE
    ${XRN_${XRN_BIN_NAME}_LIBRARIES_DEPENDENCY}
)

if (ENABLE_PCH)
    target_precompile_headers(
        XRN_${XRN_BIN_NAME}_BIN_OBJECTS
        PRIVATE
            <pch.hpp>
    )
endif ()

if (ENABLE_BINARY)
    add_executable(${XRN_${XRN_BIN_NAME}_BIN_NAME} $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS>)
    target_link_libraries(
        ${XRN_${XRN_BIN_NAME}_BIN_NAME}
        PRIVATE
            project_options
            project_warnings
            project_dependencies
    )
endif ()

set_property(TARGET XRN_${XRN_BIN_NAME}_BIN_OBJECTS PROPERTY POSITION_INDEPENDENT_CODE 1)
if (ENABLE_STATIC_LIBRARY)
    add_library(${XRN_${XRN_BIN_NAME}_BIN_NAME}_static STATIC $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS>)
    set_target_properties(${XRN_${XRN_BIN_NAME}_BIN_NAME}_static PROPERTIES OUTPUT_NAME ${XRN_${XRN_BIN_NAME}_BIN_NAME})
endif ()

if (ENABLE_SHARED_LIBRARY)
    add_library(${XRN_${XRN_BIN_NAME}_BIN_NAME}_shared SHARED $<TARGET_OBJECTS:XRN_${XRN_BIN_NAME}_BIN_OBJECTS>)
    set_target_properties(${XRN_${XRN_BIN_NAME}_BIN_NAME}_shared PROPERTIES OUTPUT_NAME ${XRN_${XRN_BIN_NAME}_BIN_NAME})
endif ()

foreach(library IN LISTS XRN_${XRN_BIN_NAME}_LIBRARIES_HEADERS)
    include_directories(
        ${${library}_INCLUDE_DIRS}
    )
endforeach()
