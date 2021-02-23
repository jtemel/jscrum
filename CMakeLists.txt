# Main entry point for cmake

cmake_minimum_required(VERSION 2.8)

project(jscrum)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.45.0 REQUIRED COMPONENTS filesystem program_options)

# TODO: Update this!
set(INSTALL_DIR "/home/jtemel/jscrum/bin")

# All includes are found in the same parent directory
include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)

# All src files are found in the same parent directory
add_subdirectory(src)

# All test files are found in the same parent directory
add_subdirectory(test)
