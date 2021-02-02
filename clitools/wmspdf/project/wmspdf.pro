TEMPLATE = app
TARGET = wmspdf
QT += core script sql network scripttools xml widgets
DESTDIR = $$OUT_PWD/../../../../bin
CONFIG += console

win32{
   WMS_ARCH = mingw32
}
else:macx{
   WMS_ARCH = macx
}
else:ios{
   WMS_ARCH = ios
   DEFINES += WMS_LINK_STATIC
}
else:android{
   WMS_ARCH = android
   DEFINES += WMS_NO_LDAP
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

message("WMSPDF DESTDIR: "$$DESTDIR)

INCLUDEPATH += ./../../wmsusermanager/VisualStudio/GeneratedFiles \
    ./../../../../bms/ThirdParty/NCReport/source/src/designer \
    ./../../../../bms/ThirdParty/NCReport/source/src/ncreport \
    ./../../../wmsmanager/Src/DataManagement \
    ./../../../wmsmanager/Src/UserManagement \
./../../../wmsmanager/Src/SimpleApi \
    ./../../../wmsodbc/src \
    ./../../../wmssqlite/src \
    ./../src \
    ./../../../wmscom/Src \
    ./../../wmsbasesettings/src \
    ./../../WMSlogin/VisualStudio \
    ./../../wmsusermanager/src \
    ./../../wmsqml/src \
    ./../../basetools/src \
    ./../../WMSgui/VisualStudio/GeneratedFiles \
    ./../../WMSgui/VisualStudio \
    ./../../WMSgui/src \
    ./../../WMSgui/src/misc \
    ./../../WMSgui/src/RightsManager \
    ./../../WMSgui/src/ObjectEditor \
    ./../../wmsexportdll/VisualStudio \
    ./../../wmsexportdll/src \
    ./debug \
    . \
    ./GeneratedFiles

LIBS +=  -L$$DESTDIR -L$$DESTDIR/dataaccess \
    -lwmsbasetools \
    -lwmsusermanagerdll \
    -lwmscommons \
    -lwmsmanager \
    -lantlr3c \
    -lmessageserver \
    -lqtopiamail

contains(DEFINES, WMS_LINK_STATIC) {
LIBS +=  -L$$DESTDIR/dataaccess \
         -lwmswebclient \
         -lwmssqlite \
         -lwmsodbc \
}

include(wmspdf.pri)


QMAKE_TARGET_COMPANY = "WOGRA"
QMAKE_TARGET_PRODUCT = "WMS PDF"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
QMAKE_TARGET_DESCRIPTION = "Generates PDF documents over the printing plugin."

DEFINES += \
  APP_VERSION=\"\\\"$$VERSION\\\"\" \
  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"
