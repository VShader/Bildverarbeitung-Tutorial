import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: item1
    width: 550
    height: 400

    property alias redImage: redImage
    property alias greenImage: greenImage
    property alias blueImage: blueImage
    property alias redGrayImage: redGrayImage
    property alias greenGrayImage: greenGrayImage
    property alias blueGrayImage: blueGrayImage
    property alias item1: item1
    property alias mouseArea1: mouseArea1


    MouseArea {
        id: mouseArea1
        anchors.fill: parent

        Item {
            id: item2
            anchors.fill: parent

            Button {
                id: button1
                x: 223
                y: 344
                text: qsTr("Switch State")
                onClicked: item1.state = "State1"
            }

            Image {
                id: image1
                x: 157
                y: 48
                width: 208
                height: 255
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }

        Item {
            id: item3
            anchors.fill: parent
            visible: false
            Image {
                id: redGrayImage
                x: 46
                y: 64
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Image {
                id: redImage
                x: 46
                y: 203
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Image {
                id: greenGrayImage
                x: 210
                y: 64
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Image {
                id: greenImage
                x: 210
                y: 203
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Image {
                id: blueGrayImage
                x: 365
                y: 64
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Image {
                id: blueImage
                x: 365
                y: 203
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            Label {
                id: label7
                x: 75
                y: 45
                text: qsTr("Rotkanal")
            }

            Label {
                id: label8
                x: 37
                y: 184
                text: qsTr("Rotkanal - rot eingefärbt")
            }

            Label {
                id: label9
                x: 236
                y: 45
                text: qsTr("Grünkanal")
            }

            Label {
                id: label10
                x: 194
                y: 184
                text: qsTr("Grünkanal - grün eingefärbt")
            }

            Label {
                id: label11
                x: 391
                y: 45
                text: qsTr("Blaukanal")
            }

            Label {
                id: label12
                x: 351
                y: 184
                text: qsTr("Blaukanal - blau eingefärbt")
            }

            ColumnLayout {
            }

            Button {
                id: button2
                x: 223
                y: 344
                text: qsTr("Switch State")
                onClicked: item1.state = "default state"
            }
        }

    }
    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: item1
                visible: true
            }

            PropertyChanges {
                target: button1
                visible: true
            }

            PropertyChanges {
                target: item3
                visible: true
            }

            PropertyChanges {
                target: item2
                visible: false
            }
        }
    ]
}

