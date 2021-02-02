TEMPLATE = subdirs

message($$CONFIG)

SUBDIRS += \
    # xlsx \
    qtservice \
    qtopiamail \
    qmfutil \
    messageserver \
    antlr \
    antlr4 \
    qmqtt \
    wmscommons \
    wmscore \
    wmsentities \
    wmsdb \
    # wmssqlite \
    wmsftl \
    wmsneo4j \
    # wmses \
    # wmsneo4jtest \
    wmswebclient \
    wmsusermanagerlib \
    wmsqml \
    wmsgui \
    wmsrequestmanager \
    wmsservercommands \
    wmssimplerestapi \
    wmsapplicationserver \
    wmsusermanager \
    wmsdevelopmentplatform \
    wmsruntime \
    wmsservercontroller \
    wmsdatainterface \
    wmswql \
    # wmspdf \
    wmsdeploy \
    wmsexec \
    wmsplugin \
    wmsuser \
    wmsmqtt \
    wmsclienttest \
    wmstest

# xlsx.file = thirdparty/qtxlsx/src/xlsx/xlsx.pro
qtservice.file = thirdparty/qtservice/buildlib/buildlib.pro
qtopiamail.file = thirdparty/QMessaging/src/qtopiamail/qtopiamail.pro
qmfutil.file = thirdparty/QMessaging/src/qmfutil/qmfutil.pro
messageserver.file = thirdparty/QMessaging/src/messageserver/messageserver.pro
antlr.file = thirdparty/antlr/libantlr3c-3.4/antlr.pro
antlr4.file = thirdparty/antlr/antlr4-cpp-runtime-4.7.2-source/antlr4.pro
qmqtt.file = thirdparty/qmqtt/src/qmqtt.pro
wmscommons.file = core/wmscommons/project/wmscommons.pro
wmscore.file = core/wmscore/project/wmscore.pro
wmsentities.file = core/wmsentities/project/wmsentities.pro
wmsdb.file = dataaccess/wmsdb/project/wmsdb.pro
wmssqlite.file = dataaccess/wmssqlite/project/wmssqlite.pro
wmsftl.file = dataaccess/wmsftl/project/wmsftl.pro
wmsneo4j.file = dataaccess/wmsneo4j/project/wmsneo4j.pro
wmses.file = plugins/wmseventstore/project/wmses.pro
# wmsneo4jtest.file = dataaccess/wmsneo4jtest/project/wmsneo4jtest.pro
wmswebclient.file = dataaccess/wmswebclient/project/wmswebclient.pro
wmsusermanagerlib.file = guilibraries/wmsusermanagerlib/project/wmsusermanagerlib.pro
wmsqml.file = guilibraries/wmsqml/project/wmsqml.pro
wmsgui.file = guilibraries/wmsgui/project/wmsgui.pro
wmsrequestmanager.file = services/wmsrequestmanager/project/wmsrequestmanager.pro
wmsservercommands.file = services/wmsservercommands/project/wmsservercommands.pro
wmssimplerestapi.file = services/wmssimplerestapi/project/wmssimplerestapi.pro
wmsapplicationserver.file = services/wmsapplicationserver/project/wmsapplicationserver.pro
wmsserverd.file = services/wmsserverdaemon/project/wmsserverd.pro
wmsusermanager.file = guitools/wmsusermanager/project/wmsusermanager.pro
wmsdevelopmentplatform.file = guitools/wmsdevelopmentplatform/project/wmsdevelopmentplatform.pro
wmsruntime.file = guitools/wmsruntime/project/wmsruntime.pro
wmsservercontroller.file = guitools/wmsservercontroller/project/wmsservercontroller.pro
wmsdatainterface.file = clitools/wmsdatainterface/project/wmsdatainterface.pro
wmswql.file = clitools/wmswql/project/wmswql.pro
# wmspdf.file = clitools/wmspdf/project/wmspdf.pro
wmsdeploy.file = clitools/wmsdeploy/project/wmsdeploy.pro
wmsexec.file = clitools/wmsexec/project/wmsexec.pro
wmsplugin.file = clitools/wmsplugin/project/wmsplugin.pro
wmsuser.file = clitools/wmsuser/project/wmsuser.pro
wmsmqtt.file = plugins/wmsmqtt/project/wmsmqtt.pro
wmsclienttest.file = services/wmsclienttests/project/wmsclienttest.pro
wmstest.file = test/project/wmstest.pro

qmfutil.depends = qtopiamail
messageserver.depends = qtopiamail qmfutil
wmscore.depends = wmscommons antlr4
wmsclienttest.depends = wmscommons

wmsentities.depends = wmscommons wmscore messageserver qmfutil qtopiamail

