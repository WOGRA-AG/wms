import QtQuick 2.2


Item {
    id: root
    width: parent.width
    height: textitem.height + 20

    property alias text: textitem.text
    signal clicked

    Text {
        id: textitem
        color: wmsStyle.getForegroundColor()
        text: modelData
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        font.pointSize:  wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale()
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        height: 1
        color: wmsStyle.getSeperatorColor()
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

