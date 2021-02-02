import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Controls.Styles 1.3


Rectangle {
    id: content
    color: "#212126"
    height: wmsStyle.getContentHeight()
    width: wmsStyle.getContentWidth()

    GridLayout {
        id: mainlayout
        anchors.fill: parent
        columns: 1

        Text {
            id: header
            text: qsTr("Datenzugriff")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getHeaderScale()
            font.bold: true
            color: "white"
        }

        GroupBox {
            id: connectionGroupbox
            Layout.fillWidth: true
            anchors { top: header.bottom; left: parent.left; right: parent.right
                topMargin: Math.round(wmsApp.getCentralWindow().width * 1.5625) / 100
                leftMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                rightMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
            }

            GridLayout {
                id: grid_layout1
                anchors.fill: parent
                anchors.margins: 3
                columns: 3
                rows: 1

                Text {
                    id: text1
                    text: qsTr("Methode")
                    color: "white"
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getTextScale()
                }

                WmsComboBox {
                    id: dataAccessType
                    Layout.fillWidth: true
                    model: wmsDataAccessModel
                    currentIndex: wmsConfig.getCurrentDataAccessConfigurationIndex();
                }

                WmsToolButton {
                    id: wmsConfigureButton
                    text: qsTr("Konfiguration")
                    image: "../icons/settings32.png"
                    parentWindow: wmsApp.getCentralWindow().width
                    onClicked: {
                        var ui = wmsApp.getClientConfigurationQmlDialog(dataAccessType.currentText);
                        console.log(ui);

                        if (ui.length > 0) {
                            openPageFile(ui);
                        }
                    }
                }
            }
        }

        Item { Layout.fillHeight: true }

        Rectangle {
            id: buttonRect
            color: "#c6c8ca"
            implicitHeight: wmsApp.getCentralWindow().width < 500 ? wmsStyle.getNavigationBarSize() : 20 + wmsApp.getCentralWindow().width * wmsStyle.getTextScale()
            Layout.fillWidth: true
            anchors.bottom: parent.botom

            RowLayout {
                id: buttonRow
                anchors.fill: parent;
                anchors.leftMargin: Math.round(content.width * 0.78125) / 100
                anchors.rightMargin: Math.round(content.width * 0.78125) / 100

                Item { Layout.fillWidth: true }

                WmsToolButton {
                    id: cancelButton
                    text: qsTr("Abbrechen")
                    image: wmsStyle.getCancelButton()
                    parentWindow: wmsApp.getCentralWindow().width
                    onClicked: {
                        openPageFile("WmsLogin.qml");
                    }
                }

                WmsToolButton {
                    id: okButton
                    text: qsTr("OK")
                    image: wmsStyle.getOkButton()
                    parentWindow: wmsApp.getCentralWindow().width
                    onClicked: {
                        wmsConfig.setDataAccessConfiguration(dataAccessType.currentText);
                        openPageFile("WmsLogin.qml");
                    }
                }
            }
        }
    }
}

