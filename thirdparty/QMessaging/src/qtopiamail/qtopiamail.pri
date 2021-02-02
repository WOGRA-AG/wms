PRECOMPILED_HEADER = precompile.h

HEADERS += \
    $$PWD/precompile.h \
    ./bind_p.h \
    ./locks_p.h \
    ./longstream_p.h \
    ./longstring_p.h \
    ./mailkeyimpl_p.h \
    ./mailsortkeyimpl_p.h \
    ./support/qcopadaptor.h \
    ./support/qcopapplicationchannel.h \
    ./support/qcopchannel.h \
    ./support/qcopchannel_p.h \
    ./support/qcopchannelmonitor.h \
    ./support/qcopserver.h \
    ./qmailaccount.h \
    ./qmailaccountconfiguration.h \
    ./qmailaccountkey.h \
    ./qmailaccountkey_p.h \
    ./qmailaccountlistmodel.h \
    ./qmailaccountsortkey.h \
    ./qmailaccountsortkey_p.h \
    ./qmailaddress.h \
    ./qmailcodec.h \
    ./qmailcontentmanager.h \
    ./qmaildatacomparator.h \
    ./qmailfolder.h \
    ./qmailfolderfwd.h \
    ./qmailfolderkey.h \
    ./qmailfolderkey_p.h \
    ./qmailfoldersortkey.h \
    ./qmailfoldersortkey_p.h \
    ./support/qmailglobal.h \
    ./qmailid.h \
    ./qmailkeyargument.h \
    ./support/qmaillog.h \
    ./qmailmessage.h \
    ./qmailmessage_p.h \
    ./qmailmessagefwd.h \
    ./qmailmessagekey.h \
    ./qmailmessagekey_p.h \
    ./qmailmessagelistmodel.h \
    ./qmailmessagemodelbase.h \
    ./qmailmessageremovalrecord.h \
    ./qmailmessageserver.h \
    ./qmailmessageset.h \
    ./qmailmessageset_p.h \
    ./qmailmessagesortkey.h \
    ./qmailmessagesortkey_p.h \
    ./qmailmessagethreadedmodel.h \
    ./support/qmailnamespace.h \
    ./support/qmailpluginmanager.h \
    ./qmailserviceaction.h \
    ./qmailserviceaction_p.h \
    ./qmailsortkeyargument.h \
    ./qmailstore.h \
    ./qmailstore_p.h \
    ./qmailstoreimplementation_p.h \
    ./qmailtimestamp.h \
    ./qprivateimplementation.h \
    ./qprivateimplementationdef.h \
    ./support/qringbuffer_p.h

SOURCES += ./locks_win32.cpp \
    ./longstream.cpp \
    ./longstring.cpp \
    ./support/qcopadaptor.cpp \
    ./support/qcopapplicationchannel.cpp \
    ./support/qcopchannel.cpp \
    ./support/qcopchannelmonitor.cpp \
    ./support/qcopserver.cpp \
    ./qmailaccount.cpp \
    ./qmailaccountconfiguration.cpp \
    ./qmailaccountkey.cpp \
    ./qmailaccountlistmodel.cpp \
    ./qmailaccountsortkey.cpp \
    ./qmailaddress.cpp \
    ./qmailcodec.cpp \
    ./qmailcontentmanager.cpp \
    ./qmailfolder.cpp \
    ./qmailfolderkey.cpp \
    ./qmailfoldersortkey.cpp \
    ./qmailid.cpp \
    ./qmailinstantiations.cpp \
    ./support/qmaillog.cpp \
    ./qmailmessage.cpp \
    ./qmailmessagekey.cpp \
    ./qmailmessagelistmodel.cpp \
    ./qmailmessagemodelbase.cpp \
    ./qmailmessageremovalrecord.cpp \
    ./qmailmessageserver.cpp \
    ./qmailmessageset.cpp \
    ./qmailmessagesortkey.cpp \
    ./qmailmessagethreadedmodel.cpp \
    ./support/qmailnamespace.cpp \
    ./support/qmailpluginmanager.cpp \
    ./qmailserviceaction.cpp \
    ./qmailstore.cpp \
    ./qmailstore_p.cpp \
    ./qmailstoreimplementation_p.cpp \
    ./qmailtimestamp.cpp

TRANSLATIONS += ./libqtopiamail-ar.ts \
    ./libqtopiamail-de.ts \
    ./libqtopiamail-en_GB.ts \
    ./libqtopiamail-en_SU.ts \
    ./libqtopiamail-en_US.ts \
    ./libqtopiamail-es.ts \
    ./libqtopiamail-fr.ts \
    ./libqtopiamail-it.ts \
    ./libqtopiamail-ja.ts \
    ./libqtopiamail-ko.ts \
    ./libqtopiamail-pt_BR.ts \
    ./libqtopiamail-zh_CN.ts \
    ./libqtopiamail-zh_TW.ts

RESOURCES += qtopiamail.qrc \
    qtopiamail_icons.qrc \
    qtopiamail_qt.qrc
