import QtQuick 2.3
import QtQuick.Layouts 1.1

Item {
    id: wmsObjectEditorDelegate
    height: wmsObjectEditorDelegate.ListView.view.height
    width: wmsObjectEditorDelegate.ListView.view.width
    signal clicked;

    Component {
        id: contentComponent

        Rectangle {
            id: contentView
            anchors.fill: parent
            color: wmsStyle.getBackgroundColor()

            //content shown here
            GridLayout {
                id: contentLayout
                anchors.fill: parent
                columns: 1
                width: catRect.visible ? parent.width - catRect.width : parent.width
                //rowSpacing: 5

                Component.onCompleted: {
                    clearChildren(contentLayout);
                    fillGroups();

                    function fillGroups() {
                        if (controller.getGroupCount() === 0) {
                            createPages("");
                        } else {
                            console.log("Fill groups to grouplistview")
                            createGroup();
                        }
                    }

                    function getGroupName() {
                        if (controller.getGroupCount() === 0) {
                            return "";
                        } else {
                            return groupView.model[groupView.currentIndex];
                        }
                    }

                    function createGroup() {
                        var groupName = getGroupName();
                        console.log("Groupname: " + groupName);

                        if (!controller.needsMultiPageView(groupName)) {
                            hidePageNavigation();
                            createGroupComponents(groupName);
                        } else {
                            showPageNavigation();
                            createPages(groupName);
                        }
                    }

                    function clearChildren(uiObject) {
                        for (var iPos = 0; iPos < uiObject.children.length; ++iPos) {
                            uiObject.children[iPos].destroy();
                        }
                    }

                    function hidePageNavigation() {
                        console.log("Hidding Page Navigator!");
                        pageNavigation.visible = false;
                        pageView.anchors.bottom = pageView.parent.bottom;
                    }

                    function showPageNavigation() {
                        console.log("Showing Page Navigator!");
                        pageNavigation.visible = true;
                        pageView.anchors.bottom = pageNavigation.top;
                    }

                    function createPages(groupName) {
                        console.log("page " + page + " has a complex type: " + componentHasComplexType(page));
                        var editValues = controller.getValuesOfGroup(groupName);
                        var valueCount = editValues.length;
                        if (valueCount > 0 && !componentHasComplexType(page)) {
                            createGroupComponents(groupName);
                        } else {
                            createEditorComponentComplexType(page);
                        }
                    }

                    function createGroupComponents(groupName) {
                        var editValues = controller.getValuesOfGroup(groupName);
                        var valueCount = editValues.length;
                        console.log("Value count: " + valueCount);
                        contentLayout.rows = editValues.length + 1; // for test

                        for (var iCounter = 0; iCounter < editValues.length; ++iCounter) {

                            var valueElement = editValues[iCounter];
                            if (valueElement !== null) {
                                createEditorComponent(valueElement);
                            }
                        }
                        var spacerHeight = wmsApp.getCentralWindow().height - contentLayout.height + 50;
                        var itemString = "import QtQuick 2.2; import QtQuick.Layouts 1.1; Item { id: spacer; height: " + spacerHeight + " }";
                        var newObject = Qt.createQmlObject(itemString, contentLayout, "spacer");
                    }

                    function createEditorComponent(valueElement) {

                        if (valueElement !== null) {
                            if (!controller.isComplexUiType(valueElement)) {
                                createEditorComponentSimpleType(valueElement)
                            } else {
                                console.log("Component of complex type tried to create with simpletype creator.");
                            }
                        }
                    }

                    function createEditorComponentSimpleType(valueElement) {

                        if (valueElement !== null) {
                            var uiName = controller.getQmlElementByValue(valueElement);
                            console.log("Ui Elementname: " + uiName);
                            console.log("Value Keyname: " + valueElement.getKeyname());

                            var component = Qt.createComponent(uiName);
                            if (component.status === Component.Ready) {

                                var uiElement = component.createObject(contentLayout);

                                if (uiElement !== null) {
                                    console.log("Ui Element created");
                                    uiElement.fillData(valueElement);
                                } else {
                                    console.log("Ui Element not created");
                                }
                                console.log("Grid Child count:" + contentLayout.children.length);
                                console.log("Page Navigation :" + pageNavigation.visible);

                            } else {
                                console.log("Component not created! Status: " + component.status);
                                console.log(component.errorString());
                            }
                        }
                    }

                    function componentHasComplexType(pageNumber) {
                        var valueElement = controller.getComplexValueAt(getGroupName(), pageNumber);

                        if (valueElement !== null) {
                            return true;
                        } else {
                            return false;
                        }
                    }

                    function createEditorComponentComplexType(pageNumber) {
                        var valueElement = controller.getComplexValueAt(getGroupName(), pageNumber);

                        if (valueElement !== null) {
                            createEditorComponentSimpleType(valueElement);
                        } else {
                            console.log("Complex component for page " + pageNumber + " not found.");
                        }
                    }
                }
            }
        }
    }

    Loader {
        id: itemDisplay
        anchors.fill: parent;
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        sourceComponent: contentComponent
        onStatusChanged: if (itemDisplay.status == Loader.Ready) pageView.currentIndex = 0
    }
}
