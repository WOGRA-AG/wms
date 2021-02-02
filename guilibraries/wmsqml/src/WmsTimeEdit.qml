import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQml 2.2

Item {
    id: wmsTimeEdit
    anchors.fill: parent
    property date time;
    signal timeChangedSignal()

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        scale: 1
        spacing: 3
        anchors.margins: 6

        SpinBox {
            id: hours
            minimumValue: 0
            maximumValue: 24
            decimals: 0
            onValueChanged: valueChanged()
        }

        SpinBox {
            id: minutes
            minimumValue: 0
            maximumValue: 59
            decimals: 0
            onValueChanged: valueChanged()
        }

        SpinBox {
            id: seconds
            minimumValue: 0
            maximumValue: 59
            decimals: 0
            onValueChanged: valueChanged()
        }
    }

    function valueChanged() {
        updateValue();
        timeChangedSignal();
    }

    function updateValue() {
        time.setHours(hours.value);
        time.setMinutes(minutes.value);
        time.setSeconds(seconds.value);
    }

    function setTime(newTime) {
        time = newTime;
    }

    function getTime() {
        valueChanged();
        return time;
    }

    function updateDisplay() {
        hours.value = time.getHours();
        minutes.value = time.getMinutes();
        seconds.value = time.getSeconds();
    }
}
