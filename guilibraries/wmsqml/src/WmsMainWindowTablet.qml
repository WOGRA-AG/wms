import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls 1.2
import com.wogra.wmsqml 1.0
import QtGraphicalEffects 1.0

Rectangle {
    id: wmsMainWindowTablet
    height: 768
    width: 1024
    anchors.fill: parent
    property bool menu_shown: false
    property int curMouseX: 0

    Rectangle {
        id: mainGrid
        //columns: 1
        anchors.fill: parent

        WmsModuleSelection {
            id: modulesSelectionArea
            onClicked: {
                wmsMainWindowTablet.onMenu();
                var selectedModuleId = getSelectedModuleId();
                var appModule = loadModule(selectedModuleId);
                wmsMainWindowTablet.showModule(appModule);
            }
        }

        Rectangle {
            id: contentRectangle
            anchors.fill: parent
            color: wmsStyle.getBackgroundColor()

            transform: Translate {
                id: swipe_translate
                x: 0
                Behavior on x {
                    NumberAnimation {
                        id: test
                        duration: 400; easing.type: Easing.OutQuad;
                        onRunningChanged: {
                            if(!running) {
                                modulesSelectionArea.visible = wmsMainWindowTablet.menu_shown;
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: navigation
                implicitHeight: wmsMainWindowTablet.width < 500 ? wmsStyle.getNavigationBarSize() : 20 + wmsMainWindowTablet.width * wmsStyle.getTextScale()
                width: parent.width
                color: wmsStyle.getNavigationBarColor()
                anchors.top: contentRectangle.top

                RowLayout {
                    id: navigationLayout
                    anchors.fill: parent
                    anchors.leftMargin: Math.round(wmsMainWindowTablet.width * 0.78125) / 100
                    anchors.rightMargin: Math.round(wmsMainWindowTablet.width * 0.78125) / 100

                    WmsToolButton {
                        id: menu_button
                        image: "../icons/menu_icon.svg"
                        parentWindow: wmsMainWindowTablet.width
                        scale: menu_button.pressed ? 1.2 : 1
                        onClicked: {
                            if(!wmsMainWindowTablet.menu_shown) {
                                modulesSelectionArea.visible = true;
                                wmsMainWindowTablet.onMenu();
                            }
                        }
                    }

                    WmsToolButton {
                        id: menu_back_button
                        image: "../icons/menu_back_icon.svg"
                        parentWindow: wmsMainWindowTablet.width
                        visible: false
                        scale: menu_back_button.pressed ? 1.2 : 1
                        onClicked: wmsMainWindowTablet.cancelClicked();
                    }

                    Item { Layout.fillWidth: true }

                    WmsToolButton {
                        id: okButton
                        image: wmsStyle.getOkButton()
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.okClicked();
                    }

                    WmsToolButton {
                        id: cancelButton
                        image: wmsStyle.getCancelButton()
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.cancelClicked();
                    }


                    WmsToolButton {
                        id: newButton
                        image: "../icons/new32.png"
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.newClicked();
                    }

                    WmsToolButton {
                        id: editButton
                        image: "../icons/edit32.png"
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.editClicked();
                    }

                    WmsToolButton {
                        id: deleteButton
                        image: "../icons/delete32.png"
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.deleteClicked();
                    }

                    WmsToolButton {
                        id: searchButton
                        image: "../icons/search32.png"
                        parentWindow: wmsMainWindowTablet.width
                        onClicked: wmsMainWindowTablet.searchClicked();
                    }
                }
            }

            RowLayout {
                id: applicationGrid
                anchors.top: navigation.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Loader {
                    id: contentAreaLoader;
                    anchors.fill: parent

                    onLoaded: {
                        //                        console.log("Content loaded at WmsMainWindowTablet: " + contentAreaLoader.source);
                        //                        contentAreaLoader.status = false
                        // ToDo
                    }
                }

                Connections {
                    id: actionConnection
                    target: contentAreaLoader.item
                    onEditObject: {
                        editClicked();
                    }

                    onCreateObject: {
                        showObjectEditorNewObject(newObject);
                    }
                }
            }

            BorderImage {
                id: menu_shadow
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: -25
                z: 1
                visible: wmsMainWindowTablet.menu_shown
                source: "../icons/menu_shadow.png"
                border { left: 12; top: 12; right: 12; bottom: 12 }
            }

            MouseArea {
                id: testArea
                anchors.fill: parent
                enabled: wmsMainWindowTablet.menu_shown
                onClicked:
                {
                    wmsMainWindowTablet.onMenu()
                }
            }

            layer.enabled: true
            layer.effect: BrightnessContrast {
                id: brightnessControl
                anchors.fill: parent
                brightness: wmsMainWindowTablet.menu_shown ? swipe_translate.x / -1000 < -0.5 ? -0.5 : swipe_translate.x / -1000 : 0.0

//                Behavior on brightness {
//                    NumberAnimation { duration: 400 }
//                }
            }

            MouseArea {
                id: mouseArea
                anchors.left: parent.left
                anchors.top: navigation.bottom
                height: parent.height - navigation.height
                width: 80
                visible: true
                onPressed:  {
                    curMouseX = mouseX;
                    modulesSelectionArea.visible = true;
                    wmsMainWindowTablet.menu_shown = true;
                    swipe_translate.x = wmsMainWindowTablet.width * 0.025
                }
                onPositionChanged: {
                    var maxWidthArea = wmsMainWindowTablet.height > wmsMainWindowTablet.width ? wmsMainWindowTablet.width * 0.8 : wmsMainWindowTablet.width * 0.5;
                    if(mouseX <= maxWidthArea){
                        if(mouseX < 0){
                        }
                        else {
                            swipe_translate.x = mouseX;
                            console.log(swipe_translate.x / -1000)
                        }
                    }
                }
                onReleased: {
                    if(mouseX > curMouseX + 80) {
                        swipe_translate.x = wmsMainWindowTablet.height > wmsMainWindowTablet.width ? wmsMainWindowTablet.width * 0.8 : wmsMainWindowTablet.width * 0.5
                        mouseArea.visible = false;
                    }
                    else {
                        wmsMainWindowTablet.menu_shown = false;
                        swipe_translate.x = 0
                        mouseArea.visible = true;
                    }
                }
            }

        }
    }

    Component.onCompleted: {
        //console.log("Looking for default module.")
        var defaultModule = wmsApp.getDefaultModule();

        if (defaultModule !== null) {
            //console.log("Default Module found " + defaultModule);
            currentModule.setObject(defaultModule);
            showModule(currentModule);
        } else {
            //console.log("No default module found!")
            hideContainerEditorButtons();
            hideObjectEditorButtons();
        }
    }


    function showModule(appModule) {
        if (appModule !== null) {
            //console.log("open module");
            var uiDef = appModule.getUserInterface();

            if (uiDef === null) {
                if (appModule.getContainerModule() !== null) {
                    showContainerModule(appModule);
                } else if (appModule.getObjectModule() !== null) {
                    showObjectModule(appModule);
                } else {
                    //console.log("Invalid module");
                }
            } else {
                showUserInterfaceModule(appModule);
            }



        } else {
            //console.log("invalid object");
        }
    }

    function showContainerModule(appModule) {
        contentAreaLoader.source = "";
        contentAreaLoader.source = wmsApp.getContainerEditorName();
        contentAreaLoader.item.setModule(appModule, wmsMainWindowTablet);
        showContainerEditorButtons();
        hideObjectEditorButtons();
        //printButton.visible = contentAreaLoader.item.hasPrinting();
        addModuleToCallStack(appModule);

    }

    function showContainerEditor(container) {
        contentAreaLoader.source = "";
        contentAreaLoader.source = wmsApp.getContainerEditorName();
        contentAreaLoader.item.setContainer(container);
        showContainerEditorButtons();
        hideObjectEditorButtons();
        contentAreaLoader.item.hideButtons();
        addToCallStack(container);
    }

    function showObjectModule(appModule) {
        //console.log("Object module");
        hideContainerEditorButtons();
        showObjectEditorButtons();
        contentAreaLoader.source = "WmsObjectEditor.qml";
        contentAreaLoader.item.setModule(appModule, wmsMainWindowTablet);
        addModuleToCallStack(appModule);
    }

    function showObjectEditor(editObject) {
        if (editObject !== null) {
            hideContainerEditorButtons();
            showObjectEditorButtons();
            contentAreaLoader.source = "WmsObjectEditor.qml";
            contentAreaLoader.item.setObject(editObject, false);
        }
    }

    function showObjectEditorNewObject(editObject) {
        if (editObject !== null) {
            hideContainerEditorButtons();
            showObjectEditorButtons();
            contentAreaLoader.source = "WmsObjectEditor.qml";
            contentAreaLoader.item.setObject(editObject, true);
        }
    }

    function addModuleToCallStack(appModule) {

        var locatedElement = null;
        var uiDefName = null;

        if (appModule.getContainerModule() !== null) {
            locatedElement = appModule.getContainerModule();
        } else if (appModule.getObjectModule() !== null) {
            locatedElement = appModule.getObjectModule();
        }

        var uiDef = appModule.getUserInterface();

        if (uiDef !== null) {
            uiDefName = uiDef.getUri();
        }
        wmsApp.pushViewToStack(appModule.getId(), uiDefName, locatedElement.getUri());
    }

    function addToCallStack(locatedElement) {
        wmsApp.pushViewToStack(0, "", locatedElement.getUri());
    }

    function showUserInterfaceModule(appModule) {
        //console.log("Module with defined User Interface");

        /* ToDo
        openCustomUserInterface

        */
        addModuleToCallStack(appModule);
    }

    function hideObjectEditorButtons() {
        changeObjectEditorButtonsVisibilty(false);
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
        editButton.visible = visibility;
        deleteButton.visible = visibility;
        searchButton.visible = visibility;
        cancelButton.visible = visibility;
        menu_button.visible = visibility;
        mouseArea.visible = visibility;
        menu_back_button.visible = !visibility;
    }

    function changeContainerEditorButtonsEnableDisable(enabled) {
        newButton.enabled = enabled;
        editButton.enabled = enabled;
        deleteButton.enabled = enabled;
    }

    function helpClicked() {
        hideContainerEditorButtons();
        okButton.visible = false;
        var helpText = wmsApp.getApplication().getHelp();
        contentAreaLoader.source = "WmsInfoContent.qml";
        contentAreaLoader.item.content = helpText;
        wmsMainWindowTablet.onMenu();
    }

    function exitClicked() {
        //console.log("exitClicked");
        wmsApp.quit();
    }

    function aboutClicked() {
        //console.log("aboutClicked");
        wmsMainWindowTablet.onMenu();
    }

    function languagesClicked() {
        //console.log("languagesClicked");
        wmsMainWindowTablet.onMenu();
    }

    function journalClicked() {
        contentAreaLoader.item.journalClicked();
        wmsMainWindowTablet.onMenu();
    }

    function printClicked() {
        contentAreaLoader.item.printClicked();
    }

    function searchClicked() {
        contentAreaLoader.item.searchClicked();
    }

    function deleteClicked() {
        contentAreaLoader.item.deleteClicked();
    }

    function editClicked() {
        var selectedObject = contentAreaLoader.item.getSelectedObject();

        if (selectedObject !== null) {
            showObjectEditor(selectedObject);
        }
    }

    function newClicked() {
        contentAreaLoader.item.newClicked();
    }

    function okClicked() {
        contentAreaLoader.item.okClicked();
        modulesSelectionArea.enabled = true;
        restoreLastView()
    }

    function cancelClicked() {
        contentAreaLoader.item.cancelClicked();
        modulesSelectionArea.enabled = true;
        restoreLastView()
    }

    function restoreLastView() {
        var viewConfig = wmsApp.popViewFromStack();
        if (viewConfig !== null) {
            var moduleId = viewConfig.getModuleId();

            if (moduleId > 0) {
                var appModule = loadModule(moduleId);
                wmsMainWindowTablet.showModule(appModule);

            } else {
                var uiName = viewConfig.getUiName();

                if (uiName.length > 0) {
                    openCustomUserInterface(uiName, viewConfig.getLocatedElement());
                } else {
                    if (viewConfig.isContainerEditor()) {
                        showContainerEditor(viewConfig.getLocatedElement());
                    } else if (viewConfig.isObjectEditor()) {
                        showObjectEditor(viewConfig.getLocatedElement());
                    }
                }
            }

        } else {
            console.log("Nothing to restore!!!");
        }
    }

    /* this functions toggles the menu and starts the animation */
    function onMenu()
    {
        swipe_translate.x = wmsMainWindowTablet.menu_shown ? 0 : wmsMainWindowTablet.width < 500 ? wmsMainWindowTablet.width * 0.8 : wmsMainWindowTablet.width * 0.5
        wmsMainWindowTablet.menu_shown = !wmsMainWindowTablet.menu_shown;
        mouseArea.visible = !wmsMainWindowTablet.menu_shown;
    }

    onWidthChanged: {
        if(wmsMainWindowTablet.menu_shown)
            swipe_translate.x = wmsMainWindowTablet.width < 500 ? wmsMainWindowTablet.width * 0.8 : wmsMainWindowTablet.width * 0.5
    }

    function openCustomUserInterface(uiDefUri,displayElement) {
    }
}
