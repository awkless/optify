CompileFlags
============

Utilities to manage compilation flags.

set_warning_flags
^^^^^^^^^^^^^^^^^

.. code-block:: cmake

   set_warning_flags(
     <library_interface>
     AS_ERRORS ["TRUE" | "FALSE"]
     MSVC_WARNINGS <flag>...
     CLANG_WARNINGS <flag>...
     GNU_WARNINGS <flag>...
   )

Set warnings flags for a target compiler.

Only sets warning flags if specific target compiler is detected during
build. Caller can choose to treat warnings as errors or not.

Arguments
---------

**interface_target**
  Library interface target to set warnings flags on.

Keyword Arguments
-----------------

**AS_ERRORS**
   If "TRUE" then all warnings will be treated as errors.

**MSVC_WARNINGS**
   Warning flags specific for MSVC compiler platform.

**CLANG_WARNINGS**
   Warning flags specific for CLANG compiler platform.

**GNU_WARNINGS**
   Warning flags specific for GNU compiler platform.

Examples
--------

.. code-block:: cmake

   option(WARNINGS_AS_ERRORS "Treat warnings as errors" FALSE)
   add_library(warning_flags INTERFACE)
   set_warning_flags(
     warning_flags
     AS_ERRORS "${WARNINGS_AS_ERRORS}"
     MSVC_WARNINGS /Wall /W4
     CLANG_WARNINGS -Wall -Wextra
     GNU_WARNINGS -Wall -Wextra
   )
