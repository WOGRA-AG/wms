import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


Item {
    id: wmsContainerEditorDelegate
    width: parent.width
    height: itemLayout.getHeight()
    clip: true

    property alias text: contentText.text
    signal editClicked(int index)
    signal deleteClicked(int index)

    Rectangle {
        anchors.fill: parent
        color: wmsStyle.getSelectionColor()
        visible: mouse.pressed
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
           wmsContainerEditorDelegate.editClicked(index);
        }
    }

    GridLayout {
        id: itemLayout
        columns: 2
        anchors.fill: parent

        Text {
            id: contentText
            text: DisplayString
            color:  wmsStyle.getForegroundColor()
            Layout.fillWidth: true
        }

        Rectangle {
            id: commands
            color: wmsStyle.getBackgroundColor()
            width: wmsStyle.getNavigationBarSize()
            height: 50
            anchors.right: parent.right

            ColumnLayout {

                anchors.fill: parent

                ToolButton {
                    id: editButton
                    iconSource: "../icons/edit32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsContainerEditorDelegate.editClicked(index);
                }

                ToolButton {
                    id: deleteButton
                    iconSource: "../icons/delete32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsContainerEditorDelegate.deleteClicked(index);
                }
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 15
            height: 1
            color: wmsStyle.getSeperatorColor()
        }

        function getHeight() {
            if (contentText.contentHeight > commands.height) {
                return contentText.contentHeight + 10
            } else {
                return commands.height + 10
            }
        }
    }


}
