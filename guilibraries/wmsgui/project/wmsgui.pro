TEMPLATE = lib
TARGET = wmsgui

!CONFIG(no_precompile_header):CONFIG += precompile_header

QT += core sql network xml script widgets gui qml printsupport quick location positioning

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

message("WMSGUI DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

#    IGNORE_ERRORS += -Wno-error=unused-parameter -Wno-error=unused-but-set-variable
#    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
#    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
#}

DEFINES += QT_NO_OPENGL WMSGUI_EXPORTS

INCLUDEPATH += \
    ./$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../core/wmscore/Src/DataManagement \
    ./../../../core/wmscore/Src/UserManagement \
    ./../../../core/wmscore/Src/SimpleApi \
    ./../../../guilibraries/wmsqml/ui \
    ./../../../guilibraries/wmsqml/src \
    ./../../../core/wmsentities/src \
    ./../../../core/wmscommons/src \
    ./../../../guilibraries/wmsusermanagerlib/project/GeneratedFiles \
    ./../../../guilibraries/wmsusermanagerlib/project \
    $$OUT_PWD/../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../guilibraries/wmsusermanagerlib/src \
    ./../src \
    ./../src/ObjectEditor \
    ./../src/RightsManager \
    ./../src/misc \
    ./../../../thirdparty/openldap/Windows/include \
    $$UI_DIR \
.
LIBS += -L$$DESTDIR \
    -lwmsqml \
    -lwmsentities \
    -lwmsusermanagerlib \
    -lwmscore \
    -lwmscommons

include(wmsgui.pri)

SOURCES += \
    ../src/misc/CwmsQueryEditorDlg.cpp

HEADERS += \
    ../src/misc/CwmsQueryEditorDlg.h

FORMS += \
    ../src/misc/CwmsQueryEditorDlg.ui








