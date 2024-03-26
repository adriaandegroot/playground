cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(cppplay)

find_package(fmt)

add_executable(cppplay main.cpp)

if(fmt_FOUND)
	target_compile_definitions(cppplay PUBLIC USE_FMT)
	target_link_libraries(cppplay PRIVATE fmt::fmt-header-only)
endif()
