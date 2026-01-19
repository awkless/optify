# SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.21)

project(
    "optify"
    VERSION 0.1.0
    DESCRIPTION "Minimal Unix-like command-line argument parser"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(cmkit/Doxygen)

set(CMAKE_DEBUG_POSTFIX d)
add_library(optify)
add_library(optify::optify ALIAS optify)
set_target_properties(
    optify
    PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_sources(optify PRIVATE src/optify.c)
target_compile_features(optify PUBLIC c_std_99)
target_include_directories(
    optify
    PRIVATE src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_property(TARGET optify PROPERTY C_VISIBILITY_PRESET "hidden")
set_property(TARGET optify PROPERTY VISIBILITY_INLINES_HIDDEN TRUE)

include(GenerateExportHeader)
generate_export_header(optify EXPORT_FILE_NAME "include/optify_export.h")

target_include_directories(
    optify
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(GNUInstallDirs)
install(
    TARGETS optify
    EXPORT optify_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/optify_export.h"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/optify
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "OptifyConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/OptifyConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/OptifyConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/optify
)

install(
    EXPORT optify_targets
    FILE OptifyTargets.cmake
    NAMESPACE optify::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/optify
)
