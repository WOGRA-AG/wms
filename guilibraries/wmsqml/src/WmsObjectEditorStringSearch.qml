import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Rectangle {
    id: wmsObjectEditorStringSearch
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editValue:     editValueTextEdit.text
    property alias captionValue:  caption.text
    property alias searchPropertyValue:  searchPropertyBox.index

    GridLayout {
       id: content
       columns: 3
       anchors.fill: parent

       Text {
           id: caption
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
       }

       ComboBox {
           id: searchPropertyBox
           model: ListModel {
                   id: cbItems
                   ListElement { text: qsTr("Beginnt mit");}
                   ListElement { text: qsTr("Enthält");}
                   ListElement { text: qsTr("Gleich");}
                   ListElement { text: qsTr("Endet mit");}
               }
       }

       TextField {
           id: editValueTextEdit
           placeholderText: qsTr("Applikationsname")
           Layout.fillWidth: true
           readOnly: true
       }
    }
}
