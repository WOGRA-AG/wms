import QtQuick.Controls 1.3
import QtQuick 2.2
import QtQuick.Window 2.1
import com.wogra.wmsqml 1.0

Window {
    id: wmsWindow;
    title: "WMS";
//    height: 400
//    width: 360
    height: wmsStyle.getContentHeight()
    width: wmsStyle.getContentWidth()

    color: "#ffffff"

    property Item currentPage: null;
    WmsApplicationModule {
        id: currentModule
    }


    Loader {
        id: contentLoader;
        anchors.fill: parent
        onLoaded: {
            //console.log("Content loaded at WmsWindow: " + contentLoader.source);
            wmsApp.setCurrentContent(contentLoader.item);
        }
    }

    Component.onCompleted: {
        openPageFile(wmsLogin.getDialogUrl());
    }


    function openPageQml(qml, name) {
        // Qt.createQmlObject parameters: source, parent, name
        var newPage = Qt.createQmlObject(qml, wmsWindow, name);

        if (newPage !== null) {
            currentPage = newPage;
            wmsApp.setCurrentContent(newPage);
        }
    }

    function openPageFile(filename) {
        currentPage = null;
        contentLoader.setSource(filename);
    }

    function loadMainWindow() {

        //console.log("Show Main Window");

        if (wmsApp.hasCustomMainWindow() === true) {
            var mainWindow = wmsApp.loadCustomMainWindow();
            openPageQml(mainWindow, "MainWindow");
        }
        else {
            var mainWindow = wmsApp.getDefaultMainWindowName();
            openPageFile(mainWindow);
        }
    }

    function loadModule(moduleId) {

        //console.log("start loading Module " + moduleId);
        var application = wmsApp.getApplication();

        if (application !== null) {
            var moduleObject = application.loadModule(moduleId);
            //console.log("Module loaded");

            if (moduleObject !== null) {
                currentModule.setObject(moduleObject);
                //console.log("Module Object created");
            }
        }

        //console.log("loading Module finished " + moduleId);
        return currentModule;
    }
}

