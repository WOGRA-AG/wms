import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1


Rectangle {
    id: content
    color: wmsStyle.getBackgroundColor()
    height: wmsStyle.getContentHeight()
    width: wmsStyle.getContentWidth()

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        columns: 1

        Text {
            id: header
            text: qsTr("Auswahl")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getHeaderScale()
            font.bold: true
            color:  wmsStyle.getForegroundColor()
            anchors.top: parent.top

        }

        ScrollView {
            anchors.left: parent.left
            anchors.leftMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
            anchors.right: parent.right
            anchors.rightMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
            anchors.top: header.bottom
            anchors.topMargin: Math.round(wmsApp.getCentralWindow().width * 1.5625) / 100
            anchors.bottom: buttonRect.top
            width: parent.width
            height: parent.height
            Layout.fillWidth: true
            Layout.fillHeight: true
            flickableItem.interactive: true

            ListView {
                id: listView
                anchors.fill: parent
                model: wmsApp.getSelectionList();
                delegate: WmsModelDelegate {
                    text: modelData
                    onClicked: {
                        ok();
                    }
                }
                focus: true
                boundsBehavior: Flickable.StopAtBounds;
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
            id: buttonRect
            color:  wmsStyle.getNavigationBarColor()
            implicitHeight: content.width < 500 ? wmsStyle.getNavigationBarSize() : 20 + content.width * wmsStyle.getTextScale()
            Layout.fillWidth: true
            anchors.bottom: parent.bottom

            RowLayout {
                id: buttonRow
                anchors.fill: parent
                anchors.leftMargin: Math.round(content.width * 0.78125) / 100
                anchors.rightMargin: Math.round(content.width * 0.78125) / 100

                WmsToolButton {
                    id: cancelButton
                    text: qsTr("Abbrechen")
                    image: wmsStyle.getCancelButton()
                    parentWindow: content.width
                    onClicked: {
                        hide();
                        wmsLogin.cancel();
                    }
                }

                Item { Layout.fillWidth: true }

            }
        }
    }

    function ok() {
        var dbName = listView.model[listView.currentIndex];
        console.log(dbName);
        wmsApp.loadSelection(dbName);
        //console.log("Selection finished");

        if (wmsApp.needsSelection() === true) {

            //console.log("Continue with next selection");

            //openPageFile("WmsSelection.qml");
            listView.model = wmsApp.getSelectionList();
        } else {
            loadMainWindow();
        }
    }
}

