import QtQuick 2.2


Item {
    id: moduleSelectionDelegate

    property alias text: textitem.text
    signal clicked
    width: parent.width;
    height: textitem.height + 20



    Rectangle {
        anchors.fill: parent
        color: wmsStyle.getSelectionColor()
        visible: mouse.pressed
    }

    Image {
        id: myIcon
        anchors {
            left: parent.left
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        width: wmsApp.getCentralWindow().width < 500 ? 32 : 12 + wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
        height: wmsApp.getCentralWindow().width < 500 ? 32 : 12 + wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
        //source: "data:image/png;base64," + Icon
        source: "../icons/exit24.png"
    }

    Text {
        id: textitem
        anchors {
            left: myIcon.right;
            leftMargin: 10
            verticalCenter: parent.verticalCenter
        }
        font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
        text: Name
        color: wmsStyle.getNavigationBarTextColor()
    }

    MouseArea {
        id: mouse
        anchors.fill: parent

        onClicked: {
            moduleSelectionDelegate.ListView.view.currentIndex = index;
            moduleSelectionDelegate.clicked();
        }
    }
}

