import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1024
    height: 768

    Rectangle {
        anchors.centerIn: parent
        width: parent.width/2
        height: parent.height/2
        Image {
            // without this image will have unwanted size
            anchors.fill: parent

            // without thie, image might be cutted.
            fillMode:Image.PreserveAspectFit
            source:"qrc:image.jpg"
        }
    }
}