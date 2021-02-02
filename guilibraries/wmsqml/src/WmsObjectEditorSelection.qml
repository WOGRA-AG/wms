import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

WmsObjectEditorValue {
    id: wmsObjectEditorSelection
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     editValueBox.currentIndex
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

       ComboBox {
           id: editValueBox
           anchors.left: caption.right
           anchors.right: parent.right
           Layout.fillWidth: true
           anchors.rightMargin: getRightMargin()

           onActivated: {
               var selectedValue = editValueBox.model.get(editValue);

               if (selectedValue !== null) {
                   setSelectionValue(selectedValue.idValue);
               }
           }
       }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        captionValue = getCaption();
        var valueModel = initListModel();

        if (valueModel !== null) {
            editValueBox.textRole = "name";
            editValueBox.model = valueModel;
        }

        editValue = getSelectionValueIndex();
    }
}
