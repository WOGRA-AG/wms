import QtQuick 2.2

Rectangle {
    id: wmsRuntimeFunctions
    color: "white"

    ListModel {
        id: appModel
        ListElement { name: "Configuration"; icon: "bold.png" }
        ListElement { name: "Change Password"; icon: "redo.png" }
        ListElement { name: "Help"; icon: "undo.png" }
        ListElement { name: "Info"; icon: "insert.png" }
        ListElement { name: "Select Language"; icon: "color.png" }
    }

    Component {
        id: appDelegate
        Item {
            width: 100; height: 100
            scale: PathView.iconScale

            Image {
                id: myIcon
                y: 20; anchors.horizontalCenter: parent.horizontalCenter
                source: icon
            }
            Text {
                anchors { top: myIcon.bottom; horizontalCenter: parent.horizontalCenter }
                text: name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }
        }
    }

    Component {
        id: appHighlight
        Rectangle { width: 80; height: 80; color: "lightsteelblue" }
    }

    PathView {
        id: view
        anchors.fill: parent
        highlight: appHighlight
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        focus: true
        model: appModel
        delegate: appDelegate
        path: Path {
            startX: 10
            startY: 50
            PathAttribute { name: "iconScale"; value: 0.5 }
            PathQuad { x: 200; y: 150; controlX: 50; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 1.0 }
            PathQuad { x: 390; y: 50; controlX: 350; controlY: 200 }
            PathAttribute { name: "iconScale"; value: 0.5 }
        }
    }
}

