import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2


SpinBox {
    id: spinBox

    maximumValue: 66000
    minimumValue: 0
    font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getSubtitleScale()
    style: WmsSpinBoxStyle { }
}

