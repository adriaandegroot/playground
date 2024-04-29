/* === This file is part of Adriaan de Groot's Playground ===
 *
 *   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: BSD-2-Clause
 *
 *   The Playground is Free Software: see the License-Identifier above.
 *
 */

//
// The executable `a_la_mode` serves only to illustrate
// how to use mode_t helpers and user-defined literals.
//

#include "mode.h"

#include <iostream>

// Shorthand for printing a line with a string literal
// and also getting the consteval value of the mode_t
// represented by that literal.
#define EXAMPLE(x) \
    std::cout << x << '\t' << std::oct << from_readable_mode(x) << std::dec << '\n'

int main()
{
    EXAMPLE("rw-rw----"); // 660
    EXAMPLE("rwxr-xr-x"); // 755
    EXAMPLE("r--------"); // 400
    EXAMPLE("-w-r---wx"); // 243??

    // These won't even compile, but show compile-time
    // bugs being caught.
    //
    // EXAMPLE("bug"); // Not a 9-character literal
    // EXAMPLE("rwxbadbug");

    // Using _mode to indicate what the string means
    // might be easier to read.
    std::cout << "rw-r--r--" << '\t' << std::oct << "rw-r--r--"_mode << std::dec << '\n';

    // These won't even compile, for the same reasons
    //
    // std::cout << "birb"_mode << "------uwu"_mode;

    return 0;
}
