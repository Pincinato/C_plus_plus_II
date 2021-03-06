cmake_minimum_required(VERSION 2.8.11)

# project name is Producer-Consumer-Pattern
project(EyeTracking)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wextra -Werror")
endif()


# Set current directory
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt Flags
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# build options
option( MODULE_CAMERA "Use UEYE Camera" ON )


set( APP_SOURCES )
set( APP_INCLUDE_DIRS )
set( APP_LIBS )

# main sources
set( APP_SOURCES ${APP_SOURCES}
    src/ui/widget.cpp
    src/ui/widget.h
    src/ui/widget.ui
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/ui/calibrationwidget.cpp
    src/ui/calibrationwidget.h
    src/ui/calibrationwidget.ui
    src/ui/icalibrationwidget.h
    src/ui/actionwidget.cpp
    src/ui/actionwidget.h
    src/ui/actionwidget.ui
    src/app/common/control.cpp
    src/app/common/control.h
    src/app/common/icontrol.h
    src/app/common/dataBuffer.cpp
    src/app/common/dataBuffer.h
    src/app/common/dataBufferPool.cpp
    src/app/common/dataBufferPool.h
    src/app/common/eyeDetector.cpp
    src/app/common/eyeDetector.h
    src/app/common/eyeAnalyser.cpp
    src/app/common/eyeAnalyser.h
    src/app/acquisition/camera.cpp
    src/app/acquisition/camera.h
    src/app/acquisition/VCamera.cpp
    src/app/acquisition/VCamera.h
    src/app/acquisition/USBcamera.cpp
    src/app/acquisition/USBcamera.h
    src/app/acquisition/icamera.h
    src/app/acquisition/basecamera.h
    src/app/acquisition/basecamerafactory.h
    src/app/visualisation/videoVisualizer.cpp
    src/app/visualisation/videoVisualizer.h
    src/app/visualisation/rOg_image.cpp
    src/app/visualisation/rOg_image.h
)


set( APP_INCLUDE_DIRS ${APP_INCLUDE_DIRS}
    src/ui/
    src/app/common/
    src/app/acquisition/
    src/app/visualisation/
)

# Include Qt
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

# Include threads
find_package(Threads)
if(UNIX)
set(APP_LIBS ${APP_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif(UNIX)

#Include Opencv
find_package(OpenCV REQUIRED)

# set includes
include_directories( ${APP_INCLUDE_DIRS} )

# create exe
add_executable(EyeTracking src/main.cpp ${APP_SOURCES} )
# link libs
target_link_libraries(EyeTracking Qt5::Widgets Qt5::Core Qt5::Multimedia ${OpenCV_LIBS} ${APP_LIBS} )

# copy stylesheets
file(COPY BFH.stylesheet DESTINATION ${PROJECT_BINARY_DIR})
# copy cascade files
file(COPY src/files DESTINATION ${PROJECT_BINARY_DIR})
# copy image files
file(COPY src/images DESTINATION ${PROJECT_BINARY_DIR})
