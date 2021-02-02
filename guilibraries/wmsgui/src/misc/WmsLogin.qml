import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0


Window {
    id: wmsLogin

    property alias login:     loginTextField.text
    property alias password:  passwordTextField.text
    property alias saveLogin: checkboxSaveLogin.checked

    Rectangle {
        id: wmsLoginRectangle
        color: "#ffffff"
        height: 200
        width: 360

        ColumnLayout {
            id: mainlayout
            anchors.fill: parent
            scale: 1
            spacing: 3
            anchors.margins: 6

            Text {
                id: header
                text: qsTr("Anmeldung")
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                font.pointSize: 18
                font.bold: true
                color: "blue"
            }

            GroupBox {
                id: logingroupbox
                anchors.left: parent.left
                anchors.leftMargin: 3
                anchors.right: parent.right
                anchors.rightMargin: 3
                title: qsTr("Login")

                GridLayout {

                    id: grid_layout1
                    anchors.fill: parent
                    columns: 2
                    rows: 2


                    Text {
                        id: text1
                        text: qsTr("Benutzername")
                    }

                    TextField {
                        id: loginTextField
                        placeholderText: qsTr("Benutzername")
                        Layout.fillWidth: true
                        text: wmsLogin.GetLogin()
                    }

                    Text {
                        id: labelPassword
                        text: qsTr("Passwort")
                    }

                    TextField {
                        id: passwordTextField
                        placeholderText: qsTr("Passwort")
                        Layout.fillWidth: true
                        echoMode: TextInput.Password
                        text: wmsLogin.GetPassword()
                    }

                    CheckBox {
                        id: checkboxSaveLogin
                        x: 0
                        y: 50
                        width: 210
                        height: 17
                        text: qsTr("Benutzername speichern")
                        Layout.rowSpan: 2
                        checked: wmsLogin.GetStoreUserData()
                    }
                }
            }

            Text {
                id: labelLoginError
                color: "red"
                visible: false
            }

            Item { Layout.fillHeight: true }


            RowLayout {
                anchors.right: parent.right
                anchors.rightMargin: 3
                anchors.left: parent.left
                anchors.leftMargin: 3

                Button {
                    id: clientSettingsButton
                    text: qsTr("Clienteinstellungen")
                    onClicked: wmsLogin.ClientSettingsClickedSlot()
                }

                Item { Layout.fillWidth: true }

                Button {
                    id: cancelButton
                    text: qsTr("Abbrechen")
                    onClicked: {

                        hide();
                        wmsLogin.cancel();
                    }
                }

                Button {
                    id: okButton
                    text: qsTr("OK")
                    onClicked: {

                        var success = wmsLogin.Login();
                        if (success === true) {
                            hide();
                            wmsLogin.loginSuccessfull();
                        } else {
                            labelLoginError.visible = true;
                            labelLoginError.text = wmsLogin.GetLoginError();
                            labelLoginError.color = "red";
                            passwordTextField.selectAll();
                            passwordTextField.focus = true;
                        }
                    }
                }
            }
        }
    }
}
