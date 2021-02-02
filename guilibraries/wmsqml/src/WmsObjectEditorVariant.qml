import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.2

WmsObjectEditorValue {
    id: wmsObjectEditorVariant

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
            width: wmsApp.getCentralWindow().width * 0.20
            text: qsTr("Name")
            color: wmsStyle.getForegroundColor()
            font.bold: true;
            font.pointSize:  wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale()
        }

        TextField {
            id: editValueTextEdit
            anchors.left: caption.right
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 20
            readOnly: false;
            enabled: true;
            placeholderText: qsTr("Wert")
            Layout.fillWidth: true
            font.pointSize:  wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale()
            onTextChanged: {
                if (getValue() !== editValueTextEdit.text) {
                    updateValue(editValueTextEdit.text);
                }
            }
        }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        editValue = getValue();//.toLocaleString(Qt.locale());
        captionValue = getCaption();

    }

    function updateData() {
        // does nothing
    }
}
