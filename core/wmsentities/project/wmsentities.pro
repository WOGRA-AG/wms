TEMPLATE = lib
TARGET = wmsentities

!CONFIG(no_precompile_header):CONFIG += precompile_header

win32{
   WMS_ARCH = mingw32
   LIBS += -L%systemroot%\system32\wldap32.dll -lwldap32
   DEFINES += WMS_LDAP
}
else:macx{
   WMS_ARCH = macx
   DEFINES += WMS_NO_LDAP
}
else:ios{
   WMS_ARCH = ios
   DEFINES += WMS_NO_LDAP
}
else:android{
   WMS_ARCH = android
   DEFINES += WMS_NO_LDAP
}
else:linux{
   WMS_ARCH = linux
   LIBS += -L/usr/local/lib -lldap -llber
   INCLUDEPATH += /usr/local/include
   DEFINES += WMS_LDAP
}
else:unix{
   WMS_ARCH = unix
   DEFINES += WMS_NO_LDAP
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

message("WMSENTITIES DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

#    IGNORE_ERRORS += -Wno-error=unused-variable -Wno-error=unused-parameter
#    message("WMSCOMMONS Ignored Errors: "$$IGNORE_ERRORS)
#    QMAKE_CXXFLAGS += $$IGNORE_ERRORS
#}

QT += core network script widgets gui xml qml quick positioning location sql charts
DEFINES += BASETOOLS_EXPORTS WOGRA_DEBUG
INCLUDEPATH += ./../../../thirdparty/QMessaging/src/qtopiamail/support \
               ./../../../thirdparty/QMessaging/src/messageserver \
               ./../../../core/wmscore/Src/DataManagement \
               ./../../../core/wmscore/Src/UserManagement \
               ./../../../core/wmscore/Src/SimpleApi \
               ./../../../core/wmscommons/src \
               ./../src \

LIBS += -L$$DESTDIR -lmessageserver -lqtopiamail -lwmscore -lwmscommons

ios{

    QT += sql qml
    DEFINES += WMS_LINK_DATAACCESS_STATIC
    INCLUDEPATH += ./../../../dataaccess/wmsodbc/src \
                   ./../../../dataaccess/wmssqlite/src \
                   ./../../../dataaccess/wmsneo4j/src \
                   ./../../../dataaccess/wmswebclient/src
}

include(wmsentities.pri)






