import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import com.wogra.wmscore 1.0
import com.wogra.wmsqml 1.0


Rectangle {
    id: objectContainerRectangle
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()

    signal editObject()
    signal createObject(WmsObject newObject)
    property int windowWidth: 0
    property variant myColumns: [];

    WmsContainerEditorController {
        id: controller
    }

    GridLayout {
        id: content
        columns: 1
        anchors.fill: parent

        TableView {
            id: containerTable
            anchors.fill: parent
            alternatingRowColors: true
            sortIndicatorVisible: true

            style: WmsTableViewStyle { }

            onDoubleClicked: {
                editObject();
            }
        }


        Rectangle {
            id: buttonRect
            color: wmsStyle.getNavigationBarColor()
            implicitHeight: wmsMainWindowTablet.width < 500 ? wmsStyle.getNavigationBarSize() : 20 + wmsMainWindowTablet.width * wmsStyle.getTextScale()
            Layout.fillWidth: true
            anchors.bottom: parent.bottom;


            RowLayout {
                anchors.fill: parent

                WmsToolButton {
                    id: newButton
                    image: "../icons/new32.png"
                    onClicked: {
                        newClicked();
                    }
                }

                ToolButton {
                    id: editButton
                    iconSource: "../icons/edit32.png"
                    onClicked: {
                        editObject();
                    }
                }

                WmsToolButton {
                    id: deleteButton
                    image: "../icons/delete32.png"
                    onClicked: {
                        deleteClicked();
                    }
                }

                WmsToolButton {
                    id: printButton
                    image: "../icons/print32.png"
                    onClicked: {
                        printClicked();
                    }
                }

                WmsToolButton {
                    id: searchButton
                    image: "../icons/search32.png"
                    onClicked: {
                        searchClicked();
                    }
                }

                WmsToolButton {
                    id: journalButton
                    image: "../icons/printpreview32.png"
                    onClicked: {
                        journalClicked();
                    }
                }



                Item { Layout.fillWidth: true }
            }
        }
    }

    function setModule(module, mainWindow) {
        //console.log("SetModule called");
        hideButtons();
        setContainer(module.getContainerModule());
    }

    function setContainer(container) {
        controller.setContainer(container);
        containerTable.model = controller.getModel();

        var columns = controller.getColumnCount();
        var pos = 0;

        for( pos = 0; pos < columns; pos++) {
            var columnObject = "column_" + pos;
            var columnCode = controller.getColumnCode(pos);
            var currentColumn = Qt.createQmlObject(columnCode,containerTable,columnObject)
            myColumns.push(currentColumn);
            containerTable.addColumn(currentColumn);
        }

        if (!controller.hasPrinting()) {
            printButton.visible = false;
        }
    }

    function hideButtons() {
        buttonRect.visible = false;
        //containerTable.anchors.bottom = objectContainerRectangle.bottom
    }

    function hasPrinting() {
        return controller.hasPrinting();
    }

    function journalClicked() {
        //console.log("journalClicked");
    }

    function printClicked() {
        //console.log("printClicked");
    }

    function searchClicked() {
        //console.log();
    }

    function deleteClicked() {

        var obj = getSelectedObject();

        if (obj !== null) {
            obj.setDeleted();
            obj.commit();
            restoreLastView();
        }
    }

    function newClicked() {

        var container = containerTable.model.getContainer();

        if (container !== null) {
            var newObject = container.createObject();
            createObject(newObject);
        }
    }

    function getSelectedObject() {
        return containerTable.model.getObject(containerTable.currentRow);
    }



    onWidthChanged: {
        windowWidth = wmsApp.getCentralWindow().width;
    }

    onWindowWidthChanged: {
        if(myColumns.length != 0){
            var index;
            var tableColumnWidth = windowWidth / myColumns.length - 2;

            for( index = 0; index < myColumns.length; index++) {
                myColumns[index].width = tableColumnWidth;
            }
        }
    }
}
