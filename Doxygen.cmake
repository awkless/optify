# SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

# Use Doxygen to generate documentation using a template Doxyfile.
#
# Only generates documentation when updates are made to the generated index
# file.
#
# Keyword Arguments
# -----------------
#
# DOXYFILE_IN:
#     Path to the input template Doxyfile.
# DOXYFILE_OUT:
#     Path where the configured Doxyfile will be written.
# DOXYGEN_INDEX:
#     Path to check if generated index file changed to update documentation.
function(doxygen_generate)
    set(options "")
    set(one_value_keywords "DOXYFILE_IN" "DOXYFILE_OUT" "DOXYGEN_INDEX")
    set(multi_value_keywords "")
    cmake_parse_arguments(
        ARG
        "${options}"
        "${one_value_keywords}"
        "${multi_value_keywords}"
        ${ARGN}
    )

    if(NOT DEFINED ARG_DOXYFILE_IN)
        message(FATAL_ERROR "No path to input template Doxyfile config")
    endif()

    if(NOT DEFINED ARG_DOXYFILE_OUT)
        message(FATAL_ERROR "No path to output template Doxyfile config")
    endif()

    if(NOT DEFINED ARG_DOXYGEN_INDEX)
        message(FATAL_ERROR "No path to generated index")
    endif()

    find_package(Doxygen)
    if(NOT DEFINED DOXYGEN_FOUND)
        message(FATAL_ERROR "Cannot locate Doxygen, please install it")
    endif()

    configure_file("${ARG_DOXYFILE_IN}" "${ARG_DOXYFILE_OUT}" @ONLY)

    message(STATUS "Start Doxygen build")
    add_custom_target(
        doxygen
        ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${ARG_DOXYFILE_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generate API documentation with Doxygen"
        VERBATIM
    )

    add_custom_target(Doxygen ALL DEPENDS "${ARG_DOXYGEN_INDEX}")
endfunction()
