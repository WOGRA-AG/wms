import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

WmsObjectEditorValue {
    id: wmsObjectEditorVariant
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     editValueTextEdit.text
    property alias captionValue:  caption.text


    GridLayout {
       id: content
       columns: 2
       anchors.fill: parent

       Text {
           id: caption

           verticalAlignment: Text.AlignVCenter
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.bottom: parent.bottom
           anchors.right: editValueTextEdit.left
           anchors.leftMargin: 20
           width: 250
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
       }

       TextField {
           id: editValueTextEdit
           placeholderText: qsTr("Liste TODO")
           Layout.fillWidth: true
           readOnly: true
       }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        editValue = getValue();
        captionValue = getCaption();
    }

    function updateData() {
        // does nothing
    }
}
