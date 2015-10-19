cmake_minimum_required(VERSION 3.3)
project(Aufgabe1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenCV REQUIRED )
#find_package(Qt5Widgets REQUIRED )

set(src
	src/aufgabe1.cpp	
)

set(resources ${resources}
	${images}/Aufgabe1.jpg
)

include_directories( ${OpenCV_INCLUDE_DIRS} )
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} ${src} ${resources})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})
#target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Widgets )

	