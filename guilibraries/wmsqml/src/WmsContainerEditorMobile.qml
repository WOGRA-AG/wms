import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.1
import com.wogra.wmscore 1.0
import com.wogra.wmsqml 1.0


Rectangle {
    id: wmsContainerEditorMobile
    anchors.fill: parent
    color: wmsStyle.getBackgroundColor()

    WmsContainerEditorController {
         id: controller
     }

    GridLayout {
        id: mainLayout
        anchors.fill: parent
        columns: 1

        ScrollView {
            anchors.fill: parent
            flickableItem.interactive: true

            ListView {
                id: container
                anchors.fill: parent
                delegate: WmsContainerEditorDelegate {

                    onEditClicked: {
                        console.log("Edit call! Index: " + index);
                        wmsContainerEditorMobile.editClicked(index);
                    }

                    onDeleteClicked: {
                        console.log("Delete call! Index: " + index);
                        wmsContainerEditorMobile.deleteClicked(index);
                    }
                }
            }

            style: ScrollViewStyle {
                transientScrollBars: true
                handle: Item {
                    implicitWidth: 14
                    implicitHeight: 26
                    Rectangle {
                        color: wmsStyle.getScrollbarColor()
                        anchors.fill: parent
                        anchors.topMargin: 6
                        anchors.leftMargin: 4
                        anchors.rightMargin: 4
                        anchors.bottomMargin: 6
                    }
                }
                scrollBarBackground: Item {
                    implicitWidth: 14
                    implicitHeight: 26
                }
            }
        }
    }

    function setModule(module, mainWindow) {
        console.log("SetModule called");
        controller.setContainer(module.getObjectListModule());
        container.model = controller.getModel();

        if (!controller.hasPrinting()) {
            printButton.visible = false;
        }
    }

    function hasPrinting() {
        return controller.hasPrinting();
    }

    function journalClicked() {
        console.log("journalClicked");
    }

    function printClicked() {
        console.log("printClicked");
    }

    function searchClicked() {
        console.log("searchClicked");
    }

    function deleteClicked(index) {

        var obj = container.model.getObject(index);

        if (obj !== null) {
            obj.setDeleted();
            obj.commit();
        }
    }

    function editClicked(index) {
        console.log("editClicked");
    }

    function newClicked() {
        console.log("newClicked");
    }

}
