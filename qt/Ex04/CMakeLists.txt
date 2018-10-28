cmake_minimum_required(VERSION 3.1.0)

project(Ex04)
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
# Populate a CMake variable with the sources
set(APP_SOURCES src/main.cpp src/threadlogfile.h src/threadlogfilesafe.h
    src/files/threadLog.txt src/files/threadLogSafe.txt)
#set Directories
set(APP_INCLUDE_DIRS src )
INCLUDE_DIRECTORIES(${APP_INCLUDE_DIRS})
# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")
add_executable(${PROJECT_NAME} ${APP_SOURCES})
FILE(COPY src/files/threadLog.txt DESTINATION ${PROJECT_BINARY_DIR})
FILE(COPY src/files/threadLogSafe.txt DESTINATION ${PROJECT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
