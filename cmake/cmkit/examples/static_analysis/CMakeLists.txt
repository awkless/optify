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
include(StaticAnalysis)

set(mysort_src
    "${CMAKE_SOURCE_DIR}/src/sort.c"
    "${CMAKE_SOURCE_DIR}/src/main.c"
)
lint_with_clang_tidy("${mysort_src}")
lint_with_iwyu(-Xiwu --error_always)

add_executable(mysort)
target_sources(mysort PRIVATE "${mysort_src}")
