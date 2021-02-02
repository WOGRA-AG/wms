import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: wmsAboutViewer
    anchors.fill: parent
    color: wmsStyle.GetBackgroundColor()

    GridLayout {
       id: content
       columns: 1
       anchors.fill: parent

       Text {
           id: header
           text: qsTr("Anwendungsinformationen")
           horizontalAlignment: Text.AlignHCenter
           Layout.fillWidth: true
           font.pointSize: 18
           font.bold: true
           color: wmsStyle.GetForegroundColor()
       }

       GroupBox {
           id: applicationInfo
           Layout.fillWidth: true
           title: qsTr("Applikation")

           GridLayout {
               id: grid_layout1
               anchors.fill: parent
               columns: 2

               Text {
                   id: nameText
                   text: qsTr("Name")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: nameTextField
                   placeholderText: qsTr("Applikationsname")
                   Layout.fillWidth: true
                   readOnly: true
               }

               Text {
                   id: vendorText
                   text: qsTr("Hersteller")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: vendorTextField
                   placeholderText: qsTr("Hersteller")
                   Layout.fillWidth: true
                   readOnly: true
               }
           }
       }

       GroupBox {
           id: supportInfo
           Layout.fillWidth: true
           title: qsTr("Unterstützung")

           GridLayout {
               id: grid_layout2
               anchors.fill: parent
               columns: 2

               Text {
                   id: supportText
                   text: qsTr("Support")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: supportTextField
                   placeholderText: qsTr("Support")
                   Layout.fillWidth: true
                   readOnly: true
               }

               Text {
                   id: hotlineText
                   text: qsTr("Hotline")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: hotlineTextField
                   placeholderText: qsTr("Hotline")
                   Layout.fillWidth: true
                   readOnly: true
               }

               Text {
                   id: webText
                   text: qsTr("Web")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: webTextField
                   placeholderText: qsTr("Web")
                   Layout.fillWidth: true
                   readOnly: true
               }
           }
       }

       GroupBox {
           id: versionInfo
           Layout.fillWidth: true
           title: qsTr("Versionsinformationen")

           GridLayout {
               id: grid_layout3
               anchors.fill: parent
               columns: 2

               Text {
                   id: applicationVersionText
                   text: qsTr("Applikationsversion")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: applicationVersionTextField
                   placeholderText: qsTr("Applikationsversion")
                   Layout.fillWidth: true
                   readOnly: true
               }

               Text {
                   id: runtimeVersionText
                   text: qsTr("Hotline")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: runtimeVersionTextField
                   placeholderText: qsTr("Runtimeversion")
                   Layout.fillWidth: true
                   readOnly: true
               }

               Text {
                   id: wmsVersionText
                   text: qsTr("WMS Version")
                   color: wmsStyle.GetForegroundColor()
               }

               TextField {
                   id: wmsVersionTextField
                   placeholderText: qsTr("WMS Version")
                   Layout.fillWidth: true
                   readOnly: true
               }
           }
       }
    }

    Component.onCompleted: {
        // todo fill data
    }
}
