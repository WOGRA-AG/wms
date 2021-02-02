QT += core network
QT -= gui

CONFIG += c++11

TARGET = wmsclienttest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

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

message("WMSCLIENTTEST DESTDIR: "$$DESTDIR)


SOURCES += ../src/main.cpp \
    ../src/CwmsRestApiTestMultiThreaded.cpp \
    ../src/CwmsRestRequestSender.cpp


INCLUDEPATH += ./../../../core/wmscommons/src

LIBS += -L$$DESTDIR -lwmscommons

HEADERS += \
    ../src/CwmsRestApiTestMultiThreaded.h \
    ../src/CwmsRestRequestSender.h
