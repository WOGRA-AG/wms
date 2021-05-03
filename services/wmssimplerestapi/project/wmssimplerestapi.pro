TEMPLATE = lib
TARGET = wmssimplerestapi

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

DESTDIR = $$DESTDIR/servercommands
message("WMSINTERFACE DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

#    IGNORE_ERRORS += -Wno-error=unused-parameter -Wno-error=return-type -Wno-error=unused-variable
#    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
#    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
#}

QT += core sql xml script widgets gui qml
DEFINES += BMSINTERFACE_LIB
INCLUDEPATH += ./../../wmsrequestmanager/src \
               ./../../../core/wmsentities/src \
               ./../../../core/wmscommons/src \
               ./../../../guilibraries/wmsgui/src/misc \
               ./../../../core/wmscore/Src/DataManagement \
               ./../../../core/wmscore/Src/UserManagement \
               ./../../../core/wmscore/Src/SimpleApi

LIBS += -L$$DESTDIR/.. \
    -lwmsentities \
    -lwmscore \
    -lwmsrequestmanager \
    -lwmscommons

include(wmssimplerestapi.pri)

HEADERS += \
    ../src/CsraPlugin.h \
    ../src/CsraHandlerContainerManager.h

SOURCES += \
    ../src/CsraPlugin.cpp \
    ../src/CsraHandlerContainerManager.cpp



