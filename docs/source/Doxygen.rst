Doxygen
=======

Utilities to manage in-source documentation generation through the Doxygen
command.

doxygen_generate
^^^^^^^^^^^^^^^^

.. code-block:: cmake

  doxygen_generate(
    DOXYFILE_IN  <path>
    DOXYFILE_OUT <path>
    DOXYGEN_INDEX <path>
  )

Use Doxygen to generate documentation using a template Doxyfile.

Only generates documentation when updates are made to the generated index
file.

Keyword Arguments
-----------------

**DOXYFILE_IN**
    Path to the input template Doxyfile.

**DOXYFILE_OUT**
    Path where the configured Doxyfile will be written.

**DOXYGEN_INDEX**
    Path to check if generated index file changed to update documentation.

Examples
--------

Assume that the following settings have been set in a Doxyfile template
located at ``docs/Doxyfile.in``:

.. code-block:: text

  PROJECT_NAME     = "@PROJECT_NAME@"
  PROJECT_NUMBER   = "@PROJECT_VERSION@"
  PROJECT_BRIEF    = "@PROJECT_DESCRIPTION@"
  OUTPUT_DIRECTORY = @CMAKE_CURRENT_BINARY_DIR@/docs/
  INPUT            = @CMAKE_SOURCE_DIR@/include/
  RECURSIVE        = YES

Now call ``doxygen_generate`` using the Doxyfile template:

.. code-block:: cmake

  doxygen_generate(
    DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in"
    DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    DOXYGEN_INDEX "${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html"
  )
