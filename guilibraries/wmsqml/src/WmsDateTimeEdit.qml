import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQml 2.2


Item {
    id: wmsDateTimeEdit
    anchors.fill: parent
    property date datetime;
    signal dateTimeChangedSignal()

    RowLayout {
        id: mainLayout
        anchors.fill: parent
        scale: 1
        spacing: 3
        anchors.margins: 6

        WmsDateEdit {
            id: date
            onDateChanged: valueChanged();
        }

        WmsTimeEdit {
            id: time
            anchors.left: date
            onTimeChanged: valueChanged();
        }
    }

    function valueChanged() {
        updateValue();
        dateTimeChangedSignal();
    }

    function updateValue() {
        var dateValue = date.getDate();
        datetime.setDate(dateValue.getDate());
        datetime.setMonth(dateValue.getMonth());
        datetime.setYear(dateValue.getYear());
        var timeValue = time.getTime();
        datetime.setHours(timeValue.getHours());
        datetime.setMinutes(timeValue.getMinutes());
        datetime.setSeconds(timeValue.getSeconds());
    }

    function setDate(newDate) {
        datetime = newDate;
        updateDisplay();
    }

    function getDate() {
        updateValue();
        return datetime;
    }

    function updateDisplay() {
        date.setDate(datetime);
        time.setTime(datetime);
    }
}
