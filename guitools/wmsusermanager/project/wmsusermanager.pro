TEMPLATE = app
TARGET = wmsusermanager

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

DESTDIR = $$DESTDIR/$$WMS_ARCH/$$WMS_MODE
MOC_DIR = $$OUT_PWD/$$WMS_ARCH/moc/$$WMS_MODE
OBJECTS_DIR = $$OUT_PWD/$$WMS_ARCH/obj/$$WMS_MODE
UICIMPLS = $$OUT_PWD/$$WMS_ARCH/uic/$$WMS_MODE

message("WMSUSERMANAGER DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra
#}

QT += core script widgets gui
INCLUDEPATH += ./../../../core/wmscore/Src/DataManagement \
    ./../../../core/wmscore/Src/UserManagement \
    ./../../../core/wmscore/Src/SimpleApi \
    ./../src \
    ./../../../guilibraries/wmsgui/project/GeneratedFiles \
    ./../../../guilibraries/wmsgui/project \
    ./../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
    $$OUT_PWD/../../../guilibraries/wmsgui/project/$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../guilibraries/wmsusermanagerlib/project/GeneratedFiles \
    ./../../../guilibraries/wmsusermanagerlib/project \
    $$OUT_PWD/../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../guilibraries/wmsusermanagerlib/src \
    ./../../../guilibraries/wmsgui/src \
    ./../../../guilibraries/wmsgui/src/misc \
    ./../../../core/wmscommons/src \
    ./debug \
    .

LIBS += -L$$DESTDIR \
    -lwmscommons \
    -lwmscore \
    -lwmsusermanagerlib \
    -lwmsgui

QMAKE_RPATHDIR += $$DESTDIR

include(wmsusermanager.pri)
