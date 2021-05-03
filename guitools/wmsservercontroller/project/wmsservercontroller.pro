TEMPLATE = app
TARGET = wmsservercontroller

win32{
   WMS_ARCH = mingw32
   RC_FILE = $$OUT_PWD/logo.rc
}
else:macx{
   WMS_ARCH = macx
   ICON = $$OUT_PWD/wmsserver.icns
}
else:ios{
   WMS_ARCH = ios
}
else:android{
   WMS_ARCH = android
}
else:linux{
   WMS_ARCH = linux
}
else:unix{
   WMS_ARCH = unix
}

CONFIG(release, debug|release){
   WMS_MODE = release
}
else:CONFIG(debug, debug|release): {
   WMS_MODE = debug
}

DESTDIR = $$OUT_PWD/../../../../bin/$$WMS_ARCH/$$WMS_MODE
MOC_DIR = $$OUT_PWD/$$WMS_ARCH/moc/$$WMS_MODE
OBJECTS_DIR = $$OUT_PWD/$$WMS_ARCH/obj/$$WMS_MODE
UICIMPLS = $$OUT_PWD/$$WMS_ARCH/uic/$$WMS_MODE
UI_DIR = $$OUT_PWD/$$WMS_ARCH/ui/$$WMS_MODE

message("WMSSERVERCONTROLLER DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra
#}

QT = core gui widgets script

INCLUDEPATH += ./../../../guilibraries/wmsgui/src \
               ./../../../guilibraries/wmsgui/src/misc \
               ./../../../guilibraries/wmsgui/project \
               ./../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
               $$OUT_PWD/../../../guilibraries/wmsgui/project/$$WMS_ARCH/ui/$$WMS_MODE \
               ./../../../thirdparty/qtservice/src \
               ./../../../core/wmscore/Src/DataManagement \
               ./../../../core/wmscore/Src/UserManagement \
               ./../../../core/wmscore/Src/SimpleApi \
               ./../../../core/wmsentities/src \
               ./../../../core/wmscommons/src \
               $$UI_DIR

LIBS += -L$$DESTDIR \
        -lwmsgui \
        -lqtservice \
        -lwmsentities \
        -lwmscore \
        -lwmscommons

QMAKE_RPATHDIR += $$DESTDIR

SOURCES = ../src/main.cpp \
          ../src/CwsController.cpp \
    ../src/CwsServerConfig.cpp

HEADERS = ../src/CwsController.h \
    ../src/CwsServerConfig.h

FORMS += ../src/CwsController.ui \
    ../src/CwsServerConfig.ui

RESOURCES += ../src/servercontroller.qrc

#QMAKE_TARGET_COMPANY = "WOGRA"
#QMAKE_TARGET_PRODUCT = "WMS Server Controller"
#QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
#QMAKE_TARGET_DESCRIPTION = "server controller component for managing the server installation"

#DEFINES += \
#  APP_VERSION=\"\\\"$$VERSION\\\"\" \
#  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
#  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
#  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
#  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
