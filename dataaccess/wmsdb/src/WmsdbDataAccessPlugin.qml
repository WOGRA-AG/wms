import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import QtQuick.Controls.Styles 1.3


Rectangle {
    id: wmsDbConfigurator
    color: wmsStyle.getBackgroundColor()
    height: wmsStyle.getContentHeight()
    width: wmsStyle.getContentWidth()
    //width: 360
    //height: 320

    ColumnLayout {
        id: mainlayout
        anchors.fill: parent
        scale: 1

        Text {
            id: header
            text: qsTr("Datenbank Einstellungen")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getTextScale()
            font.bold: true
            color: wmsStyle.getForegroundColor()
        }

        GroupBox {
            id: connectionGroupbox
            anchors { top: header.bottom; left: parent.left; right: parent.right
                topMargin: Math.round(wmsApp.getCentralWindow().width * 1.5625) / 100
                leftMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                rightMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
            }

            GridLayout {
                id: grid_layout1
                anchors.fill: parent
                anchors.margins: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                columns: 2
                rows: 6

                Text {
                    id: driverText
                    text: qsTr("Treiber")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                WmsComboBox {
                    id: driverComboBox
                    Layout.fillWidth: true
                    model: settings.getDrivers()
                    currentIndex: settings.getDriverIndex()
                }


                Text {
                    id: databaseText
                    text: qsTr("Datenbankname")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                TextField {
                    id: databaseTextField
                    Layout.fillWidth: true
                    text: settings.getDatabase()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                Text {
                    id: serverText
                    text: qsTr("Server")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                TextField {
                    id: serverTextField
                    Layout.fillWidth: true
                    text: settings.getServer()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                Text {
                    id: portText
                    text: qsTr("Port")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                SpinBox {
                    id: portSpinBox
                    Layout.fillWidth: true
                    value: settings.getPort()
                    maximumValue: 66000
                    minimumValue: 0
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

//                WmsSpinBox {
//                    id: portSpinBox
//                    Layout.fillWidth: true
//                    value: settings.getPort()
//                }

                Text {
                    id: userText
                    text: qsTr("Benutzer")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                TextField {
                    id: userTextField
                    Layout.fillWidth: true
                    text: settings.getUser()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                Text {
                    id: passwordText
                    text: qsTr("Paswort")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                TextField {
                    id: passwordTextField
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    text: settings.getPassword()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                Text {
                    id: connectionOptionsText
                    text: qsTr("Verbindungsoptionen")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }

                TextField {
                    id: connectionOptionsTextField
                    Layout.fillWidth: true
                    text: settings.getConnectOptions()
                    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
                }
            }
        }

        Text {
            id: labelTestResult
            color: wmsStyle.getErrorTextColor()
            visible: false
            anchors { top: connectionGroupbox.bottom; left: parent.left; right: parent.right
                topMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                leftMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                rightMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
            }
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
        }

        Item { Layout.fillHeight: true }

        Rectangle {
            Layout.fillWidth: true
            anchors.bottom: parent.bottom
            implicitHeight: wmsApp.getCentralWindow().width < 500 ? wmsStyle.getNavigationBarSize() : 20 + wmsApp.getCentralWindow().width * wmsStyle.getTextScale()
            color: wmsStyle.getNavigationBarColor();

            RowLayout {
                id: buttonRow
                anchors.fill: parent
                anchors.leftMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100
                anchors.rightMargin: Math.round(wmsApp.getCentralWindow().width * 0.78125) / 100

                Item { Layout.fillWidth: true }

                ToolButton {
                    id: cancelButton
                    text: qsTr("Abbrechen")
                    implicitWidth: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    implicitHeight: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    Image {
                        id: cancelButtonImage
                        source: wmsStyle.getCancelButton()
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                        anchors.fill: parent
                    }
                    onClicked: {
                        openPageFile("WmsDataAccessConfiguration.qml");
                    }

                }

                ToolButton {
                    id: testButton
                    text: qsTr("Test")
                    implicitWidth: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    implicitHeight: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    Image {
                        id: testButtonImage
                        source: "../icons/reports32.png"
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                        anchors.fill: parent
                    }
                    onClicked: {
                        if (settings.testDatabaseConnection(serverTextField.text,
                                                            databaseTextField.text,
                                                            portSpinBox.value,
                                                            driverComboBox.currentText,
                                                            userTextField.text,
                                                            passwordTextField.text,
                                                            connectionOptionsTextField.text) == true) {

                            labelTestResult.color = wmsStyle.getForegroundColor();
                            labelTestResult.visible = true;
                            labelTestResult.text = qsTr("Datenbankverbindung wurde erfolgreich aufgebaut.");

                        } else {
                            labelTestResult.color = wmsStyle.getErrorTextColor();
                            labelTestResult.visible = true;
                            labelTestResult.text = qsTr("Datenbankverbindung konnte nicht aufgebaut werden.");
                        }

                    }

                }

                ToolButton {
                    id: okButton
                    text: qsTr("OK")
                    implicitWidth: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    implicitHeight: mainlayout.width < 500 ? 32 : 12 + mainlayout.width * wmsStyle.getTextScale()
                    Image {
                        id: okButtonImage
                        source: wmsStyle.getOkButton();
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                        anchors.fill: parent
                    }
                    onClicked: {
                        // Save Data
                        settings.setDriver(driverComboBox.currentText);
                        settings.setDatabase(databaseTextField.text);
                        settings.setServer(serverTextField.text);
                        settings.setPort(portSpinBox.value);
                        settings.setUser(userTextField.text);
                        settings.setPassword(passwordTextField.text);
                        settings.setConnectOptions(connectionOptionsTextField.text);
                        openPageFile("WmsDataAccessConfiguration.qml");
                    }

                }
            }
        }
    }
}

