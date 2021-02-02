import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import com.wogra.wmscore 1.0

Rectangle {
    id: wmsMainWindowMobile
    height: wmsStyle.getContentHeight()
    width: wmsStyle.getContentWidth()
    color: wmsStyle.getBackgroundColor()

    WmsModel {
        id: moduleModel
    }

    GridLayout {
        id: mainGrid
        columns: 1
        anchors.fill: parent

        ComboBox {
            id: moduleSelection
            Layout.fillWidth: true;

            onCurrentIndexChanged: {
                moduleSelected();
            }
        }

        Rectangle {
            id: contentRectangle
            anchors.top: moduleSelection.bottom
            anchors.bottom: navigation.top
            color: wmsStyle.getBackgroundColor()
            Layout.fillWidth: true


            Loader {
                id: contentAreaLoader;
                anchors.fill: parent

                onLoaded: {
                    console.log("Content loaded: " + contentLoader.source);
                    // ToDo
                }
            }
        }

        Rectangle {
            id: navigation
            height: wmsStyle.getNavigationBarSize()
            color: wmsStyle.getNavigationBarColor()
            anchors.bottom: parent.bottom
            Layout.fillWidth: true


            RowLayout {
                id: navigationLayout
                anchors.fill: parent

                ToolButton {
                    id: okButton
                    iconSource: wmsStyle.getOkButton()
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.newClicked();
                }

                ToolButton {
                    id: cancelButton
                    iconSource: wmsStyle.getCancelButton()
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.editClicked();
                }


                ToolButton {
                    id: newButton
                    iconSource: "../icons/new32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.newClicked();
                }

                ToolButton {
                    id: printButton
                    iconSource: "../icons/print32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.printClicked();
                }

                ToolButton {
                    id: searchButton
                    iconSource: "../icons/search32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.searchClicked();
                }

                ToolButton {
                    id: journalButton
                    iconSource: "../icons/printpreview32.png"
                    height: wmsStyle.getToolButtonSize()
                    width: wmsStyle.getToolButtonSize()
                    onClicked: wmsMainWindowMobile.journalClicked();
                }


                ToolButton {
                   id: languageButton
                   iconSource: "../icons/languages.png"
                   height: wmsStyle.getToolButtonSize()
                   width: wmsStyle.getToolButtonSize()
                   onClicked: wmsMainWindowMobile.languageClicked();
                }

                ToolButton {
                    id: aboutButton
                   iconSource: "../icons/about32.png"
                   height: wmsStyle.getToolButtonSize()
                   width: wmsStyle.getToolButtonSize()
                   onClicked: wmsMainWindowMobile.aboutClicked();
                }

                ToolButton {
                    id: helpButton
                   iconSource: "../icons/help32.png"
                   height: wmsStyle.getToolButtonSize()
                   width: wmsStyle.getToolButtonSize()
                   onClicked: wmsMainWindowMobile.helpClicked();
                }

                ToolButton {
                    id: exitButton
                   iconSource: "../icons/exit24.png"
                   height: wmsStyle.getToolButtonSize()
                   width: wmsStyle.getToolButtonSize()
                   onClicked: wmsMainWindowMobile.exitClicked();
                }

                Item { Layout.fillWidth: true }
            }
        }
    }

    Component.onCompleted: {
        var modulesContainer = wmsApp.getApplication().getModulesContainerName();
        var query = "select Name, Icon, Position from \"" + modulesContainer + "\" where Active = true order by Position";
        console.log(query);
        moduleModel.execute(query);
        moduleSelection.model = moduleModel;
        moduleSelection.textRole = "Name";

        var defaultModule = wmsApp.getDefaultModule();

        if (defaultModule !== null) {
            console.log("Default Module found");
            currentModule.setObject(defaultModule);
            showModule(currentModule);
        } else {
            console.log("No default module found!")
            hideContainerEditorButtons();
            hideObjectEditorButtons();
        }
    }

    function moduleSelected() {
        var selectedObjectId = getSelectedModuleId();
        console.log("Module Object ID: " + selectedObjectId);
        var appModule = loadModule(selectedObjectId);
        showModule(appModule);
    }

    function getSelectedModuleId() {

        var selectedObject = null;

        if (moduleModel !== null) {
            var queryObject = moduleModel.getQuery();

            if (queryObject !== null) {
                selectedObject = queryObject.getObjectIdAt(moduleSelection.currentIndex);
            } else {
                console.error("Query Object is null");
            }
        } else {
            console.error("Model is null");
        }

        return selectedObject;
    }

    function showModule(appModule) {
        if (appModule !== null) {
            console.log("open module");

            var uiDef = appModule.getUserInterface();

            if (uiDef === null) {
                if (appModule.getObjectListModule() !== null) {
                    showContainerModule(appModule);
                } else if (appModule.getObjectModule() !== null) {
                    showObjectModule(appModule);
                } else {
                    console.log("Invalid module");
                }
            } else {
                showUserInterfaceModule(appModule);
            }

        } else {
            console.log("invalid object");
        }
    }

    function showContainerModule(appModule) {
        console.log("Container module");
        contentAreaLoader.source = "";
        contentAreaLoader.source = wmsApp.getContainerEditorName();
        contentAreaLoader.item.setModule(appModule, wmsMainWindowMobile);
        showContainerEditorButtons();
        hideObjectEditorButtons();
        printButton.visible = contentAreaLoader.item.hasPrinting();
    }

    function showObjectModule(appModule) {
        console.log("Object module");
        hideContainerEditorButtons();
        showObjectEditorButtons();

        /* ToDo
        contentAreaLoader.source = "WmsContainerEditor.qml";
        contentAreaLoader.item.setModule(appModule, wmsMmainWindowTablet);
        */
    }


    function showObjectEditor(editObject) {

    }

    function showUserInterfaceModule(appModule) {
        console.log("Module with defined User Interface");

        /* ToDo
        contentAreaLoader.source = "WmsContainerEditor.qml";
        contentAreaLoader.item.setModule(appModule, wmsMmainWindowTablet);
        */
    }

    function hideObjectEditorButtons() {
        changeObjectEditorButtonsVisibilty(false);
    }

    function helpClicked() {
        console.log("helpClicked");
        hideContainerEditorButtons();
        hideObjectEditorButtons();
        var helpText = wmsApp.getApplication().getHelp();
        contentAreaLoader.source = "WmsInfoContent.qml";
        contentAreaLoader.item.content = helpText;
    }

    function exitClicked() {
        console.log("exitClicked");
        wmsApp.quit();
    }

    function aboutClicked() {
        console.log("aboutClicked");
        hideContainerEditorButtons();
        hideObjectEditorButtons();
        contentAreaLoader.source = "WmsAboutViewer.qml";
    }

    function languagesClicked() {
        console.log("languagesClicked");
    }

    function journalClicked() {
        contentAreaLoader.item.journalClicked();
    }

    function printClicked() {
        contentAreaLoader.item.printClicked();
    }

    function searchClicked() {
        contentAreaLoader.item.searchClicked();
    }

    function newClicked() {
        contentAreaLoader.item.newClicked();

    }

    function editClicked() {
        var selectedObject = contentAreaLoader.item.getSelectedObject();

        if (selectedObject !== null) {
            showObjectEditor(selectedObject);
        }
    }

    function showObjectEditorButtons() {
        changeObjectEditorButtonsVisibilty(true);
    }

    function changeObjectEditorButtonsVisibilty(visibility) {
        okButton.visible = visibility;
        cancelButton.visible = visibility;
    }

    function hideContainerEditorButtons() {
        changeContainerEditorButtonsVisibilty(false);
    }

    function showContainerEditorButtons() {
        changeContainerEditorButtonsVisibilty(true);
    }

    function changeContainerEditorButtonsVisibilty(visibility) {
        newButton.visible = visibility;
        printButton.visible = visibility;
        journalButton.visible = visibility;
    }


}
