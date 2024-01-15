cmake_minimum_required(VERSION 3.10)

project(CommandGUI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# list(APPEND CMAKE_PREFIX_PATH "/usr/local/share/") Find GTKmm package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
find_package(OpenCV REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

# find_package(stereocam REQUIRED) target_link_libraries( main PRIVATE
# stereocam::stereoCamUtils stereocam::stereocam_options
# stereocam::stereocam_warnings)

# Add the executable
add_executable(
  main
  src/main.cpp
  src/captureScreen.cpp
  src/CommandRunner.cpp
  src/TaskManger.cpp
  src/widgets.cpp
  src/CalibrationScreen.cpp
  src/CalibrationFishEyeScreen.cpp
  src/LiveViewScreen.cpp
  src/RectifyScreen.cpp
  src/DepthScreen.cpp
  src/utils.cpp)

add_subdirectory("/home/jorge1504/projects/stereocam2/" build)
file(WRITE "all_variables.txt" "")

# Get all CMake properties and iterate over them
get_cmake_property(_variable_names VARIABLES)
foreach(_variable_name ${_variable_names})
  # Append variable name and value to the file
  file(APPEND "all_variables.txt" "${_variable_name}=${${_variable_name}}\n")
endforeach()

# Include GTKmm headers
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Specify the libraries to link against
target_link_libraries(main PRIVATE ${GTKMM_LIBRARIES} stereocam_lib fmt::fmt
                                   ${OpenCV_LIBS})
# target_link_libraries( main PRIVATE stereocam::stereoCamUtils
# stereocam::stereocam_options stereocam::stereocam_warnings)

# Set C++ standard
set_property(TARGET main PROPERTY CXX_STANDARD 20)

# Export compile commands for use with editors supporting Language Server
# Protocol (LSP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
