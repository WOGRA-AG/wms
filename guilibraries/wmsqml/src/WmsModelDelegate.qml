import QtQuick 2.2


Item {
    id: root
    width: parent.width
    height: content.height * 0.25


    property alias text: textitem.text
    signal clicked

    Rectangle {
        anchors.fill: parent
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        color: wmsStyle.getSelectionColor()
        visible: mouse.pressed
    }

    Text {
        id: textitem
        color: wmsStyle.getForegroundColor()
        font.pointSize: content.width * wmsStyle.getSubtitleScale()
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        height: 1
        color: wmsStyle.getSeperatorColor()
    }

    Image {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        source: "../icons/arrow-right32.png"
        width: content.width < 500 ? 32 : 12 + content.width * wmsStyle.getTextScale()
        height: content.width < 500 ? 32 : 12 + content.width * wmsStyle.getTextScale()
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
            root.ListView.view.currentIndex = index
            root.clicked()
        }
    }
}

