TEMPLATE = lib
TARGET = messageserver
QT += core network widgets gui

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

DESTDIR = $$OUT_PWD/../../../../../bin/$$WMS_ARCH/$$WMS_MODE
MOC_DIR = $$OUT_PWD/$$WMS_ARCH/moc/$$WMS_MODE
OBJECTS_DIR = $$OUT_PWD/$$WMS_ARCH/obj/$$WMS_MODE
UICIMPLS = $$OUT_PWD/$$WMS_ARCH/uic/$$WMS_MODE

message("MESSAGESERVER DESTDIR: "$$DESTDIR)

DEFINES += QMF_ENABLE_LOGGING MESSAGESERVER_INTERNAL
INCLUDEPATH += . \
    ./../qtopiamail \
    ./../qtopiamail/support
LIBS += -L$$DESTDIR -lqtopiamail -lqmfutil

include(messageserver.pri)
