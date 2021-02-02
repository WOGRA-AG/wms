
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1
import com.wogra.wmsqml 1.0


Rectangle {
    id: wsmTextEditor
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()
    property alias text:  textArea.text
    property int textEditorWidth: 0
    property int toolbarHeight: 0

//    Action {
//        id: cutAction
//        text: "Cut"
//        shortcut: "ctrl+x"
//        iconName: "edit-cut"
//        onTriggered: textArea.cut()
//    }

//    Action {
//        id: copyAction
//        text: "Copy"
//        shortcut: "Ctrl+C"
//        iconName: "edit-copy"
//        onTriggered: textArea.copy()
//    }

//    Action {
//        id: pasteAction
//        text: "Paste"
//        shortcut: "ctrl+v"
//        iconName: "edit-paste"
//        onTriggered: textArea.paste()
//    }

//    Action {
//        id: alignLeftAction
//        text: "&Left"
//        iconName: "format-justify-left"
//        shortcut: "ctrl+l"
//        onTriggered: document.alignment = Qt.AlignLeft
//        checkable: true
//        checked: document.alignment == Qt.AlignLeft
//    }

//    Action {
//        id: alignCenterAction
//        text: "C&enter"
//        iconName: "format-justify-center"
//        onTriggered: document.alignment = Qt.AlignHCenter
//        checkable: true
//        checked: document.alignment == Qt.AlignHCenter
//    }

//    Action {
//        id: alignRightAction
//        text: "&Right"
//        iconName: "format-justify-right"
//        onTriggered: document.alignment = Qt.AlignRight
//        checkable: true
//        checked: document.alignment == Qt.AlignRight
//    }

//    Action {
//        id: alignJustifyAction
//        text: "&Justify"
//        iconName: "format-justify-fill"
//        onTriggered: document.alignment = Qt.AlignJustify
//        checkable: true
//        checked: document.alignment == Qt.AlignJustify
//    }

//    Action {
//        id: boldAction
//        text: "&Bold"
//        iconSource: "../icons/bold.png"
//        iconName: "format-text-bold"
//        onTriggered: document.bold = !document.bold
//        checkable: true
//        checked: document.bold
//    }

//    Action {
//        id: italicAction
//        text: "&Italic"
//        iconName: "format-text-italic"
//        onTriggered: document.italic = !document.italic
//        checkable: true
//        checked: document.italic
//    }
//    Action {
//        id: underlineAction
//        text: "&Underline"
//        iconName: "format-text-underline"
//        onTriggered: document.underline = !document.underline
//        checkable: true
//        checked: document.underline
//    }

    ColorDialog {
        id: colorDialog
        color: "black"
        onAccepted: document.textColor = color
    }

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        columns: 1


//        Rectangle {
//            id: toolbarRect
//            color: wmsStyle.getNavigationBarColor()
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.right: parent.right
//            anchors.bottom: textArea.top

//            GridLayout {
//                id: toolbars
//                columns: 1
//                rows: 2
//                anchors.fill: parent

//                ToolBar {
//                    id: mainToolBar
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    anchors.top: parent.top

//                    RowLayout {
//                        anchors.fill: parent
//                        spacing: 0

//                        WmsToolButton {
//                            image: "../icons/copy32.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: copyAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/cut32.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: cutAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/insert32.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: pasteAction
//                        }

//                        ToolBarSeparator {}

//                        WmsToolButton {
//                            image: "../icons/bold.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: boldAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/italic.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: italicAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/underlined.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: underlineAction
//                        }

//                        ToolBarSeparator {}

//                        WmsToolButton {
//                            image: "../icons/align-left.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: alignLeftAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/align-center.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: alignCenterAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/align-right.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: alignRightAction
//                        }
//                        WmsToolButton {
//                            image: "../icons/align-justify.png"
//                            parentWindow: wmsApp.getCentralWindow().width
//                            action: alignJustifyAction
//                        }

//                        ToolBarSeparator {}

//                        WmsToolButton {
//                            id: colorButton
//                            parentWindow: wmsApp.getCentralWindow().width
//                            property var color : document.textColor
//                            Rectangle {
//                                id: colorRect
//                                anchors.fill: parent
//                                anchors.margins: 8
//                                color: Qt.darker(document.textColor, colorButton.pressed ? 1.4 : 1)
//                                border.width: 1
//                                border.color: Qt.darker(colorRect.color, 2)
//                            }
//                            onClicked: {
//                                colorDialog.color = document.textColor
//                                colorDialog.open()
//                            }
//                        }
//                        Item { Layout.fillWidth: true }
//                    }
//                }

//                ToolBar {
//                    id: secondaryToolBar
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    anchors.top: mainToolBar.bottom

//                    RowLayout {
//                        anchors.fill: parent
//                        spacing: 0

//                        WmsComboBox {
//                            id: fontFamilyComboBox
//                            Layout.fillWidth: true
//                            Layout.maximumWidth: wmsApp.getCentralWindow().width / 2
//                            model: Qt.fontFamilies()
//                            property bool special : false
//                            onCurrentTextChanged: {
//                                if (special == false || currentIndex != 0)
//                                    document.fontFamily = currentText
//                            }
//                        }
//                        SpinBox {
//                            id: fontSizeSpinBox
//                            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
//                            value: 0
//                            onValueChanged: document.fontSize = value
//                        }
//                        Item { Layout.fillWidth: true }
//                    }
//                }
//            }
//        }

        TextArea {
            Accessible.name: "document"
            id: textArea
            frameVisible: false
            anchors.fill: parent
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale()
            textFormat: Qt.RichText
            Component.onCompleted: {
                //textArea.anchors.topMargin = mainToolBar.height + secondaryToolBar.height;
                forceActiveFocus()
            }
        }
    }


    WmsDocumentHandler {
        id: document
        target: textArea
        cursorPosition: textArea.cursorPosition
        selectionStart: textArea.selectionStart
        selectionEnd: textArea.selectionEnd
        Component.onCompleted: document.fileUrl = ""
//        onFontSizeChanged: fontSizeSpinBox.value = document.fontSize
//        onFontFamilyChanged: {
//            var index = Qt.fontFamilies().indexOf(document.fontFamily)
//            if (index == -1) {
//                fontFamilyComboBox.currentIndex = 0
//                fontFamilyComboBox.special = true
//            } else {
//                fontFamilyComboBox.currentIndex = index
//                fontFamilyComboBox.special = false
//            }
//        }
    }
//    onWidthChanged: {
//        textEditorWidth = wmsApp.getCentralWindow().width;
//    }

//    onTextEditorWidthChanged: {
//        textArea.anchors.topMargin = toolbarHeight;
//        toolbarHeight = mainToolBar.height + secondaryToolBar.height;
//    }
}
