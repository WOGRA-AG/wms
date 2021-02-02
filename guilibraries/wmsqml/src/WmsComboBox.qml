import QtQuick 2.2
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.1


ComboBox {
    id: comboBox
    style: WmsComboBoxStyle {
        label: Text {
            font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
            color: "#808080"
            text: control.currentText
            wrapMode: "WordWrap"
        }
    }
}
