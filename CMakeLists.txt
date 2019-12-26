cmake_minimum_required(VERSION 3.15)
project(StringEquation)

set(CMAKE_CXX_STANDARD 14)

add_library(StringEquation SHARED StringEquation.cpp StringEquation.h Plugin.cpp Parser.cpp Parser.h)
target_link_libraries(
        StringEquation $ENV{DEVKIT_LOCATION}/lib/OpenMaya.lib $ENV{DEVKIT_LOCATION}/lib/Foundation.lib)

include_directories($ENV{DEVKIT_LOCATION}/include)
link_libraries($ENV{DEVKIT_LOCATION}/lib)
