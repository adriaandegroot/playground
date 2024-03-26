# BusyButton is a QWidget -- a C++ class -- that provides a UI
# for a long-running operation. See the API documentation for details.
#
#   SPDX-FileCopyrightText:  Copyright (C) 2024 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build directly in the source-dir")
endif()

project(busybutton VERSION 0.1)
find_package(Qt5 5.15 COMPONENTS Widgets)

add_library(busybutton_lib STATIC src/busybutton.cc)
target_include_directories(busybutton_lib PUBLIC src)
target_link_libraries(busybutton_lib PUBLIC Qt5::Widgets)

add_executable(busybutton_demo example/main.cc)
target_link_libraries(busybutton_demo PRIVATE busybutton_lib)
