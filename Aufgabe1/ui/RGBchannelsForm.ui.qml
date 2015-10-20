import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: 550
    height: 400

    property alias redImage: redImage
    property alias greenImage: greenImage
    property alias blueImage: blueImage
    property alias redGrayImage: redGrayImage
    property alias greenGrayImage: greenGrayImage
    property alias blueGrayImage: blueGrayImage

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
        id: label1
        x: 75
        y: 45
        text: qsTr("Rotkanal")
    }

    Label {
        id: label2
        x: 37
        y: 184
        text: qsTr("Rotkanal - rot eingefärbt")
    }

    Label {
        id: label3
        x: 236
        y: 45
        text: qsTr("Grünkanal")
    }

    Label {
        id: label4
        x: 194
        y: 184
        text: qsTr("Grünkanal - grün eingefärbt")
    }

    Label {
        id: label5
        x: 391
        y: 45
        text: qsTr("Blaukanal")
    }

    Label {
        id: label6
        x: 351
        y: 184
        text: qsTr("Blaukanal - blau eingefärbt")
    }
}

