TEMPLATE = lib
TARGET = wmscommons

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

message("WMSCOMMONS DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

    IGNORE_ERRORS += -Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=deprecated
    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
}

QT += core network
DEFINES += WMSCOMMONS_LIB
include(wmscommons.pri)

HEADERS += \
    ../src/CwmsCleanupMacros.h \
    ../src/CwmsCrypt.h \
    ../src/IwmsModel.h

SOURCES += \
    ../src/CwmsCrypt.cpp



