import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import com.wogra.wmscore 1.0

Rectangle {
    id: wmsObjectEditorValue
    anchors.left: parent.left
    anchors.right: parent.right
    color: wmsStyle.getBackgroundColor()
    height: wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale() + 30
    border.color: "#333"
    border.width: 1
    Layout.fillWidth: true

    WmsValue {
        id: valueObj
    }


    function setValue(newValue) {

        if (newValue !== null) {
            valueObj.setValueObject(newValue);
            // to do connect events

        }
    }

    function getValue() {
        return valueObj.getValue();
    }

    function getValueBool() {
        return valueObj.getValueAsBool();
    }

    function setValueBool(valueBool) {
        valueObj.setValueBool(valueBool);
    }

    function getCaption() {
        return valueObj.getCaption();
    }

    function updateValue(newValue) {
        valueObj.setValue(newValue);
    }

    function isDate() {
        return valueObj.isDate();
    }

    function isDateTime() {
        return valueObj.isDateTime();
    }

    function isTime() {
        return valueObj.isTime();
    }

    function getTime() {
        return valueObj.getValueTime();
    }

    function getDateTime() {
        return valueObj.getValueDateTime();
    }

    function getDate() {
        return valueObj.getValueDate();
    }

    function setTime(timeValue) {
        valueObj.setValueTime(timeValue);
    }

    function setDateTime(dateTimeValue) {
        console.log("Set datetime value: " + dateTimeValue);
        valueObj.setValueDateTime(dateTimeValue);
    }

    function setDate(dateValue) {
        valueObj.setValueDate(dateValue);
    }

    function getBinDocFilename() {
        return valueObj.getBinDocFileName();
    }

    function openBinDoc() {
        valueObj.openBinDoc();
    }

    function isReadOnly() {
        return valueObj.isReadOnly();
    }

    function initListModel() {
        var modelString = valueObj.getSelectionModel();
        var initModel = Qt.createQmlObject(modelString, wmsObjectEditorValue, "genericModel");
        return initModel;
    }

    function setSelectionValue(selectionValue) {
        valueObj.setSelectionValue(selectionValue);
    }

    function getSelectionValueIndex() {
        return valueObj.getSelectionValueIndex();
    }
    function addListValue(listValue) {
        return valueObj.addListValue(listValue);
    }

    function removeListValue(listValue) {
        return valueObj.removeListValue(listValue);
    }

    function isListOfObjects() {
        return valueObj.isListOfObjects();
    }

    function getRightMargin() {
        return 3;
    }
    function getLeftMargin() {
        return 3;
    }
}
