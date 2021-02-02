HEADERS += ../src/CwqQmlObjectViewer.h \
    ../src/wmsqml_global.h \
    ../src/CwqObjectEditorGenerator.h \
    ../src/CwqObjectEditorController.h \
    ../src/CwmsQmlApplicationController.h \
    ../src/CwmsQmlWidget.h \
    ../src/CwmsQmlLogin.h \
    ../src/CwmsQmlApplicationSelection.h \
    ../src/CwmsQmlDatabaseSelection.h \
    ../src/CwmsQmlStyle.h \
    ../src/CwmsQmlStyleAndroid.h \
    ../src/CwmsQmlStyleIOS.h \
    ../src/CwmsQmlHelper.h \
    ../src/CwqDocumentHandler.h \
    ../src/CwmsqmlApplication.h \
    ../src/CwmsqmlApplicationModule.h \
    ../src/CwmsQmlContainerEditor.h \
    $$PWD/../src/CwmsqmlImageProvider.h \
    $$PWD/../src/CwmsQmlEngineInitializer.h

SOURCES += \
    ../src/CwqQmlObjectViewer.cpp \
    ../src/CwqObjectEditorGenerator.cpp \
    ../src/CwqObjectEditorController.cpp \
    ../src/CwmsQmlApplicationController.cpp \
    ../src/CwmsQmlWidget.cpp \
    ../src/CwmsQmlLogin.cpp \
    ../src/CwmsQmlApplicationSelection.cpp \
    ../src/CwmsQmlDatabaseSelection.cpp \
    ../src/CwmsQmlStyle.cpp \
    ../src/CwmsQmlStyleAndroid.cpp \
    ../src/CwmsQmlStyleIOS.cpp \
    ../src/CwmsQmlHelper.cpp \
    ../src/CwqDocumentHandler.cpp \
    ../src/CwmsqmlApplication.cpp \
    ../src/CwmsqmlApplicationModule.cpp \
    ../src/CwmsQmlContainerEditor.cpp \
    $$PWD/../src/CwmsqmlImageProvider.cpp \
    $$PWD/../src/CwmsQmlEngineInitializer.cpp


RESOURCES += ../src/wmsqml.qrc


lupdate_only {
    SOURCES = ../src/*.qml \
              ../src/*.js
}

DISTFILES +=
