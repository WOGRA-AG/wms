TEMPLATE = lib
TARGET = wmsftl

!CONFIG(no_precompile_header):CONFIG += precompile_header

win32{
   WMS_ARCH = mingw32
   DEFINES += WMS_LDAP
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
   DEFINES += WMS_LDAP
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

DESTDIR = $$DESTDIR/dataaccess
message("WMSFTL DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

    IGNORE_ERRORS += -Wno-error=unused-parameter
    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
}

QT += core sql script gui quick qml
DEFINES += WMSDB_EXPORTS
INCLUDEPATH += ./../../../core/wmscore/Src/DataManagement \
               ./../../../core/wmscore/Src/UserManagement \
               ./../../../core/wmscore/Src/SimpleApi \
               ./../../../core/wmsentities/src \
               ./../../../core/wmscommons/src

LIBS += -L$$DESTDIR/.. -lwmscommons -lwmscore -lwmsentities
include(wmsftl.pri)

