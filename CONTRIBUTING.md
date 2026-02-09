<!--
SPDX-FileCopyrightText: 2026 Jason Pena <jasonpena@awkless.com>
SPDX-License-Identifier: MIT
-->

# Contributing

Thank you for taking the time to contribute! Please note that the information
stored in this document should be seen as guidelines, not steadfast rules!

## Issue Tracker Submissions

The issue tracker of this project is only for bug reports or feature requests.
please do not use it for asking questions or help. Please use the provided
templates when making a submission to the issue tracker.

## Pull Request Style

Helpful templates are provided to you for properly formatting your pull
requests. Understand that this project uses trunk based development. Thus, all
changes you make must occur separately on an unprotected branch based off of
`main` from your fork. Try to keep a linear commit history by using rebase
merging. Avoid merge commits.

Here some tips for better pull requests:

- Keep pull requests short and simple.
- Keep pull requests focused on one goal/issue.
- Break up large scale changes into multiple pull requests.
- Use `git fetch --all -p` to get changes from main and then use
  `get rebase origin/main` to put your changes over the changes on `main`
  keeping a nice linear history.
- Stash untracked local changes with `git stash -u` and later pop them with
  `git stash pop`.

Remember that your pull requests must pass through the various CI workflow tests
that the project uses to ensure code quality. If your pull requests fail any one
of these automated tests, then your changes __WILL NOT__ be merged into `main`
until you fix the issues.

Afterwards, manual code review will occur. Awkless is the main code owner and
may ask you to make some changes to your code before rebase merging the pull
request onto `main`.

## Code Style

To keep things simple, rely on the [gersemi][gersemi] styling tool to quickly
format any piece of CMake code. The `cmake-format` tool is dead,
[gersemi][gersemi] is the way forward. Here are some additional rules.

1. Use uppercase for cache variables or variables shared across CMake files.
2. Use lowercase for local variables.
3. Use consistent prefixes for variables to avoid name conflicts.
4. Quote strings and variables to avoid unintended behavior, especially when
   dealing with paths or arguments that may contain spaces.
5. Do not quote boolean values.
6. Always use lowercase for commands.

## Commit Style

All commits must abide by the [Conventional Commits 1.0.0][cc1.0.0]
specification. Here are the following valid types of commits accepted by this
project:

- __chore__: General change that does not affect production code.
- __feat__: Change that implements a feature in production code.
- __fix__: Change that fixes a bug in production code.
- __docs__: Improvements or fixes to documentation.
- __style__: Improvements or fixes to the formatting of code.
- __refactor__: Changes involve refactoring the code base.
- __revert__: A set of commits were revereted.

Keep the subject, body, and trailer of your commits below 80 characters unless
you have good reason otherwise.

## Licensing and Copyright

This project abides by the MIT license for the distribution of its source
code and documentation. The project also uses the CC0-1.0 license to place files
in the public domain, which are considered to be to small, or to generic to
place copyright over.

This project abides by the [REUSE 3.3 specification][reuse-3.3-spec]
specification to determine the licensing and copyright of files in the code
base. Thus, all files must have the proper SPDX copyright and licensing tags at
the top always. Contributors can use the [reuse tool][reuse-tool] to determine
if their changes are REUSE 3.3 compliant.

Do not forget to include the following SPDX copyright identifier at the top of
any file you create along with the SPDX license identifier:

```
SPDX-FileCopyrightText: <year> <name> <email>
SPDX-License-Identifier: MIT
```

[gersemi]: https://github.com/BlankSpruce/gersemi
[cc1.0.0]: https://www.conventionalcommits.org/en/v1.0.0/
[reuse-3.3-spec]: https://reuse.software/spec-3.3/
[reuse-tool]: https://reuse.software/tutorial/
