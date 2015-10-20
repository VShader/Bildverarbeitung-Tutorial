cmake_minimum_required(VERSION 3.3)
project(BV_Praktikum)

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
	