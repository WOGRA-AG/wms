import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: wmsLoginRect
    color: wmsStyle.getBackgroundColor()

    Component.onCompleted: {

        if (wmsApp.IsMobile) {
            grid_layout1.columns = 1;
        }
    }

    property alias login:     loginTextField.text
    property alias password:  passwordTextField.text
    property alias saveLogin: checkboxSaveLogin.checked
    property int columnWidth: wmsStyle.getContentWidth()/9


    GridLayout {
        id: content
        columns: 1
        height: wmsStyle.getContentHeight()
        width: wmsStyle.getContentWidth()
        anchors.fill: parent

        Text {
            id: header
            text: qsTr("Anmeldung")
            anchors.top: content.top
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
            font.pointSize: 1 + content.width * wmsStyle.getTextScale()
            font.bold: true
            color: wmsStyle.getForegroundColor()
        }

        GroupBox {
            id: logingroupbox
            anchors { top: header.bottom; left: parent.left; right: parent.right
                topMargin: Math.round(content.width * 1.5625) / 100
                leftMargin: Math.round(content.width * 0.78125) / 100
                rightMargin: Math.round(content.width * 0.78125) / 100
            }


            GridLayout {
                id: grid_layout1
                anchors.fill: parent
                anchors.margins: Math.round(content.width * 0.78125) / 100
                columns: 2

                Text {
                    id: text1
                    text: qsTr("Benutzername")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: 1 + content.width * wmsStyle.getTextScale()
                }

                TextField {
                    id: loginTextField
                    placeholderText: qsTr("Benutzername")
                    Layout.fillWidth: true
                    text: wmsLogin.getLogin()
                    font.pointSize: 1 + content.width * wmsStyle.getTextScale()
                }

                Text {
                    id: labelPassword
                    text: qsTr("Passwort")
                    color: wmsStyle.getForegroundColor()
                    font.pointSize: 1 + content.width * wmsStyle.getTextScale()
                }

                TextField {
                    id: passwordTextField
                    placeholderText: qsTr("Passwort")
                    Layout.fillWidth: true
                    echoMode: TextInput.Password
                    text: wmsLogin.getPassword()
                    font.pointSize: 1 + content.width * wmsStyle.getTextScale()
                }

                CheckBox {
                    id: checkboxSaveLogin
                    Layout.rowSpan: 2
                    checked: wmsLogin.getStoreUserData()
                    style: CheckBoxStyle {
                        spacing: 10
                        indicator: Rectangle {
                            implicitWidth: 1 + content.width * wmsStyle.getTextScale()
                            implicitHeight: 1 + content.width * wmsStyle.getTextScale()
                            radius: 3
                            border.color: control.activeFocus ? "darkblue" : "gray"
                            border.width: 1
                            Image {
                                source: wmsStyle.getCheckboxMarker()
                                visible: control.checked
                                anchors.fill: parent
                            }
                        }
                        label: Text {
                            color: wmsStyle.getForegroundColor()
                            text: qsTr("Benutzername speichern")
                            font.pointSize: 1 + content.width * wmsStyle.getSubtitleScale()
                        }
                    }
                }
            }
        }

        Text {
            id: labelLoginError
            color: wmsStyle.getErrorTextColor()
            visible: false
            font.pointSize: 1 + content.width * wmsStyle.getSubtitleScale()
        }

        Item { Layout.fillHeight: true }

        Rectangle {
            id: buttonRect
            anchors.bottom: content.bottom
            color: wmsStyle.getNavigationBarColor()
            implicitHeight: content.width < 500 ? wmsStyle.getNavigationBarSize() : 20 + content.width * wmsStyle.getTextScale()
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Math.round(content.width * 0.78125) / 100
                anchors.rightMargin: Math.round(content.width * 0.78125) / 100

                WmsToolButton {
                    id: clientSettingsButton
                    text: qsTr("Konfiguration")
                    image: wmsStyle.getConfigurationButton()
                    parentWindow: content.width
                    onClicked: { openPageFile("WmsDataAccessConfiguration.qml") }
                }

                Item { Layout.fillWidth: true }

                WmsToolButton {
                    id: cancelButton
                    text: "Abbrechen"
                    image: wmsStyle.getCancelButton()
                    parentWindow: content.width
                    onClicked: {
                        hide();
                        wmsLogin.cancel();
                    }
                }

                WmsToolButton {
                    id: okButton
                    text: qsTr("OK")
                    image: wmsStyle.getOkButton()
                    parentWindow: content.width
                    onClicked: {

                        var success = wmsLogin.login();
                        if (success === true) {
                            wmsApp.loginSuccessfull();

                            if (wmsApp.needsDatabaseSelection() === true) {
                                openPageFile("WmsSelection.qml");
                            } else if (wmsApp.needsApplicationSelection() === true) {
                                openPageFile("WmsSelection.qml");
                            } else {
                                loadMainWindow();
                            }
                        } else {
                            labelLoginError.visible = true;
                            labelLoginError.text = wmsLogin.getLoginError();
                            labelLoginError.color = wmsStyle.getErrorTextColor();
                            passwordTextField.selectAll();
                            passwordTextField.focus = true;
                        }
                    }
                }
            }
        }
    }
}
