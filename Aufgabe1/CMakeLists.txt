cmake_minimum_required(VERSION 3.3)
project(Aufgabe1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(OpenCV REQUIRED )
find_package(Qt5 REQUIRED Core Qml Gui Widgets)

set(src
    src/aufgabe1.cpp
)

set(ui
    ui/RGBchannels.qml
    ui/RGBchannelsForm.ui.qml
)

set(resources ${resources}
    ${images}/Aufgabe1.jpg
    resources.qrc

)

include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

QT5_ADD_RESOURCES(resources resources.qrc)

add_executable(${PROJECT_NAME} ${src} ${ui} ${resources})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Core Qt5::Qml Qt5::Gui Qt5::Widgets)

	
