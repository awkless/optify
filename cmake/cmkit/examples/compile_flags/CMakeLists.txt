# SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21)

project(
    "compile_flags_example"
    VERSION 0.1.0
    DESCRIPTION "Example use of CompileFlags utilities"
    LANGUAGES C
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../")
include(CompileFlags)

option(WARNINGS_AS_ERRORS "Treat warnings as errors" FALSE)
add_library(warning_flags INTERFACE)
set_warning_flags(
    warning_flags
    AS_ERRORS "${WARNINGS_AS_ERRORS}"
    MSVC_WARNINGS /Wall /W4
    CLANG_WARNINGS -Wall -Wextra
    GNU_WARNINGS -Wall -Wextra
)
add_library(mysort::warning_flags ALIAS warning_flags)

add_executable(mysort)
target_sources(
    mysort
    PRIVATE "${CMAKE_SOURCE_DIR}/src/sort.c" "${CMAKE_SOURCE_DIR}/src/main.c"
)
target_link_libraries(mysort PRIVATE mysort::warning_flags)
