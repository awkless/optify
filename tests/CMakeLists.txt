# SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/extern/cmocka/cmake/Modules")
include(AddCMockaTest)

add_cmocka_test(
    test_foobar
    COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_foobar.c"
    LINK_LIBRARIES cmocka::cmocka optify::optify)
add_cmocka_test_environment(test_foobar)
