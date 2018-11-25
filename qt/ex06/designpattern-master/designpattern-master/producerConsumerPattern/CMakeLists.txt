cmake_minimum_required(VERSION 2.8.11)

# project name is Producer-Consumer-Pattern
project(PCP)

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


SET( APP_SOURCES )
SET( APP_INCLUDE_DIRS )
SET( APP_LIBS )

# main sources
SET( APP_SOURCES ${APP_SOURCES}
    src/ui/IWidget.h
    src/ui/widget.cpp
    src/ui/widget.h
    src/ui/widget.ui
    src/app/common/control.cpp
    src/app/common/control.h
    src/app/common/dataBuffer.cpp
    src/app/common/dataBuffer.h
    src/app/common/dataBufferPool.cpp
    src/app/common/dataBufferPool.h
    src/app/acquisition/VCamera.cpp
    src/app/acquisition/VCamera.h
    src/app/acquisition/icamera.h
    src/app/visualisation/videoVisualizer.cpp
    src/app/visualisation/videoVisualizer.h
    src/app/visualisation/rOg_image.cpp
    src/app/visualisation/rOg_image.h
)


SET( APP_INCLUDE_DIRS ${APP_INCLUDE_DIRS}
    src/ui/
    src/app/common/
    src/app/acquisition/
    src/app/visualisation/
)

# Include Qt
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

# Include threads
FIND_PACKAGE(Threads)
IF(UNIX)
SET(APP_LIBS ${APP_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
ENDIF(UNIX)

# set includes
include_directories( ${APP_INCLUDE_DIRS} )

# create exe
add_executable(PCP src/main.cpp ${APP_SOURCES} )
# link libs
target_link_libraries(PCP Qt5::Widgets Qt5::Core ${APP_LIBS} )

# copy stylesheets
file(COPY BFH.stylesheet DESTINATION ${PROJECT_BINARY_DIR})
