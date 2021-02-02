import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1


WmsObjectEditorValue {
    id: wmsObjectEditorVariant
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()
    property alias captionValue:  caption.text

    Component {
        id: lvDelegateComp

        //property alias text: lvDelegate.text;
        //signal clicked;

        Item {
            id: lvDelegate
            width: parent.width
            height: 30

            property alias text: textitem.text;
            signal clicked;

            Text {
                id: textitem
                color: wmsStyle.getForegroundColor()
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
                text: name
            }

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 15
                height: 1
                color: wmsStyle.getSeperatorColor()
            }

            MouseArea {
                id: mouse
                anchors.fill: parent
                onClicked: {
                    lvDelegate.ListView.view.currentIndex = index
                    //lvDelegate.clicked()
                }
            }
        }
    }

    Component {
        id: highlightBar
        Rectangle {
            //width: parent.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 15
            height: 30
            color: wmsStyle.getSelectionColor()
            y: listView.currentItem.y;

            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }

    GridLayout {
       id: content
       columns: 1
       anchors.fill: parent

       Text {
           id: caption
           verticalAlignment: Text.AlignVCenter
           horizontalAlignment: Text.AlignHCenter
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.right: parent.right
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
           height: 40
       }

       ScrollView {
           id: scrollView
           anchors.left: parent.left
           anchors.leftMargin: 3
           anchors.right: parent.right
           anchors.rightMargin: 3
           anchors.top: caption.bottom
           anchors.topMargin: 10
           anchors.bottom: commandsRect.top
           width: parent.width
           Layout.fillWidth: true
           Layout.fillHeight: true
           flickableItem.interactive: true

           ListView {
               id: listView
               anchors.fill: parent
               Layout.fillWidth: true
               focus: true
               delegate: lvDelegateComp
               highlight: highlightBar
               highlightFollowsCurrentItem: true
           }

           style: ScrollViewStyle {
               transientScrollBars: true
               handle: Item {
                   implicitWidth: 14
                   implicitHeight: 26
                   Rectangle {
                       color: wmsStyle.getScrollbarColor()
                       anchors.fill: parent
                       anchors.topMargin: 6
                       anchors.leftMargin: 4
                       anchors.rightMargin: 4
                       anchors.bottomMargin: 6
                   }
               }
               scrollBarBackground: Item {
                   implicitWidth: 14
                   implicitHeight: 26
               }
           }
        }

       Rectangle {
           id: commandsRect
           anchors.left: parent.left
           anchors.right: parent.right
           anchors.bottom: parent.bottom
           color: wmsStyle.getBackgroundColor()
           anchors.leftMargin: 3
           anchors.bottomMargin: 3
           height: wmsStyle.getNavigationBarSize()

           RowLayout {
               anchors.fill: parent

               TextField {
                   id: newValue
                   placeholderText: qsTr("Wert")
                   Layout.fillWidth: true
               }

               ToolButton {
                   id: addButton
                   iconSource: "../icons/new32.png"
                   onClicked: addClicked();
               }

               ToolButton {
                   id: removeButton
                   iconSource: "../icons/delete32.png"
                   onClicked: removeClicked();
               }

               Item {
                   id: spacer
                   Layout.fillWidth: true
                   visible: false
               }
           }
       }
    }

    function fillData(valueElement) {
        console.log("ObjectList in fillData()")
        setValue(valueElement);
        listView.model = initListModel();
        captionValue = getCaption();

        if (isListOfObjects()) {
            newValue.visible = false;
            spacer.visible = true
        }
    }

    function updateData() {
        // does nothing
    }

    function addClicked() {

        if (isListOfObjects()) {
            var selectedClass = getClass();
        } else {
            var editValue = newValue.text;
            if (addListValue(editValue) === true) {
                listView.model.append({"name": editValue});
                newValue.text = "";
                console.log("Value successfully added");
            } else {
                console.log("Add failed");
            }
        }
    }

    function removeClicked() {
        console.log("Remove Clicked");
        var removeValue;

        if (isListOfObjects()) {
            removeValue = listView.model.get(listView.currentIndex).idValue;
        } else {
            removeValue = listView.model.get(listView.currentIndex).name;
        }

        console.log("Value to remove: " + removeValue);

        if (removeListValue(removeValue) === true) {
            listView.model.remove(listView.currentIndex, 1);
            console.log("Value successfully removed");
        } else {
            console.log("Remove failed");
        }
    }

    function getClass() {
        selectionLoader.setSource("WmsClassSelection.qml");
        selectionLoader.item.fillData();


    }
}
