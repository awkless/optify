<!--
SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Doxygen Utility Example

Example of using Doxygen utilities to generate in-source documentation.

Run the following to see the results:

```
cmake -S . -B build
cmake --build build
```

The resulting documentation can be viewed through a web browser by loading
 `build/docs/html/index.html`. The resulting executable `build/mysort` can also
run.
