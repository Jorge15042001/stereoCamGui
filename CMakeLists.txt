cmake_minimum_required(VERSION 3.10)

project(CommandGUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Find GTKmm package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Add the executable
add_executable(main src/main.cpp)

# Include GTKmm headers
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Specify the libraries to link against
target_link_libraries(main ${GTKMM_LIBRARIES})

# Set C++ standard
set_property(TARGET main PROPERTY CXX_STANDARD 11)

# Export compile commands for use with editors supporting Language Server
# Protocol (LSP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
