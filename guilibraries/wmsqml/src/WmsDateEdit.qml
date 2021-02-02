import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQml 2.2

Item {
    id: wmsDateEdit
    anchors.fill: parent
    property date date;
    signal dateChangedSignal()

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        scale: 1
        spacing: 3
        anchors.margins: 6

        Item { Layout.fillWidth: true }

        SpinBox {
            id: days
            minimumValue: 1
            maximumValue: 31
            decimals: 0
            onValueChanged: valueChanged()
        }

        ComboBox {
            id: month
            model: [ qsTr("Januar"),
                     qsTr("Februar"),
                     qsTr("März"),
                     qsTr("April"),
                     qsTr("Mai"),
                     qsTr("Juni"),
                     qsTr("Juli"),
                     qsTr("August"),
                     qsTr("September"),
                     qsTr("Oktober"),
                     qsTr("November"),
                     qsTr("Dezember") ]
            currentIndex: 0
            onCurrentIndexChanged: valueChanged()
        }

        SpinBox {
            id: year
            minimumValue: 1800
            maximumValue: 3000
            decimals: 0
            onValueChanged: valueChanged()
        }


    }

    function valueChanged() {
        updateValue();
        dateChangedSignal();
    }

    function updateValue() {
        date.setDate(days.value);
        date.setMonth(month.currentIndex + 1);
        date.setYear(year.value);
    }

    function setDate(newDate) {
        date = newDate;
    }

    function getDate() {
        valueChanged();
        return date;
    }

    function updateDisplay() {
        days.value = date.getDate();
        month.currentIndex = date.getMonth() - 1;
        year.value = date.getYear();
    }
}
