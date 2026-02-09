# SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21)

project(
    "doxygen_example"
    VERSION 0.1.0
    DESCRIPTION "Example use of Doxygen utilities"
    LANGUAGES C
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../")
include(Doxygen)

doxygen_generate(
	DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
	DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
	DOXYGEN_INDEX "${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html"
)

add_executable(mysort)
target_sources(
    mysort
    PRIVATE "${CMAKE_SOURCE_DIR}/src/sort.c" "${CMAKE_SOURCE_DIR}/src/main.c"
)
