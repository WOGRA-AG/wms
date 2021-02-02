import QtQuick 2.2
import com.wogra.wmscore 1.0
import QtQuick.Controls 1.2


Rectangle {
    id: moduleSelectionArea

    color: wmsStyle.getNavigationBarColor()
    signal clicked;
    //for swipe menu
//    opacity: wmsMainWindowTablet.menu_shown ? 1 : 0
//    Behavior on opacity { NumberAnimation { duration: 300 } }
    anchors.fill: parent

    ListView {
        id: moduleListView
        anchors.fill: parent

        delegate: WmsModuleSelectionDelegate {
            onClicked: {
               // ToDo
                //console.log("Module selected")
               moduleSelectionArea.clicked();
            }
        }
        boundsBehavior: Flickable.StopAtBounds;

        footer: footerComponent

    }

    Component {
        id: footerComponent
        Column {
            //seperator
            Item { height: 20; width: moduleListView.width; }
            Rectangle { width: moduleListView.width / 2; height: 1; color: wmsStyle.getSeperatorColor() }
            Item { height: 20; width: moduleListView.width; }

            WmsModuleSelectionOptions {
                id: printButton
                image: "../icons/print32.png"
                onClicked: wmsMainWindowTablet.printClicked();
                text: "PrintButton"
            }

            WmsModuleSelectionOptions {
                id: journalButton
                image: "../icons/printpreview32.png"
                onClicked: wmsMainWindowTablet.journalClicked();
                text: "journalButton"
            }

            WmsModuleSelectionOptions {
                id: languageButton
                image: "../icons/languages.png"
                onClicked: wmsMainWindowTablet.languagesClicked();
                text: "languageButton"
            }

            WmsModuleSelectionOptions {
                id: aboutButton
                image: "../icons/about32.png"
                onClicked: wmsMainWindowTablet.aboutClicked();
                text: "aboutButton"
            }

            WmsModuleSelectionOptions {
                id: helpButton
                image: "../icons/help32.png"
                onClicked: wmsMainWindowTablet.helpClicked();
                text: "helpButton"
            }

            WmsModuleSelectionOptions {
                id: exitButton
                image: "../icons/exit24.png"
                onClicked: wmsMainWindowTablet.exitClicked();
                text: "exitButton"
            }
        }
    }




    Component.onCompleted: {
        var modulesContainer = wmsApp.getApplication().getModulesContainerName();
        var query = "select Name, Icon, Position from \"" + modulesContainer + "\" where Active = true order by Position";

        var factory = wmsApp.getFactory();

        if (factory !== null){
            var moduleModel = factory.createQueryModel();
            moduleModel.execute(query);
            moduleListView.model = moduleModel;
          //            console.log("Rowcount of Modules:" + moduleModel.rowCount());
            //            console.log("Column count of Modules:" + moduleModel.columnCount());
            //            console.log("First Entry: " + moduleModel.data(0,0));
       }
    }

    function getSelectedModuleId() {

        var moduleModel = moduleListView.model;
        var selectedObject = null;

        if (moduleModel !== null) {
            var queryObject = moduleModel.getQuery();

            if (queryObject !== null) {
                selectedObject = queryObject.getObjectIdAt(moduleListView.currentIndex);
            } else {
                console.error("Query Object is null");
            }
        } else {
            console.error("Model is null");
        }

        return selectedObject;
    }
}
