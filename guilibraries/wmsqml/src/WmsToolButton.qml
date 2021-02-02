import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1


ToolButton {
    property int parentWindow
    property alias image: buttonImage.source

    id: toolButton
    implicitWidth: parentWindow < 500 ? 32 : 12 + parentWindow * wmsStyle.getSubtitleScale()
    implicitHeight: parentWindow < 500 ? 32 : 12 + parentWindow * wmsStyle.getSubtitleScale()

    Image {
        id: buttonImage
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

}

