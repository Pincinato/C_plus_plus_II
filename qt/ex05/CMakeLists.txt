cmake_minimum_required(VERSION 2.8)

project(ex05)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# set flags to configure the warning settings
# Note: warnings are compiler specific
if( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Find library
find_package(Threads)
set(CMAKE_BUILD_TYPE "Debug")
add_executable(${PROJECT_NAME} main.cpp dataqueue.h)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
