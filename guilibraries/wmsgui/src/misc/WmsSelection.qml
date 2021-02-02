import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0


Window {
    id: wmsSelection
    color: "#ffffff"
    minimumHeight: 200
    minimumWidth: 360
    flags: Qt.Dialog
    title: "Datenbankauswahl"

    // Define a delegate component.  A component will be
    // instantiated for each visible item in the list.
    Component {
        id: modelDelegate
        Item {
            id: wrapper
            width: listView.width; height: 20

            MouseArea {
                anchors.fill: parent
                onClicked: wrapper.ListView.view.currentIndex = index
                onDoubleClicked: {
                    wrapper.ListView.view.currentIndex = index;
                    ok();
                }
            }

            Row {
                anchors.fill: parent
                Text {
                    text: '<br><b>' + modelData + '</b>'
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                }
            }

            transitions: Transition {
                NumberAnimation { properties: "x"; duration: 200 }
            }
        }
    }

    //! [0]
    // Define a highlight with customized movement between items.
    Component {
        id: highlightBar
        Rectangle {
            width: listView.width;
            height: 30
            color: "lightsteelblue"
            y: listView.currentItem.y+5;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }


    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        scale: 1
        spacing: 3
        anchors.margins: 6

        Text {
            id: header
            text: qsTr("Datenbankauswahl")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: 18
            font.bold: true
            color: "blue"
            anchors.top: parent.top
        }

        GroupBox {
            id: logingroupbox
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.right: parent.right
            anchors.rightMargin: 3
            title: qsTr("Datenbankauswahl")
            height: 120


            ListView {
                id: listView
                anchors.fill: parent
                anchors.bottomMargin: 30
                model: selectionModel
                delegate: modelDelegate
                focus: true
                spacing: 10

                // Set the highlight delegate. Note we must also set highlightFollowsCurrentItem
                // to false so the highlight delegate can control how the highlight is moved.
                highlight: highlightBar
                highlightFollowsCurrentItem: false
            }
        }

        Item { Layout.fillHeight: true }

        RowLayout {
            id: buttonRow
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            Item { Layout.fillWidth: true }

            Button {
                id: cancelButton
                text: qsTr("Abbrechen")
                onClicked: {
                    hide();
                    listView.currentItem.
                    selector.Cancel();
                }
            }

            Button {
                id: okButton
                text: qsTr("OK")
                onClicked: ok();
            }
        }
    }

    function ok() {
        var dbName = selectionModel[listView.currentIndex];

        if (selector.LoadSelection(dbName))
        {
            selector.Ok();
            hide();
        }
    }
}

