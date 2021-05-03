TEMPLATE = lib
TARGET = wmscore

!CONFIG(no_precompile_header):CONFIG += precompile_header

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

message("WMSCORE DESTDIR: "$$DESTDIR)

#CONFIG(gcc, gcc|clang) {
#    QMAKE_CXXFLAGS += -Werror -Wall -Wextra

#    ## used to ignore warnings in generated files WmsQL1Lexer.cpp and WmsQL1Parser.cpp
#    IGNORE_ERRORS = -Wno-unused-parameter -Wno-deprecated-declarations
#    message("WMSCORE Ignored Errors: "$$IGNORE_ERRORS)
#    QMAKE_CXXFLAGS += $(and $(filter %/WmsQL1Lexer.o %/WmsQL1Parser.o, $@), $$IGNORE_ERRORS)
#}

# script, scripttools widgets and qml is needed for scriptengine todo: extract from core
QT += core xml script scripttools widgets qml
DEFINES += WMSMANAGER_EXPORTS _ALLOW_KEYWORD_MACROS NOMINMAX
INCLUDEPATH += ./../Src/DataManagement \
               ./../Src/UserManagement \
               ./../Src/SimpleApi \
               ./../../../core/wmscommons/src \
               ./../../../thirdparty/antlr/antlr4-cpp-runtime-4.7.2-source/src

## Make antlr headers system headers to disable warnings
#QMAKE_CXXFLAGS += -isystem ./../../../thirdparty/antlr/antlr4-cpp-runtime-4.7.2-source/src

include(wmscore.pri)

LIBS += -L$$DESTDIR -lwmscommons -lantlr4runtime

HEADERS += \
    ../Src/DataManagement/wmsmacros.h
