HEADERS += ../src/CwsService.h \
   ./resource.h \
    ../src/CwsServerCommandHandler.h \
    ../src/IwsServerCommand.h \
    ../src/CwsCommandStartServer.h \
    ../src/CwsRequest.h \
    ../src/CwsResponse.h \
    ../src/CwsCommandStopServer.h \
    ../src/CwsCommandIsRunning.h \
    ../src/CwsCommandGetOpenSessions.h \
    $$PWD/../src/CwsCommandLogin.h \
    $$PWD/../src/CwsCommandLogout.h \
    $$PWD/../src/CwsCommandGetServerSettings.h \
    $$PWD/../src/CwsCommandUpdateServerSettings.h \
    $$PWD/../src/CwsServerStrings.h \
    $$PWD/../src/CwsCommandGetAppStoreData.h \
    $$PWD/../src/CwsCommandAddAppToStore.h \
    $$PWD/../src/CwsCommandDeleteAppFromStore.h
SOURCES += ../src/main.cpp \
    ../src/CwsService.cpp \
    ../src/CwsServerCommandHandler.cpp \
    ../src/CwsCommandStartServer.cpp \
    ../src/CwsRequest.cpp \
    ../src/CwsResponse.cpp \
    ../src/CwsCommandStopServer.cpp \
    ../src/CwsCommandIsRunning.cpp \
    ../src/CwsCommandGetOpenSessions.cpp \
    $$PWD/../src/CwsCommandLogin.cpp \
    $$PWD/../src/CwsCommandLogout.cpp \
    $$PWD/../src/CwsCommandGetServerSettings.cpp \
    $$PWD/../src/CwsCommandUpdateServerSettings.cpp \
    $$PWD/../src/CwsCommandGetAppStoreData.cpp \
    $$PWD/../src/CwsCommandAddAppToStore.cpp \
    $$PWD/../src/CwsCommandDeleteAppFromStore.cpp

TRANSLATIONS += ./bmswebserver_en.ts
RESOURCES +=
