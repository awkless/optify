# SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

# Set warnings flags for a target compiler.
#
# Only sets warning flags if specific target compiler is detected during
# build. Caller can choose to treat warnings as errors or not.
#
# Arguments
# ---------
#
# interface_target
#     Library interface target to set warnings flags on.
#
# Keyword Arguments
# -----------------
#
# AS_ERRORS
#     If "TRUE" then all warnings will be treated as errors.
# MSVC_WARNINGS
#     Warning flags specific for MSVC compiler platform.
# CLANG_WARNINGS
#     Warning flags specific for CLANG compiler platform.
# GNU_WARNINGS
#     Warning flags specific for GNU compiler platform.
function(set_warning_flags interface_target)
    set(options "")
    set(one_value_keywords "AS_ERRORS")
    set(multi_value_keywords "MSVC_WARNINGS" "CLANG_WARNINGS" "GNU_WARNINGS")
    cmake_parse_arguments(
        ARG
        "${options}"
        "${one_value_keywords}"
        "${multi_value_keywords}"
        ${ARGN}
    )

    set(target_warnings "")
    set(error_flags "")

    if(MSVC)
        if(DEFINED ARG_MSVC_WARNINGS)
            set(target_warnings ${ARG_MSVC_WARNINGS})
            set(error_flags "/WX")
        endif()
    elseif(
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang"
        OR CMAKE_C_COMPILER_ID MATCHES ".*Clang"
    )
        if(DEFINED ARG_CLANG_WARNINGS)
            set(target_warnings ${ARG_CLANG_WARNINGS})
            set(error_flags "-Werror")
        endif()
    elseif(
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
        OR CMAKE_C_COMPILER_ID STREQUAL "GNU"
    )
        if(DEFINED ARG_GNU_WARNINGS)
            set(target_warnings ${ARG_GNU_WARNINGS})
            set(error_flags "-Werror")
        endif()
    endif()

    if(ARG_AS_ERRORS STREQUAL "TRUE" AND error_flags)
        list(APPEND target_warnings ${error_flags})
    endif()

    if(target_warnings)
        target_compile_options(${interface_target} INTERFACE ${target_warnings})
    else()
        message(
            AUTHOR_WARNING
            "No warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler."
        )
    endif()
endfunction()
