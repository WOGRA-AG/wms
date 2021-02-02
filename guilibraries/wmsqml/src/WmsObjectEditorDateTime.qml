import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

WmsObjectEditorValue {
    id: wmsObjectEditorDateTime
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()

    property alias editDateValue:        editDateValueTextEdit.text
    property alias editTimeValue:        editTimeValueTextEdit.text
    property alias captionValue:         caption.text

    GridLayout {
       id: content
       columns: 3
       anchors.fill: parent

       Text {
           id: caption

           verticalAlignment: Text.AlignVCenter
           anchors.left: parent.left
           anchors.top: parent.top
           anchors.bottom: parent.bottom
           anchors.right: editDateValueTextEdit.left
           anchors.leftMargin: 20
           width: 250
           text: qsTr("Name")
           color: wmsStyle.getForegroundColor()
           font.bold: true;
       }

       TextField {
           id: editDateValueTextEdit
           anchors.left: caption.right;
           anchors.right: editTimeValueTextEdit.left
           anchors.rightMargin: 3
           placeholderText: qsTr("Datum")

           onTextChanged: {
               updateDateTimeValue();
           }
       }

       TextField {
           id: editTimeValueTextEdit
           anchors.right: parent.right
           anchors.rightMargin: getRightMargin()

           placeholderText: qsTr("Uhrzeit")

           onTextChanged: {
               updateDateTimeValue();
           }
       }
    }

    function fillData(valueElement) {
        setValue(valueElement);
        //editValue = getValue();
        var dateValue = getValue();
        console.log("Date from WMS: " + dateValue);

        if (isDate()) {
            editDateValue = getDate().toLocaleDateString(Locale.ShortFormat);
            editTimeValueTextEdit.visible = false;
            editDateValueTextEdit.anchors.right = editDateValueTextEdit.parent.right;
        } else if (isDateTime()) {
            dateValue = getDateTime();
            editDateValue = dateValue.toLocaleDateString(Locale.ShortFormat);
            editTimeValue = dateValue.toLocaleTimeString(Locale.ShortFormat);
        } else if (isTime()) {
            editTimeValue = getTime().toLocaleTimeString(Locale.ShortFormat);
            editDateValueTextEdit.visible = false;
            editTimeValueTextEdit.anchors.left = caption.right;
        }

        captionValue = getCaption();
    }

    function updateDateTimeValue() {
        if (getValue().toLocaleTimeString(Qt.locale()) !== editTimeValueTextEdit.text ||
            getValue().toLocaleDateString(Qt.locale()) !== editDateValueTextEdit.text) {
            var valueDate = new Date();
            var valueTime = new Date();

            if (isDate()) {
                valueDate = Date.fromLocaleDateString(Qt.locale(), editDateValue, Locale.ShortFormat);
                setDate(valueDate);
            } else if (isDateTime()) {
                var valueDateTime = new Date();
                valueDate = Date.fromLocaleDateString(Qt.locale(), editDateValue, Locale.ShortFormat);
                console.log("date value: " + valueDate);
                valueTime = Date.fromLocaleTimeString(Qt.locale(), editTimeValue, Locale.ShortFormat);
                console.log("time value: " + valueTime);
                valueDateTime.setFullYear(valueDate.getFullYear());
                valueDateTime.setMonth(valueDate.getMonth());
                valueDateTime.setDate(valueDate.getDate());
                valueDateTime.setHours(valueTime.getHours());
                valueDateTime.setMinutes(valueTime.getMinutes());
                valueDateTime.setSeconds(valueTime.getSeconds());
                valueDateTime.setMilliseconds(valueTime.getMilliseconds());
                console.log("datetime value: " + valueDateTime);
                setDateTime(valueDateTime);
            } else if (isTime()) {
                valueTime = Date.fromLocaleTimeString(Qt.locale(), editTimeValue, Locale.ShortFormat);
                setTime(valueTime);
            }
        }
    }

    function updateData() {
        // does nothing
    }
}
