TEMPLATE = app
TARGET = wmsplugin
QT += core script sql network scripttools xml widgets
CONFIG += console

win32{
   WMS_ARCH = mingw32
}
else:macx{
   WMS_ARCH = macx
}
else:ios{
   WMS_ARCH = ios
   DEFINES += WMS_LINK_STATIC
}
else:android{
   WMS_ARCH = android
   DEFINES += WMS_NO_LDAP
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

message("WMSPLUGINS DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra
}

INCLUDEPATH +=    ./../../../core/wmscore/Src/DataManagement \
    ./../../../core/wmscore/Src/UserManagement \
    ./../../../core/wmscore/Src/SimpleApi \
    ./../src \
    ./../../../core/wmsentities/src \
    ./../../../core/wmscommons/src

LIBS +=  -L$$DESTDIR \
    -lwmsentities \
    -lwmscommons \
    -lwmscore

QMAKE_RPATHDIR += $$DESTDIR

contains(DEFINES, WMS_LINK_STATIC) {
LIBS +=  -L$$DESTDIR/dataaccess \
         -lwmswebclient \
         -lwmssqlite \
         -lwmsodbc \
}

include(wmsplugin.pri)


QMAKE_TARGET_COMPANY = "WOGRA"
QMAKE_TARGET_PRODUCT = "WMS Plugin Manager Console App"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
QMAKE_TARGET_DESCRIPTION = "Managing WMS Plugins"

DEFINES += \
  APP_VERSION=\"\\\"$$VERSION\\\"\" \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
