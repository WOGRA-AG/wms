TEMPLATE = app
TARGET = wmsneo4jtest
QT += core sql network script widgets gui testlib

DESTDIR = $$OUT_PWD/../../../../bin

win32{
   WMS_ARCH = mingw32
}
else:macx{
   WMS_ARCH = macx
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

message("WMSTEST DESTDIR: "$$DESTDIR)

INCLUDEPATH += ./../../../wmssqlite/src \
    ./../../../wmsodbc/src \
    ./../../../wmswebclient/src \
    ./../../../wmsmanager/Src/UserManagement \
    ./../../../wmsmanager/Src/DataManagement \
    ./../../../wmstools/basetools/src \
    ./../../../wmstools/wmscommons/src \
    ./../../wmsneo4j/src

LIBS += -L$$DESTDIR -L$$DESTDIR/dataaccess \
    -lqtopiamail \
    -lqmfutil \
    -lmessageserver \
    -lantlr3c \
    -lwmscommons \
    -lwmsmanager \
    -lwmsbasetools \
    -lwmsneo4j \
    -lwmsqml \
    -lwmsusermanagerdll \
    -lwmsgui

include(wmsneo4jtest.pri)


