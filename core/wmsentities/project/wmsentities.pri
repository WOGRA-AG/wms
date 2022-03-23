PRECOMPILED_HEADER = precompile.h

HEADERS += \
    $$PWD/../src/CwmsQueryModelExportCsv.h \
    $$PWD/../src/CwmsScriptableModel.h \
    ../src/CwmsObjectLocker.h \
    $$PWD/precompile.h \
    ../src/CwmsFormBase.h \
    ../src/CwmsFormManager.h \
    ../src/CwmsFormObject.h \
    ../src/CwmsFormObjectList.h \
    ../src/CwmsFormObjectObjectList.h \
    ../src/CwmsFormSearch.h \
    ../src/CwmsFormStandardObjectList.h \
    ../src/CwmsFormUserDefined.h \
    ../src/CwmsFormView.h \
    ../src/CwmsPluginManager.h \
    ../src/basetools.h \
    ../src/CwmsbtMailMessage.h \
    ../src/CwmsbtRightsGroup.h \
    ../src/CwmsbtSessionManager.h \
    ../src/CwmsbtSmtpAuthentification.h \
    ../src/CwmsbtSmtpClient.h \
    ../src/CwmsEscalation.h \
    ../src/CwmsSmtpConfiguration.h \
    ../src/CwmsSmtpManager.h \
    ../src/CwmsWorkflowBase.h \
    ../src/CwmsWorkflowDefinition.h \
    ../src/CwmsWorkflowManager.h \
    ../src/CwmsWorkflowObject.h \
    ../src/CwmsWorkflowStepDefinition.h \
    ../src/CwmsWorkflowStepExecution.h \
    ../src/CwmsApplication.h \
    ../src/CwmsApplicationManager.h \
    ../src/CwmsApplicationModule.h \
    ../src/CwmsExportFileWriter.h \
    ../src/CwmsExportSettings.h \
    ../src/CwmsImExportSettingsHandler.h \
    ../src/CwmsImExportConfiguration.h \
    ../src/CwmsImExportManager.h \
    ../src/CwmsImport.h \
    ../src/CwmsImportParser.h \
    ../src/CwmsImportParserCsv.h \
    ../src/CwmsImportParserText.h \
    ../src/CwmsImportSettings.h \
    ../src/CwmsImportSettingsColumn.h \
    ../src/CwmsScriptableMailer.h \
    ../src/CwmsScriptableMessage.h \
    ../src/CwmsScriptablePrinter.h \
    ../src/CwmsScriptableLogger.h \
    ../src/CwmsScriptableWorkflow.h \
    ../src/CwmsScriptableWql.h \
    ../src/CwmsPrintingTemplate.h \
    ../src/CwmsReportManager.h \
    ../src/IwmsbtSmtpConfiguration.h \
    ../src/CwmsApplicationServices.h \
    ../src/CwmsErrorCollector.h \
    ../src/CwmsErrorCollectorSession.h \
    ../src/cwmsbtplattforminformation.h \
    ../src/CwmsTranslatorConfiguration.h \
    ../src/CwmsContext.h \
    ../src/CwmsServerAddOnManager.h \
    ../src/CwmsFormLibrary.h \
    ../src/CwmsInitApplication.h \
    ../src/CwmsDataExchange.h \
    $$PWD/../src/CwmsViewManager.h \
    $$PWD/../src/CwmsView.h \
    ../src/CwmsDataExchangeConfigurator.h \
    $$PWD/../src/CwmsHttpService.h \
    $$PWD/../src/CwmsServerSchemeManager.h \
    $$PWD/../src/CwmsAppStoreData.h \
    $$PWD/../src/CwmsCloudServices.h \
    $$PWD/../src/CwmsDataAccessConfiguration.h \
    $$PWD/../src/CwmsLdapFassade.h \
    $$PWD/../src/IwmsImExportProcessor.h \
    $$PWD/../src/CwmsScriptablePlugin.h \
    $$PWD/../src/CwmsScriptableStatic.h \
    $$PWD/../src/CwmsLoggerConsole.h \
    $$PWD/../src/CwmsScriptableUtilities.h \
    $$PWD/../src/CwmsServiceManager.h \
    $$PWD/../src/IwmsRunningService.h \
    $$PWD/../src/CwmsTechnicalSchemeSwitch.h \
    $$PWD/../src/CwmsServerLogin.h \
    $$PWD/../src/IwmsWebService.h \
    $$PWD/../src/CwmsScriptableHttpClient.h \
    $$PWD/../src/CwmsScriptableGeoServices.h \
    $$PWD/../src/CwmsScriptableBase.h \
    $$PWD/../src/CwmsScriptableTimer.h \
    $$PWD/../src/CwmsScriptableFile.h \
    $$PWD/../src/CwmsScriptableSql.h \
    $$PWD/../src/CwmsCsvExport.h \
    $$PWD/../src/CwmsLogout.h \
    $$PWD/../src/CdmEnhancedQueryProxy.h \
    $$PWD/../src/CwmsServerSettings.h \
    $$PWD/../src/CwmsFormInteractiveComponent.h \
    $$PWD/../src/CdmQueryModel.h


contains(DEFINES, WMS_LDAP) {
    SOURCES += ../src/CwmsLdapUtilities.h
}

win32{
    HEADERS += ../src/CwmsLdapFunctionalitiesWindows.h
}
else:linux{
    HEADERS += ../src/CwmsLdapFunctionalitiesLinux.h
}



