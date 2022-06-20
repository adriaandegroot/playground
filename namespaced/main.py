#! /usr/bin/env python3
#
#   SPDX-FileCopyrightText: no
#   SPDX-License-Identifier: CC0-1.0

"""
Reads stdin, computes namespace-nesting, then spits out
a uniqued namespace map showing the overall nesting
in a codebase. Assumes clang-formatted sources,
and that you're using `rg namespace`
to do the searching.

FixNamespaceComments: "true"
NamespaceIndentation: None
ShortNamespaceLines: 0

Something like `rg namespace | python3 main.py` should do the trick.
"""

import sys

namespaces = set()
current_namespace = []
current_filename = None
anon_count = 0

def munge_filename(filename):
    return "".join([x for x in filename.split('/')[-1].split('.')[0] if x.isalpha() ])


for l in sys.stdin.readlines():
    try:
        filename, code = l.split(':', maxsplit=1)
        if current_filename != filename:
            assert not current_namespace
            current_filename = filename
        if code.startswith('namespace'):
            if '=' not in code:
                parts = code.split()
                if len(parts) == 2:
                    assert parts[0] == 'namespace'
                    current_namespace.append(parts[1])
                if len(parts) == 1:
                    current_namespace.append(f"_{munge_filename(current_filename)}_{anon_count}")
                    anon_count += 1
                namespaces.add("::".join(current_namespace))
        if code.startswith('}  // namespace'):
            parts = code.split()
            if len(parts) == 3:
                assert current_namespace[-1].startswith("_")
            else:
                assert parts[-1] == current_namespace[-1], "Mismatch %r vs %r" % (parts[-1], current_namespace[-1])
            current_namespace.pop()
    except Exception as e:
        print(l)
        raise

for n in sorted(list(namespaces)):
    print(n)
