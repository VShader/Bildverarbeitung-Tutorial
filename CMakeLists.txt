cmake_minimum_required(VERSION 3.3)
project(BV_Praktikum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenCV REQUIRED )
find_package(Qt5 REQUIRED Core Qml Gui Widgets)

include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


set(images
	${CMAKE_CURRENT_SOURCE_DIR}/images
)

set(resources
	${CMAKE_CURRENT_SOURCE_DIR}/configs.h.in
)

configure_file(configs.h.in ${CMAKE_CURRENT_BINARY_DIR}/configs.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Aufgabe1)
add_subdirectory(Aufgabe2)
add_subdirectory(Aufgabe3)
	
