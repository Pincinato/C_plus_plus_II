# Name of project and executable
project(HelloWorld)

# set cmake version
cmake_minimum_required(VERSION 2.8)

# activate latest c++ compiler version
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# set flags to configure the warning settings
# Note: warnings are compiler specific
if( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Add an executable to the project and sources
add_executable(${PROJECT_NAME} "helloworld.cpp")


