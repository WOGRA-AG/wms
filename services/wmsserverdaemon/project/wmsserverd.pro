TEMPLATE = app
config+= console qt
TARGET = wmsserverd

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

message("WMSSERVER DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

    IGNORE_ERRORS += -Wno-error=unused-variable
    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
}

QT += core sql network script widgets gui qml
INCLUDEPATH += ./../../../core/wmscommons/src \
               ./../../../thirdparty/qtservice/src

LIBS += -L$$DESTDIR \
    -lwmscommons \
    -lqtservice

include(wmsserverd.pri)

QMAKE_TARGET_COMPANY = "WOGRA"
QMAKE_TARGET_PRODUCT = "WMS Server Daemon"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
QMAKE_TARGET_DESCRIPTION = "server daemon executable for WMS"

DEFINES += \
  APP_VERSION=\"\\\"$$VERSION\\\"\" \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
