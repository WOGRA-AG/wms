import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import com.wogra.wmscore 1.0

Rectangle {
    id: wmsClassSelection
    color: wmsStyle.getBackgroundColor()
    anchors.fill: parent

    signal classSelected;
    signal selectionCanceled;

    GridLayout {
        id: selectionLayout
        columns: 1

        Text {
            id: header
            text: qsTr("Bitte Klasse auswählen")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: 18
            font.bold: true
            color:  wmsStyle.getForegroundColor()
            anchors.top: parent.top
        }

        ScrollView {
            anchors.left: parent.left
            anchors.leftMargin: 3
            anchors.right: parent.right
            anchors.rightMargin: 3
            anchors.top: header.bottom
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
                    text: modelData.getKeyname()
                    onClicked: {
                      //  ok();
                    }
                }

                focus: true
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

        /*
        CheckBox: {
            id: showTechnicalClassesCheckBox
            checked: false
            text: qsTr("Technische Klassen darstellen");
        }
        */

        Rectangle {
            id: buttonRect
            color:  wmsStyle.getNavigationBarColor()
            height: wmsStyle.getNavigationBarSize()
            Layout.fillWidth: true
            anchors.bottom: parent.botom

            RowLayout {
                id: buttonRow
                anchors.fill: parent

                ToolButton {
                    id: cancelButton
                    iconSource: wmsStyle.getCancelButton()
                    onClicked: {
                        // hide();
                    }
                }

                ToolButton {
                    id: okButton
                    iconSource: wmsStyle.getOkButton()
                    onClicked: {
                        // todo
                    }
                }

                Item { Layout.fillWidth: true }

            }
        }
    }


    function fillData(){
        var classManager = wmsFactory.getClassManager();

        if (classManager !== null) {
            listView.model = classManager.getClassList();
        }
    }
}
