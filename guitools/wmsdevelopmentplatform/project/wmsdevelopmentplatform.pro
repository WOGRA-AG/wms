TEMPLATE = app
TARGET = wmsdp
QT += core sql script scripttools widgets gui printsupport qml

win32{
   WMS_ARCH = mingw32
   RC_FILE += logo.rc
}
else:macx{
   WMS_ARCH = macx
   ICON = $$OUT_PWD/wmsdeveloper.icns
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

message("WMSADMIN DESTDIR: "$$DESTDIR)

CONFIG(gcc, gcc|clang) {
    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

    IGNORE_ERRORS += -Wno-error=unused-variable
    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
}

DEFINES += QT_NO_OPENGL
INCLUDEPATH += \
    ./../../../core/wmscore/Src/DataManagement \
    ./../../../core/wmscore/Src/UserManagement \
    ./../../../core/wmscore/Src/SimpleApi \
    ./../src \
    ./../../../core/wmsentities/src \
    ./../../../guilibraries/wmsusermanagerlib/project/GeneratedFiles \
    ./../../../guilibraries/wmsusermanagerlib/project \
    ./../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
    $$OUT_PWD/../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../guilibraries/wmsusermanagerlib/src \
    ./../../../guilibraries/wmsqml/src \
    ./../../../guilibraries/wmsgui/project \
    $$OUT_PWD/../../../guilibraries/wmsgui/project/$$WMS_ARCH/ui/$$WMS_MODE \
    ./../../../guilibraries/wmsgui/src \
    ./../../../guilibraries/wmsgui/src/misc \
    ./../../../guilibraries/wmsgui/src/RightsManager \
    ./../../../guilibraries/wmsgui/src/ObjectEditor \
    $$UI_DIR \
    ./../../../core/wmscommons/src

LIBS += -L$$DESTDIR \
    -lwmsentities \
    -lwmsgui \
    -lwmsusermanagerlib \
    -lwmscommons \
    -lwmscore \
    -lwmsqml

QMAKE_RPATHDIR += $$DESTDIR

include(wmsdevelopmentplatform.pri)
TRANSLATIONS += wmsadmin_en.ts



QMAKE_TARGET_COMPANY = "WOGRA"
QMAKE_TARGET_PRODUCT = "WMS Development Platfrom"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
QMAKE_TARGET_DESCRIPTION = "Development Plattform for developing WMS applications"

DEFINES += \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
