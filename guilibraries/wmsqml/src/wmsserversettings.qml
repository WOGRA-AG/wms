import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0



Window {
    id: wmsServerSettings
    color: "#ffffff"
    flags: Qt.Dialog
    title: qsTr("Server Einstellungen")
    minimumWidth: 520
    minimumHeight: 600

    signal openDataAccess();

    FileDialog {
        id: fileDialog
        title: qsTr("Bitte wählen Sie eine Datei.")
        modality: Qt.WindowModal
        selectMultiple: false
        selectFolder: false
        selectExisting: true
        nameFilters: [ "Text files (*.txt *.log)", "All files (*)" ]

        onAccepted: {
            filePathTextField.text = fileUrl;
        }
        onRejected: {
            close();
        }
    }

    ColumnLayout {
        id: mainlayout
        anchors.fill: parent
        scale: 1
        spacing: 3
        anchors.margins: 6

        Text {
            id: header
            text: qsTr("Server Einstellungen")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: 18
            font.bold: true
            color: "blue"
        }

        GroupBox {
            id: connectionGroupbox
            anchors.left: parent.left
            anchors.right: parent.right
            title: qsTr("Verbindung")

            GridLayout {

                id: grid_layout1
                anchors.fill: parent
                anchors.margins: 3
                columns: 2
                rows: 5

                Text {
                    id: text1
                    text: qsTr("Port")
                }

                SpinBox {
                    id: portSpinBox
                    Layout.fillWidth: true
                    value: settings.getSettingsValueSlot("Config_Port");
                    minimumValue: 0
                    maximumValue: 999999
                }

                Text {
                    id: text2
                    text: qsTr("SSL Verbindung")
                    Layout.fillWidth: true
                }

                CheckBox {
                    id: sslCheckBox
                    Layout.fillWidth: true
                    checked: settings.getSsl();
                }


                Text {
                    id: maxConnectionTrialsText
                    text: qsTr("Maximale Anzahl Verbindungsversuche")
                }

                SpinBox {
                    id: maxConnectionTrialsSpinBox
                    Layout.fillWidth: true
                    value: settings.getSettingsValueSlot("Config_MaxTrials");
                }

                Text {
                    id: zipCompressionText
                    text: qsTr("Übertragungsdaten komprimieren")
                    Layout.fillWidth: true
                }

                CheckBox {
                    id: zipCompressionCheckBox
                    Layout.fillWidth: true
                    checked: settings.getCompression();
                }

                Text {
                    id: multiThreadedText
                    text: qsTr("Multithreaded")
                    Layout.fillWidth: true
                }

                CheckBox {
                    id: multithreadedCheckBox
                    Layout.fillWidth: true
                    checked: settings.getMultiThreaded();
                    onClicked: {
                        if (multithreadedCheckBox.checked) {
                            maxThreadCountSpinBox.enabled = true
                        } else {
                            maxThreadCountSpinBox.enabled = false
                        }
                    }
                }

                Text {
                    id: maxThreadCountText
                    text: qsTr("Maximale Thread Anzahl")
                }

                SpinBox {
                    id: maxThreadCountSpinBox
                    Layout.fillWidth: true
                    value: settings.getSettingsValueSlot("Config_MaxThreadCount");
                }

            }
        }

        GroupBox {
            id: logingGroupbox
            anchors.left: parent.left
            anchors.right: parent.right
            title: qsTr("Logging")
            checkable: true
            checked: settings.getLoggingActive()

            ColumnLayout {
                id: logingLayout
                anchors.fill: parent

                GridLayout {

                    id: grid_layout2
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    anchors.right: parent.right
                    anchors.rightMargin: 3
                    anchors.top: parent.top
                    columns: 3
                    rows: 1

                    Text {
                        id: text5
                        text: qsTr("Pfad")
                    }

                    TextField {
                        id: filePathTextField
                        Layout.fillWidth: true
                        text: settings.getSettingsValueSlot("Logging_Path")
                    }

                    Button {
                        id: selectFileButton
                        text: qsTr("Auswählen...")
                        onClicked: {
                            fileDialog.open();
                        }
                    }
                }

                RowLayout {
                    id: logingCheckBoxes
                    anchors.top: grid_layout2.bottom
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    anchors.right: parent.right
                    anchors.rightMargin: 3

                    CheckBox{
                        id: infoCheckBox
                        text: qsTr("Informationen")
                        checked: settings.getLoggingInformation()
                    }

                    CheckBox{
                        id: warningCheckBoxCheckBox
                        text: qsTr("Warnung")
                        checked: settings.getLoggingWarning()
                    }

                    CheckBox{
                        id: errorCheckBoxCheckBox
                        text: qsTr("Fehler")
                        checked: settings.getLoggingError()
                    }

                    CheckBox{
                        id: fatalCheckBoxCheckBox
                        text: qsTr("Fataler Fehler")
                        checked: settings.getLoggingFatal()
                    }
                }
            }
        }

        GroupBox {
            id: serveruserGroupbox
            anchors.left: parent.left
            anchors.right: parent.right
            title: qsTr("Server Anwender")

            GridLayout {

                id: grid_layoutServerUser
                anchors.fill: parent
                anchors.margins: 3
                columns: 2
                rows: 2

                Text {
                    id: textUser
                    text: qsTr("Login")
                }

                TextField {
                    id: user
                    Layout.fillWidth: true
                    text: settings.getServerUser();
                }

                Text {
                    id: textPassword
                    text: qsTr("Passwort")
                    Layout.fillWidth: true
                }

                TextField {
                    id: password
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    text: settings.getServerUserPassword();
                }
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
                    close()
                }
            }

            Button {
                id: okButton
                text: qsTr("OK")
                onClicked: {
                    settings.setSettingsValueSlot("Logging_Path", filePathTextField.text);
                    settings.setSettingsValueSlot("Logging_Information", infoCheckBox.checked);
                    settings.setSettingsValueSlot("Logging_Warning", warningCheckBoxCheckBox.checked);
                    settings.setSettingsValueSlot("Logging_Error", errorCheckBoxCheckBox.checked);
                    settings.setSettingsValueSlot("Logging_Fatal", fatalCheckBoxCheckBox.checked);
                    settings.setSettingsValueSlot("Logging_Active", logingGroupbox.checked);
                    settings.setSettingsValueSlot("Config_MaxThreadCount", maxThreadCountSpinBox.value);
                    settings.setSettingsValueSlot("Config_MultiThread", multithreadedCheckBox.checked);
                    settings.setSettingsValueSlot("Config_Compression", zipCompressionCheckBox.checked);
                    settings.setSettingsValueSlot("Config_Port", portSpinBox.value);
                    settings.setSettingsValueSlot("Config_Ssl", sslCheckBox.checked);
                    settings.setSettingsValueSlot("Config_MaxTrials", maxConnectionTrialsSpinBox.value);
                    settings.setSettingsValueSlot("Server_User", user.text);
                    settings.setSettingsValueSlot("Server_Password", password.text);
                    close();
                }
            }
        }
    }
}

