

HEADERS += ../src/wmscommons.h \
           $$PWD/../src/wmsdefines.h \
           $$PWD/../src/wmsServerDefines.h \
           $$PWD/../src/CwmsSettingsStoreFactory.h \
    $$PWD/../src/CwmsArgumentParser.h \
    $$PWD/../src/CwmsUtilities.h \
    $$PWD/../src/IwmsHttpRequestHandler.h \
../src/CwsHttpServer.h \
    $$PWD/../src/CwsHttpResponse.h \
    $$PWD/../src/CwsHttpBase.h \
    ../src/CwsHttpRequest.h \
    ../src/CwmsHttpService.h \
    $$PWD/../src/CwsCookie.h \
    $$PWD/../src/CwsHttpClient.h \
    $$PWD/../src/CwsHttpServerRequest.h\
    $$PWD/../src/CwmsJson.h \
    $$PWD/../src/IwmsParser.h \
    $$PWD/../src/IwmsSerializer.h \
   ../src/CwmsSynchronizable.h \
    $$PWD/../src/CwmsTimeMeassurement.h


SOURCES += $$PWD/../src/CwmsSettingsStoreFactory.cpp \
    $$PWD/../src/CwmsArgumentParser.cpp \
    $$PWD/../src/CwmsUtilities.cpp \
   ../src/CwsHttpServer.cpp \
    $$PWD/../src/CwsHttpResponse.cpp \
    $$PWD/../src/CwsHttpBase.cpp \
    ../src/CwsHttpRequest.cpp \
    ../src/CwmsHttpService.cpp \
    $$PWD/../src/CwsCookie.cpp \
    $$PWD/../src/CwsHttpClient.cpp \
    $$PWD/../src/CwsHttpServerRequest.cpp\
    $$PWD/../src/CwmsJson.cpp \
   ../src/CwmsSynchronizable.cpp \
    $$PWD/../src/CwmsTimeMeassurement.cpp
