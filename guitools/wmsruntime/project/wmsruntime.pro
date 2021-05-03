TEMPLATE = app
TARGET = wmsruntime
QT += core script widgets gui qml quick sql network scripttools xml

win32{
   WMS_ARCH = mingw32
   RC_FILE = $$OUT_PWD/wmsruntime.rc
}
else:macx{
   WMS_ARCH = macx
   ICON = $$OUT_PWD/wmsruntime.icns
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

message("WMSRUNTIME DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra
#}

INCLUDEPATH += ./../../../core/wmscore/Src/DataManagement \
               ./../../../core/wmscore/Src/UserManagement \
               ./../../../core/wmscore/Src/SimpleApi \
               ./../src \
               ./../../../guilibraries/wmsqml/src \
               ./../../../core/wmsentities/src \
               ./../../../guilibraries/wmsgui/project \
               ./../../../guilibraries/wmsusermanagerlib/project/$$WMS_ARCH/ui/$$WMS_MODE \
               $$OUT_PWD/../../../guilibraries/wmsgui/project/$$WMS_ARCH/ui/$$WMS_MODE \
               ./../../../guilibraries/wmsgui/src \
               ./../../../guilibraries/wmsgui/src/misc \
               ./../../../guilibraries/wmsgui/src/RightsManager \
               ./../../../guilibraries/wmsgui/src/ObjectEditor \
               ./../../../core/wmscommons/src

LIBS +=  -L$$DESTDIR \
    -lwmsgui \
    -lwmsqml \
    -lwmsentities \
    -lwmscommons \
    -lwmscore

QMAKE_RPATHDIR += $$DESTDIR

#contains(DEFINES, WMS_LINK_STATIC) {
#LIBS +=  -L$$DESTDIR/dataaccess \
#         -lwmswebclient \
#         -lwmssqlite \
#         -lwmsodbc \
#}

include(wmsruntime.pri)

#DISTFILES += \
#    android/gradle/wrapper/gradle-wrapper.jar \
#    android/AndroidManifest.xml \
#    android/res/values/libs.xml \
#    android/build.gradle \
#    android/gradle/wrapper/gradle-wrapper.properties \
#    android/gradlew \
#    android/gradlew.bat

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/wmstools/wmsruntime/VisualStudio/android


#QMAKE_TARGET_COMPANY = "WOGRA"
#QMAKE_TARGET_PRODUCT = "WMS Runtime"
#QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2010-2015 WOGRA Consulting GmbH <info@wogra.com>"
#QMAKE_TARGET_DESCRIPTION = "Native WMS Runtime for different devices"

#DEFINES += \
#  APP_VERSION=\"\\\"$$VERSION\\\"\" \
#  APP_COMPANY=\"\\\"$$QMAKE_TARGET_COMPANY\\\"\" \
#  APP_PRODUCT=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\" \
#  APP_DESCRIPTION=\"\\\"$$QMAKE_TARGET_DESCRIPTION\\\"\" \
#  APP_COPYRIGHT=\"\\\"$$QMAKE_TARGET_COPYRIGHT\\\"\"

HEADERS += \
    ../src/CwmsNonGuiInitApplication.h

SOURCES += \
    ../src/CwmsNonGuiInitApplication.cpp
