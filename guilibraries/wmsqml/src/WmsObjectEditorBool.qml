import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

WmsObjectEditorValue {
    id: wmsObjectEditorBool
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     editValueBox.checked
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
           anchors.right: editValueBox.left
           anchors.leftMargin: 20
           width: 250
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
           font.bold: true;
       }

       CheckBox {
           id: editValueBox
           anchors.rightMargin: getRightMargin()

           onCheckedChanged: {
               setValueBool(editValue);
           }
       }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        editValue = getValueBool();
        captionValue = getCaption();
    }

    function updateData() {
        // does nothing
    }
}
