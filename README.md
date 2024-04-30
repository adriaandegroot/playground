# Playground

> This repository contains "playground" applications, or
> things that don't particularly fit anywhere else in my
> collection of repositories.

To use one of these playground applications, `cd` into the appropriate
directory and build it there (with CMake) or run it there (for Python
applications). There is no top-level builder.

- *cppplay* is a tiny example C++ project with CMake,
  used to test CLion's remote-development setup.
- *mode* is a consteval (compile-time) interpreter of
  compact readable file-mode expressions in the style
  of `ls(1)`, usable in e.g. `chmod(filename, "rwxr-x---"_mode)`.
- *namespaced* is a little tool to print out anonymous
  and non-anonymous namespaces found in a codebase (assumes
  particular clang-format conventions to spot the namespace names).
- *strong-bool* is a demonstration of a "strong boolean",
  something that is a suitable "upgrade" for a 0/1 `int`
  in legacy codebases.
