cmake_minimum_required(VERSION 3.1.0)

project(EyeTracking)

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
find_package(OpenCV REQUIRED)
find_package(Threads)
message("${Qt5PrintSupport_DIR}")
# Populate a CMake variable with the sources
set(APP_SOURCES src/main.cpp src/ui/widget.ui src/ui/widget.cpp src/main.cpp src/ui/widget.h
    src/ui/qcustomplot-source/qcustomplot.cpp src/ui/qcustomplot-source/qcustomplot.h
    src/app/acquisition/Camera.cpp src/app/acquisition/Camera.h src/app/acquisition/Icamera.h src/app/common/Eye_detector.cpp
    src/app/common/Eye_detector.h src/files/haarcascade_frontalface_alt.xml src/files/haarcascade_eye_tree_eyeglasses.xml
    src/app/common/ieye_detector.h )
#set Directories
set(APP_INCLUDE_DIRS src src/ui src/ui/qcustomplot-source src/app/ src/app/acquisition src/app/common src/files)
INCLUDE_DIRECTORIES(${APP_INCLUDE_DIRS})
# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")
add_executable(${PROJECT_NAME} ${APP_SOURCES})
FILE(COPY src/files/haarcascade_frontalface_alt.xml src/files/haarcascade_eye_tree_eyeglasses.xml DESTINATION ${PROJECT_BINARY_DIR})
# Use the Widgets module from Qt 5
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})
