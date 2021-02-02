import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: wmsInfo
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()

    property alias content: info.text
    property alias header: header.text

    GridLayout {
       id: content
       columns: 1
       anchors.fill: parent

        Text {
            id: header
            text: qsTr("Hilfe")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: 18
            font.bold: true
            color: wmsStyle.getForegroundColor()
        }

        TextEdit {
            id: info
            color: "white"
            textFormat: TextEdit.RichText
            readOnly: true
        }
    }

    function cancelClicked() {
        modulesSelectionArea.enabled = true;
        restoreLastView();
    }
}