wmsdb.depends = wmscommons wmscore wmsentities
#wmssqlite.depends = wmscommons wmscore wmsentities
wmsftl.depends = wmscommons wmscore wmsentities
wmsneo4j.depends = wmscommons wmscore wmsentities
wmses.depends = wmscommons wmscore wmsentities
wmswebclient.depends = wmscommons wmscore
wmsusermanagerlib.depends = wmscommons wmscore
wmsqml.depends = wmscommons wmscore wmsentities
wmsrequestmanager.depends = wmscommons wmscore wmsentities
wmsdatainterface.depends = wmscommons wmscore wmsentities
wmswql.depends = wmscommons wmscore wmsentities
wmsdeploy.depends = wmscommons wmscore wmsentities
wmsexec.depends = wmscommons wmscore wmsentities
wmsplugin.depends = wmscommons wmscore wmsentities
wmsuser.depends = wmscommons wmscore wmsentities

wmsgui.depends = wmscommons wmscore wmsentities wmsusermanagerlib wmsqml
wmsservercommands.depends = wmscommons wmscore wmsentities wmsrequestmanager
wmssimplerestapi.depends = wmscommons wmscore wmsentities wmsrequestmanager
wmsapplicationserver.depends = wmscommons wmscore wmsentities qtservice wmsrequestmanager

wmsusermanager.depends = wmscommons wmscore wmsusermanagerlib wmsgui
wmsdevelopmentplatform.depends = wmscommons wmscore wmsentities wmsusermanagerlib wmsqml wmsgui
wmsruntime.depends = wmscommons wmscore wmsentities wmsqml wmsgui
wmstest.depends = wmscommons wmscore wmsentities wmsrequestmanager
wmsservercontroller.depends = wmscommons wmscore wmsentities qtservice wmsgui
wmsmqtt.depends = wmscommons wmscore wmsentities wmsrequestmanager wmsgui qmqtt

qtservicetarget.target = qtservice
qtservicetarget.depends = sub-thirdparty-qtservice-buildlib-buildlib-pro
QMAKE_EXTRA_TARGETS += qtservicetarget

qtopiamailtarget.target = qtopiamail
qtopiamailtarget.depends = sub-thirdparty-QMessaging-src-qtopiamail-qtopiamail-pro
QMAKE_EXTRA_TARGETS += qtopiamailtarget

qmfutiltarget.target = qmfutil
qmfutiltarget.depends = sub-thirdparty-QMessaging-src-qmfutil-qmfutil-pro
QMAKE_EXTRA_TARGETS += qmfutiltarget

messageservertarget.target = messageserver
messageservertarget.depends = sub-thirdparty-QMessaging-src-messageserver-messageserver-pro
QMAKE_EXTRA_TARGETS += messageservertarget

antlrtarget.target = antlr
antlrtarget.depends = sub-thirdparty-antlr-libantlr3c-3-4-antlr-pro
QMAKE_EXTRA_TARGETS += antlrtarget

antlr4target.target = antlr4
antlr4target.depends = sub-thirdparty-antlr-antlr4-cpp-runtime-4.7.2-source-antlr-pro
QMAKE_EXTRA_TARGETS += antlr4target

qmqtttarget.target = qmqtt
qmqtttarget.depends = sub-thirdparty-qmqtt-src-qmqtt-pro
QMAKE_EXTRA_TARGETS += qmqtttarget

wmscommonstarget.target = wmscommons
wmscommonstarget.depends = sub-core-wmscommons-project-wmscommons-pro
QMAKE_EXTRA_TARGETS += wmscommonstarget

wmscoretarget.target = wmscore
wmscoretarget.depends = sub-core-wmscore-project-wmscore-pro
QMAKE_EXTRA_TARGETS += wmscoretarget

wmsentitiestarget.target = wmsentities
wmsentitiestarget.depends = sub-core-wmsentities-project-wmsentities-pro
QMAKE_EXTRA_TARGETS += wmsentitiestarget

wmsdbtarget.target = wmsdb
wmsdbtarget.depends = sub-dataaccess-wmsdb-project-wmsdb-pro
QMAKE_EXTRA_TARGETS += wmsdbtarget

#wmssqlitetarget.target = wmssqlite
#wmssqlitetarget.depends = sub-dataaccess-wmssqlite-project-wmssqlite-pro
#QMAKE_EXTRA_TARGETS += wmssqlitetarget

wmsftltarget.target = wmsftl
wmsftltarget.depends = sub-dataaccess-wmsftl-project-wmsftl-pro
QMAKE_EXTRA_TARGETS += wmsftltarget

wmsneo4jtarget.target = wmsneo4j
wmsneo4jtarget.depends = sub-dataaccess-wmsneo4j-project-wmsneo4j-pro
QMAKE_EXTRA_TARGETS += wmsneo4jtarget

wmsestarget.target = wmses
wmsestarget.depends = sub-plugins-wmseventstore-project-wmses-pro
QMAKE_EXTRA_TARGETS += wmsestarget

