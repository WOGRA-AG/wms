TEMPLATE = lib
TARGET = wmsusermanagerlib

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
UI_DIR = $$OUT_PWD/$$WMS_ARCH/ui/$$WMS_MODE

message("WMSUSERMANAGERDLL DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra
}

QT += core script widgets gui
DEFINES += WMSUSERMANAGERDLL_LIB
INCLUDEPATH +=  ./../../../core/wmscore/Src/DataManagement \
    ./../../../core/wmscore/Src/UserManagement \
    ./../../../core/wmscore/Src/SimpleApi \
    ./../src \
    ./../../../core/wmscommons/src \
    ./debug \
    $$UI_DIR \
    .

LIBS += -L$$DESTDIR -lwmscore -lwmscommons
include(wmsusermanagerlib.pri)


