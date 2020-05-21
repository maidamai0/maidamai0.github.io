import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

Window {
    visible: true
    width: 1024
    height: 768

    Video {
        id:rect
        anchors.centerIn: parent
        width: parent.width * 0.9
        height: parent.height * 0.9
        source:"file:///D:/open_source_project/maidamai0.github.io/build/code/qml_video/video.avi"
        autoPlay: true
    }

    
    Component.onCompleted: {
        console.log("completed")
    }
    
}