wmswebclienttarget.target = wmswebclient
wmswebclienttarget.depends = sub-dataaccess-wmswebclient-project-wmswebclient-pro
QMAKE_EXTRA_TARGETS += wmswebclienttarget

wmsusermanagerlibtarget.target = wmsusermanagerlib
wmsusermanagerlibtarget.depends = sub-guilibraries-wmsusermanagerlib-project-wmsusermanagerlib-pro
QMAKE_EXTRA_TARGETS += wmsusermanagerlibtarget

wmsqmltarget.target = wmsqml
wmsqmltarget.depends = sub-guilibraries-wmsqml-project-wmsqml-pro
QMAKE_EXTRA_TARGETS += wmsqmltarget

wmsguitarget.target = wmsgui
wmsguitarget.depends = sub-guilibraries-wmsgui-project-wmsgui-pro
QMAKE_EXTRA_TARGETS += wmsguitarget

wmsrequestmanagertarget.target = wmsrequestmanager
wmsrequestmanagertarget.depends = sub-services-wmsrequestmanager-project-wmsrequestmanager-pro
QMAKE_EXTRA_TARGETS += wmsrequestmanagertarget

wmsservercommandstarget.target = wmsservercommands
wmsservercommandstarget.depends = sub-services-wmsservercommands-project-wmsservercommands-pro
QMAKE_EXTRA_TARGETS += wmsservercommandstarget

wmssimplerestapitarget.target = wmssimplerestapi
wmssimplerestapitarget.depends = sub-services-wmssimplerestapi-project-wmssimplerestapi-pro
QMAKE_EXTRA_TARGETS += wmssimplerestapitarget

wmsapplicationservertarget.target = wmsapplicationserver
wmsapplicationservertarget.depends = sub-services-wmsapplicationserver-project-wmsapplicationserver-pro
QMAKE_EXTRA_TARGETS += wmsapplicationservertarget

wmsusermanagertarget.target = wmsusermanager
wmsusermanagertarget.depends = sub-guitools-wmsusermanager-project-wmsusermanager-pro
QMAKE_EXTRA_TARGETS += wmsusermanagertarget

wmsdevelopmentplatformtarget.target = wmsdevelopmentplatform
wmsdevelopmentplatformtarget.depends = sub-guitools-wmsdevelopmentplatform-project-wmsdevelopmentplatform-pro
QMAKE_EXTRA_TARGETS += wmsdevelopmentplatformtarget

wmsruntimetarget.target = wmsruntime
wmsruntimetarget.depends = sub-guitools-wmsruntime-project-wmsruntime-pro
QMAKE_EXTRA_TARGETS += wmsruntimetarget

wmsservercontrollertarget.target = wmsservercontroller
wmsservercontrollertarget.depends = sub-guitools-wmsservercontroller-project-wmsservercontroller-pro
QMAKE_EXTRA_TARGETS += wmsservercontrollertarget

wmsdatainterfacetarget.target = wmsdatainterface
wmsdatainterfacetarget.depends = sub-clitools-wmsdatainterface-project-wmsdatainterface-pro
QMAKE_EXTRA_TARGETS += wmsdatainterfacetarget

wmswqltarget.target = wmswql
wmswqltarget.depends = sub-clitools-wmswql-project-wmswql-pro
QMAKE_EXTRA_TARGETS += wmswqltarget

wmsdeploytarget.target = wmsdeploy
wmsdeploytarget.depends = sub-clitools-wmsdeploy-project-wmsdeploy-pro
QMAKE_EXTRA_TARGETS += wmsdeploytarget

wmsexectarget.target = wmsexec
wmsexectarget.depends = sub-clitools-wmsexec-project-wmsexec-pro
QMAKE_EXTRA_TARGETS += wmsexectarget

wmsplugintarget.target = wmsplugin
wmsplugintarget.depends = sub-clitools-wmsplugin-project-wmsplugin-pro
QMAKE_EXTRA_TARGETS += wmsplugintarget

wmsusertarget.target = wmsuser
wmsusertarget.depends = sub-clitools-wmsuser-project-wmsuser-pro
QMAKE_EXTRA_TARGETS += wmsusertarget

wmsmqtttarget.target = wmsmqtt
wmsmqtttarget.depends = sub-plugins-wmsmqtt-project-wmsmqtt-pro
QMAKE_EXTRA_TARGETS += wmsmqtttarget

wmsclienttesttarget.target = wmsclienttest
wmsclienttesttarget.depends = sub-services-wmsclienttests-project-wmsclienttest-pro
QMAKE_EXTRA_TARGETS += wmsclienttesttarget

wmstesttarget.target = wmstest
wmstesttarget.depends = sub-test-project-wmstest-pro
QMAKE_EXTRA_TARGETS += wmstesttarget