SOURCES += ../src/CwmsbtMailMessage.cpp \
    $$PWD/../src/CwmsQueryModelExportCsv.cpp \
    $$PWD/../src/CwmsScriptableModel.cpp \
    ../src/CwmsbtRightsGroup.cpp \
    ../src/CwmsbtSessionManager.cpp \
    ../src/CwmsbtSmtpAuthentification.cpp \
    ../src/CwmsbtSmtpClient.cpp \
    ../src/CwmsEscalation.cpp \
    ../src/CwmsFormBase.cpp \
    ../src/CwmsFormManager.cpp \
    ../src/CwmsFormObject.cpp \
    ../src/CwmsFormObjectList.cpp \
    ../src/CwmsFormObjectObjectList.cpp \
    ../src/CwmsFormSearch.cpp \
    ../src/CwmsFormStandardObjectList.cpp \
    ../src/CwmsFormUserDefined.cpp \
    ../src/CwmsFormView.cpp \
    ../src/CwmsPluginManager.cpp \
    ../src/CwmsSmtpConfiguration.cpp \
    ../src/CwmsSmtpManager.cpp \
    ../src/CwmsWorkflowBase.cpp \
    ../src/CwmsWorkflowDefinition.cpp \
    ../src/CwmsWorkflowManager.cpp \
    ../src/CwmsWorkflowObject.cpp \
    ../src/CwmsWorkflowStepDefinition.cpp \
    ../src/CwmsApplication.cpp \
    ../src/CwmsApplicationManager.cpp \
    ../src/CwmsApplicationModule.cpp \
    ../src/CwmsExportFileWriter.cpp \
    ../src/CwmsExportSettings.cpp \
    ../src/CwmsImExportSettingsHandler.cpp \
    ../src/CwmsImExportConfiguration.cpp \
    ../src/CwmsImExportManager.cpp \
    ../src/CwmsImport.cpp \
    ../src/CwmsImportParser.cpp \
    ../src/CwmsImportParserCsv.cpp \
    ../src/CwmsImportParserText.cpp \
    ../src/CwmsImportSettings.cpp \
    ../src/CwmsImportSettingsColumn.cpp \
    ../src/CwmsPrintingTemplate.cpp \
    ../src/CwmsReportManager.cpp \
    ../src/CwmsScriptableMailer.cpp \
    ../src/CwmsScriptableLogger.cpp \
    ../src/CwmsScriptableMessage.cpp \
    ../src/CwmsScriptablePrinter.cpp \
    ../src/CwmsScriptableWorkflow.cpp \
    ../src/CwmsScriptableWql.cpp \
    ../src/CwmsWorkflowStepExecution.cpp \
    ../src/CwmsApplicationServices.cpp \
    ../src/CwmsErrorCollector.cpp \
    ../src/CwmsErrorCollectorSession.cpp \
    ../src/cwmsbtplattforminformation.cpp \
    ../src/CwmsTranslatorConfiguration.cpp \
    ../src/CwmsContext.cpp \
    ../src/CwmsServerAddOnManager.cpp \
    ../src/CwmsFormLibrary.cpp \
    ../src/CwmsInitApplication.cpp \
    ../src/CwmsDataExchange.cpp \
    ../src/CwmsDataExchangeConfigurator.cpp \
    $$PWD/../src/CwmsViewManager.cpp \
    $$PWD/../src/CwmsView.cpp \
    $$PWD/../src/CwmsHttpService.cpp \
    $$PWD/../src/CwmsServerSchemeManager.cpp \
    $$PWD/../src/CwmsAppStoreData.cpp \
    $$PWD/../src/CwmsCloudServices.cpp \
    $$PWD/../src/CwmsDataAccessConfiguration.cpp \
    $$PWD/../src/CwmsLdapFassade.cpp \
    $$PWD/../src/CwmsScriptablePlugin.cpp \
    $$PWD/../src/CwmsScriptableStatic.cpp \
    $$PWD/../src/CwmsLoggerConsole.cpp \
    $$PWD/../src/CwmsScriptableUtilities.cpp \
    $$PWD/../src/CwmsServiceManager.cpp \
    $$PWD/../src/CwmsTechnicalSchemeSwitch.cpp \
    $$PWD/../src/CwmsServerLogin.cpp \
    $$PWD/../src/CwmsScriptableHttpClient.cpp \
    $$PWD/../src/CwmsScriptableGeoServices.cpp \
    $$PWD/../src/CwmsScriptableBase.cpp \
    $$PWD/../src/CwmsScriptableTimer.cpp \
    $$PWD/../src/CwmsScriptableFile.cpp \
    $$PWD/../src/CwmsScriptableSql.cpp \
    $$PWD/../src/CwmsCsvExport.cpp \
    $$PWD/../src/CwmsLogout.cpp \
    $$PWD/../src/CdmEnhancedQueryProxy.cpp \
    $$PWD/../src/CdmQueryModel.cpp \
    $$PWD/../src/CwmsServerSettings.cpp \
    $$PWD/../src/CwmsFormInteractiveComponent.cpp


win32{
    SOURCES += ../src/CwmsLdapFunctionalitiesWindows.cpp
}
else:linux{
    SOURCES += ../src/CwmsLdapFunctionalitiesLinux.cpp
}

HEADERS += \
    ../src/CwmsObjectLocker.h

SOURCES += \
    ../src/CwmsObjectLocker.cpp

contains(DEFINES, WMS_LDAP) {
    SOURCES += ../src/CwmsLdapUtilities.cpp
}
