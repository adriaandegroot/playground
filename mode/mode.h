/* === This file is part of Adriaan de Groot's Playground ===
 *
 *   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: BSD-2-Clause
 *
 *   The Playground is Free Software: see the License-Identifier above.
 *
 */
#include <sys/stat.h>

namespace detail
{
    // Tag classes to get suggestive type names into error messages
    struct invalid_permission_character {};
    struct invalid_permission_string_length {};

    // Check a single character in the string, returning
    // the mode_t for that bit-position. Peculiar name means
    // we get a suggestive error message
    template<int position, char accept>
    consteval mode_t expected_character_at_position(const char * const permission_string)
    {
        const char c = permission_string[position];
        if(c == accept) { return 1 << (8-position); }
        if(c == '-') { return 0; }
        throw invalid_permission_character{};
    }

    // Worker function, assumes that it is called only by
    // from_readable_mode() or operator ""_mode, which have
    // done checking beforehand for the validity of s.
    //
    // It's wordy, but that does mean you get a suggestive
    // error message with the bit-position and expected character.
    consteval mode_t from_readable_mode_string(const char * const s)
    {
    return
        detail::expected_character_at_position<0, 'r'>(s) |
        detail::expected_character_at_position<1, 'w'>(s) |
        detail::expected_character_at_position<2, 'x'>(s) |
        detail::expected_character_at_position<3, 'r'>(s) |
        detail::expected_character_at_position<4, 'w'>(s) |
        detail::expected_character_at_position<5, 'x'>(s) |
        detail::expected_character_at_position<6, 'r'>(s) |
        detail::expected_character_at_position<7, 'w'>(s) |
        detail::expected_character_at_position<8, 'x'>(s);
    }
}

// Turns a 9-character permission string like you would get
// from `ls -l` into the mode_t that it represents.
//
// (the [10] is because of the trailing NUL byte)
consteval mode_t from_readable_mode(const char (&permission_string)[10])
{
    return detail::from_readable_mode_string(permission_string);
}

// Turns a 9-character permission string like you would get
// from `ls -l` into the mode_t that it represents.
consteval mode_t operator""_mode(const char *s, size_t len)
{
    if (len != 9)
    {
        throw detail::invalid_permission_string_length{};
    }
    return detail::from_readable_mode_string(s);
}
