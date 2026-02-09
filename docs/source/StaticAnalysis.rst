StaticAnalysis
==============

Utilities to perform static analysis checks.

lint_with_clang_tidy
^^^^^^^^^^^^^^^^^^^^

.. code-block:: cmake

   lint_with_clang_tidy(<source_file_path>...)

Perform static analysis through clang-tidy.

Will pick up the settings of a top-level `.clang-tidy` configuration file
in the source directory.

Arguments
---------

**${ARGN}**
    List of C/C++ files to run clang-tidy on.

Examples
--------

.. code-block:: cmake

   lint_with_clang_tidy(
     "${CMAKE_SOURCE_DIR}/src/main.cpp"
     "${CMAKE_SOURCE_DIR}/src/utils.cpp"
   )

lint_with_iwyu
^^^^^^^^^^^^^^

Lint with include-what-you-use.

Arguments
---------

**${ARGN}**
   List of options to pass to include-what-you-use.

Examples
--------

.. code-block:: cmake

   lint_with_iwyu(-Xiwyu --error_always)
