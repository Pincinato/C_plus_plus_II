cmake_minimum_required(VERSION 3.1.0)

project(Ex3)

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
# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5PrintSupport CONFIG REQUIRED)
message("${Qt5PrintSupport_DIR}")
# Populate a CMake variable with the sources
set(APP_SOURCES src/main.cpp src/ui/widget.ui src/ui/widget.cpp src/main.cpp src/ui/widget.h
    src/ui/qcustomplot-source/qcustomplot.cpp src/ui/qcustomplot-source/qcustomplot.h
    src/ui/widget_ex3_4.ui src/ui/widget_ex3_4.cpp src/ui/widget_ex3_4.h  src/files/ekg.txt)
#set Directories
set(APP_INCLUDE_DIRS src src/ui src/ui/qcustomplot-source)
INCLUDE_DIRECTORIES(${APP_INCLUDE_DIRS})
# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")
add_executable(${PROJECT_NAME} ${APP_SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport)
