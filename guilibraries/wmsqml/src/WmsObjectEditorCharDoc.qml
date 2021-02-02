import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.3

WmsObjectEditorValue {
    id: wmsObjectEditorCharDoc
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     textEditor.text
    property alias captionValue:  caption.text

    GridLayout {
       id: content
       columns: 1
       anchors.fill: parent

       Text {
           id: caption

           verticalAlignment: Text.AlignVCenter
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.bottom: textEditor.top
           anchors.right: parent.right
           anchors.leftMargin: 20
           width: 250
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
           font.bold: true;
           visible: false
       }

        WmsTextEditor {
            id: textEditor;
            anchors.left: parent.left
            anchors.top: parent.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: getRightMargin()
            anchors.leftMargin: getLeftMargin()
            Layout.fillWidth: true
            Layout.fillHeight: true

            onTextChanged: {

                if (getValue() !== textEditor.text) {
                     updateValue(textEditor.text);
                }
                /*
                if (getValue() !== editValue) {
                     updateValue(editValue);
                }
                */
            }
        }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        editValue = getValue();
        captionValue = getCaption();
    }

    function updateData() {
        if (getValue() !== editValue) {
             updateValue(editValue);
        }
    }
}
