project(Aufgabe1)


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


QT5_ADD_RESOURCES(resources resources.qrc)

add_executable(${PROJECT_NAME} ${src} ${ui} ${resources})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>: -DQT_QML_DEBUG>)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Core Qt5::Qml Qt5::Gui Qt5::Widgets)

	
