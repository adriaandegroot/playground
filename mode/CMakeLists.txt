# === This file is part of Adriaan de Groot's Playground ===
#
#   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# The executable `a_la_mode` serves only to illustrate
# how to use mode_t helpers and user-defined literals.
#
# Build the executable, but the interesting bit is in mode.h,
# which can be copied around (keep the license intact).
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(a_la_mode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(a_la_mode)
target_sources(a_la_mode
    PUBLIC
        main.cc
        mode.h
)
