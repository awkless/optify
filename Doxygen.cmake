# SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

#.rst:
# Doxygen
# =======
#
# Utilities to manage in-source documentation generation through the Doxygen
# command.
#
# .. cmake:command:: doxygen_generate
#
#    Use Doxygen to generate documentation using a template Doxyfile.
#
#    Only generates documentation when updates are made to the generated index
#    file.
#
#    .. code-block:: cmake
#
#       doxygen_generate(
#         DOXYFILE_IN  <path>
#         DOXYFILE_OUT <path>
#         DOXYGEN_INDEX <path>
#       )
#
#    Keyword Arguments
#    -----------------
#
#    :keyword DOXYFILE_IN:
#      Path to the input template Doxyfile.
#
#    :keyword DOXYFILE_OUT:
#      Path where the configured Doxyfile will be written.
#
#    :keyword DOXYGEN_INDEX:
#      Path to check if generated index file changed to update documentation.
#
#    Examples
#    --------
#
#    Assume that the following settings have been set in a Doxyfile template
#    located at ``docs/Doxyfile.in``:
#
#    .. code-block:: text
#
#       PROJECT_NAME     = "@PROJECT_NAME@"
#       PROJECT_NUMBER   = "@PROJECT_VERSION@"
#       PROJECT_BRIEF    = "@PROJECT_DESCRIPTION@"
#       OUTPUT_DIRECTORY = @CMAKE_CURRENT_BINARY_DIR@/docs/
#       INPUT            = @CMAKE_SOURCE_DIR@/include/
#       RECURSIVE        = YES
#
#    Now call ``doxygen_generate`` using the Doxyfile template:
#
#    .. code-block:: cmake
#
#       doxygen_generate(
#         DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
#         DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
#         DOYXGEN_INDEX "${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html"
#       )

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
	doxygen ALL
	COMMAND ${DOXYGEN_EXECUTABLE} ${ARG_DOXYFILE_OUT}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generate API documentation with Doxygen"
	VERBATIM
    )

    add_custom_target(Doxygen ALL DEPENDS "${ARG_DOXYGEN_INDEX}")
endfunction()
