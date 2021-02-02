import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

WmsObjectEditorValue {
    id: wmsObjectEditorBinDoc
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     editValueTextEdit.text
    property alias captionValue:  caption.text


    GridLayout {
       id: content
       columns: 4
       anchors.fill: parent

       Text {
           id: caption
           text: qsTr("Name")
           verticalAlignment: Text.AlignVCenter
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.bottom: parent.bottom
           anchors.right: editValueTextEdit.left
           anchors.leftMargin: 20
           width: 250
           color: wmsStyle.getForegroundColor()
           font.bold: true;
       }

       TextField {
           id: editValueTextEdit
           anchors.left: caption.right;
           anchors.right: openButton.left
           placeholderText: qsTr("Datei")
           Layout.fillWidth: true
           readOnly: true
       }

       Button {
           id: openButton
           text: qsTr("Öffnen")
           width: 40
           anchors.right: parent.right
           anchors.rightMargin: getRightMargin()

           onClicked: {
                openBinDoc();
           }
       }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        editValue = getBinDocFilename();
        captionValue = getCaption();
    }

    function updateData() {
        // does nothing
    }
}
