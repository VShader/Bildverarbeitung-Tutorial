project(Aufgabe2)


set(src
	src/aufgabe2.cpp	
)

set(resources ${resources}
	${images}/Aufgabe1.jpg
)


add_executable(${PROJECT_NAME} ${src} ${resources})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>: -DQT_QML_DEBUG>)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Core Qt5::Qml Qt5::Gui Qt5::Widgets)

	
