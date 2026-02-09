<!--
SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# CMKit

Script utility kit for CMake.

Hello, and welcome to CMKit! This repository houses common script utilities that
I found to be useful for projects that employ CMake as its main build system. I
decided to place these CMake utilities here in order to make it easier to both
manage and distribute them.

## Installation

No standard installation method exists. The recommended ways to install CMKit
into a given CMake project mainly boils down to using Git submodules, Git
subtrees, or simply copying and pasting modules of interest directly into a
given project. Personally, the Git subtree method generally works best.

## Usage

Before using any of the scripts stored in this repository, the user must be
aware that all the scripts were written to be compatible with CMake [>= 3.21].
Some scripts can potentially be used on older CMake versions, but generally the
user should stick with CMake version 3.21 at minimum.

Refer to the `examples` directory for more detailed use cases for any utility
of interest. The code for any given module does contain a few comments
documenting the API for a given utility, but more details exist within the
Sphinx documentation itself. The following allows anyone to build the Sphinx
documentation for CMKit:

```
cd docs
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
make html
```

Enjoy!

## Contributing

This project is open to all forms of contribution. Please read the
`CONTRIBUTING.md` file for more details.

## License and Copyright

The CMKit project falls under the MIT license. Check the `LICENSE.txt` file for
more details.

The CMKit project also abides by the [REUSE 3.3 specification][reuse3.3]. All
files in this repository contain corresponding SPDX tags that document its
current copyright and licensing. Additional licenses used will be stored in the
`LICENSES` directory.

[reuse3.3]: https://reuse.software/spec-3.3/
