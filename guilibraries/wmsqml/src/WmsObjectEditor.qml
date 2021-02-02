import QtQuick 2.2
import QtQml.Models 2.1
import QtQuick.Layouts 1.1
import com.wogra.wmsqml 1.0

Rectangle {
    id: objectEditor
    color: wmsStyle.getBackgroundColor()
    anchors.fill: parent

    WmsObjectEditorController {
        id: controller
    }

    Component {
        id: highlightBar
        Rectangle {
            //width: parent.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 15
            height: 30
            color: wmsStyle.getSelectionColor()
            y: groupView.currentItem.y;

            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }

    Loader {
        id: selectionLoader;
        anchors.fill: parent
        //visible: false
        onLoaded: {
            mainLayout.visible = false;
            visible = true;
            console.log("Selection loaded: " + contentLoader.source);
            // ToDo
        }
    }


    GridLayout {
        id: mainLayout
        anchors.fill: parent;
        columns: 2

        Rectangle {
            id: editorRect
            color: wmsStyle.getBackgroundColor()
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: catRect.right
            anchors.right: parent.right

            RowLayout {
                anchors.fill: parent

                ColumnLayout {
                    id: objectEditorContentLayout
                    anchors.fill: parent

                    ListModel {
                        id: data

                        //to be filled dynamically

                    }

                    ListView {
                        id: pageView
                        anchors.fill: parent
                        model: data
                        delegate: WmsObjectEditorDelegate { }
                        orientation: ListView.Horizontal
                        snapMode: ListView.SnapOneItem
                        cacheBuffer: wmsApp.getCentralWindow().width
                        boundsBehavior: Flickable.StopAtBounds;
                        preferredHighlightBegin: 0;  preferredHighlightEnd: 0
                        highlightRangeMode: ListView.StrictlyEnforceRange
                        highlightFollowsCurrentItem: true
                        highlightMoveDuration: 1
                        focus: true
                        flickDeceleration: 2000
                        Keys.onLeftPressed: {
                            if (currentIndex >= 0 ){
                                currentIndex = currentIndex-1;
                            }
                        }
                        Keys.onRightPressed: {
                            if (currentIndex < pageView.model.count-1){
                                currentIndex = currentIndex+1;
                            }
                        }
                    }

                    Rectangle {
                        id: pageNavigation
                        color: wmsStyle.getBackgroundColor()
                        width: objectEditor.width;
                        implicitHeight: objectEditor.width < 500 ? wmsStyle.getNavigationBarSize() : 20 + objectEditor.width * wmsStyle.getTextScale()
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom;

                        Row {
                            anchors.centerIn: parent
                            spacing: 20

                            Repeater {
                                id: pageNavigator

                                Rectangle {
                                    width: 15; height: 15
                                    radius: 10
                                    color: pageView.currentIndex === index ? "blue" : "white";

                                    MouseArea {
                                        width: 20; height: 20
                                        anchors.centerIn: parent

                                        onClicked: {
                                            pageView.currentIndex = index;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: catRect
            color: wmsStyle.getBackgroundColor()
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            width: objectEditor.width / 5

            Rectangle {
                id: groupsRect
                color: wmsStyle.getBackgroundColor()
                anchors.fill: parent
                anchors.topMargin: 8
                anchors.bottomMargin: 8
                border.color: "white"
                border.width: 1
                radius: 10

                GridLayout {
                    id: groups
                    anchors.fill: parent
                    columns: 1
                    // rowSpacing: 5

                    Text {
                        id: header
                        text: qsTr("Kategorien")
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        font.pointSize: wmsApp.getCentralWindow().width * wmsStyle.getTableviewScale()
                        font.bold: true
                        color:  wmsStyle.getForegroundColor()
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.bottomMargin: 10
                    }

                    ListView {
                        id: groupView
                        anchors.left: parent.left
                        anchors.leftMargin: 3
                        anchors.right: parent.right
                        anchors.rightMargin: 3
                        anchors.top: header.bottom
                        anchors.bottom: parent.bottom
                        highlight: highlightBar
                        highlightFollowsCurrentItem: true
                        boundsBehavior: Flickable.StopAtBounds;
                        delegate: WmsObjectEditorGroupDelegate {
                            text: modelData

                            onClicked: {
                                groupSelected();
                            }
                        }
                    }
                }
            }
        }
    }

    function getGroupName() {
        if (controller.getGroupCount() === 0) {
            return "";
        } else {
            return groupView.model[groupView.currentIndex];
        }
    }

    function setObject(wmsObject, newObject) {

        if (wmsObject !== null) {
            console.log("The object will be set.");
            controller.setObject(wmsObject, newObject);
            data.append({ "page": 0 });
            setGroupViewModel();
        }
    }

    function groupSelected() {
        var curIndex = groupView.currentIndex;
        console.log("Group selected. Selected Index: " + curIndex);
        changeGroup();
    }

    function changeGroup(){
        data.clear();
        data.append({ "page": 0 });
        var pageCount = controller.countPagesOfGroup(getGroupName());
        pageNavigator.model = pageCount;

        for(var i = 1; i < pageCount; i++) {
            pageView.model.append({ "page" : i });
        }
    }

    function setGroupViewModel() {
        if (controller.getGroupCount() === 0) {
            catRect.visible = false;
            editorRect.anchors.fill = editorRect.parent;
            var pageCount = controller.countPagesOfGroup(getGroupName());
            pageNavigator.model = pageCount;

            for(var i = 1; i < pageCount; i++) {
                pageView.model.append({ "page" : i });
            }

        } else {
            groupView.model = controller.getGroups();
            groupView.currentIndex = 0;
            var pageCount = controller.countPagesOfGroup(getGroupName());
            pageNavigator.model = pageCount;

            for(var i = 1; i < pageCount; i++) {
                pageView.model.append({ "page" : i });
            }
        }
    }

    function setModule(currentModule) {
        // TODO
    }

    function okClicked() {
        controller.okClicked();
    }

    function cancelClicked() {
        controller.cancelClicked();
    }
}
