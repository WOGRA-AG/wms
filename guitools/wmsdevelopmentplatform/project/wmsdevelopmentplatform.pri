
HEADERS += ../src/CwmsClassDataFiller.h \
    $$PWD/../src/CwmsPlatformServices.h \
    ../src/CwmsMiscDataFiller.h \
    ../src/CwmsObjectContainerDataFiller.h \
    ../src/CwmsAddMemberIf.h \
    ../src/CwmsAddNewClassIf.h \
    ../src/CwmsAdminMainWindowIf.h \
    ../src/CwmsClassEditorIf.h \
    ../src/CwmsClassValidationEditor.h \
    ../src/CwmsCodeGeneratorBase.h \
    ../src/CwmsCodeGeneratorC.h \
    ../src/CwmsCodeGeneratorCBase.h \
    ../src/CwmsCodeGeneratorCBl.h \
    ../src/CwmsCodeGeneratorCTemp.h \
    ../src/CwmsCodeGeneratorCWebIf.h \
    ../src/CwmsCodeGeneratorJ.h \
    ../src/CwmsCodeGeneratorTestC.h \
    ../src/CwmsFunctionEditor.h \
    ../src/CwmsGenerateCodeEditor.h \
    ../src/CwmsGenerateDatabaseCode.h \
    ../src/CwmsGenerateWmsDefinitionCode.h \
    ../src/CwmsGroupEditorDlg.h \
    ../src/CwmsLanguagesEditorDlg.h \
    ../src/CwmsMemberSequenceEditor.h \
    ../src/CwmsTranslationEditorDlg.h \
    ../src/CwmsUniversalRightsManager.h \
    ../src/IwmsCodeGenerator.h \
    ../src/CwmsCreateobjectContainerDlg.h \
    ../src/CwmsSymbolSearch.h \
../src/CwmsDataSearchDlg.h \
    $$PWD/../src/CwmsScriptingEnvironment.h
SOURCES += ../src/CwmsClassDataFiller.cpp \
    $$PWD/../src/CwmsPlatformServices.cpp \
    ../src/CwmsAddMemberIf.cpp \
    ../src/CwmsAddNewClassIf.cpp \
    ../src/CwmsAdminMainWindowIf.cpp \
    ../src/CwmsClassEditorIf.cpp \
    ../src/CwmsClassValidationEditor.cpp \
    ../src/CwmsCodeGeneratorBase.cpp \
    ../src/CwmsCodeGeneratorC.cpp \
    ../src/CwmsCodeGeneratorCBase.cpp \
    ../src/CwmsCodeGeneratorCBl.cpp \
    ../src/CwmsCodeGeneratorCTemp.cpp \
    ../src/CwmsCodeGeneratorCWebIf.cpp \
    ../src/CwmsCodeGeneratorJ.cpp \
    ../src/CwmsCodeGeneratorTestC.cpp \
    ../src/CwmsCreateobjectContainerDlg.cpp \
    ../src/CwmsFunctionEditor.cpp \
    ../src/CwmsGenerateCodeEditor.cpp \
    ../src/CwmsGenerateDatabaseCode.cpp \
    ../src/CwmsGenerateWmsDefinitionCode.cpp \
    ../src/CwmsGroupEditorDlg.cpp \
    ../src/CwmsLanguagesEditorDlg.cpp \
    ../src/CwmsMemberSequenceEditor.cpp \
    ../src/CwmsMiscDataFiller.cpp \
    ../src/CwmsObjectContainerDataFiller.cpp \
    ../src/CwmsTranslationEditorDlg.cpp \
    ../src/CwmsUniversalRightsManager.cpp \
    ../src/main.cpp \
    ../src/CwmsSymbolSearch.cpp \
   ../src/CwmsDataSearchDlg.cpp \
    $$PWD/../src/CwmsScriptingEnvironment.cpp
FORMS += ../src/cwmsaddclassmemberdlg.ui \
    ../src/cwmsaddnewclass.ui \
    ../src/CwmsAdminMainWindow.ui \
    ../src/CwmsClassEditor.ui \
    ../src/CwmsClassValidationEditor.ui \
    ../src/cwmscreatobjectlistdlg.ui \
    ../src/CwmsFunctionEditor.ui \
    ../src/CwmsGenerateCodeEditor.ui \
    ../src/CwmsGroupEditorDlg.ui \
    ../src/CwmsLanguagesEditorDlg.ui \
    ../src/CwmsMemberSequenceEditor.ui \
    ../src/CwmsTranslationEditorDlg.ui \
../src/CwmsDataSearchDlg.ui \
    $$PWD/../src/CwmsScriptingEnvironment.ui


HEADERS += \
    ../src/CwmsInitAdmin.h

SOURCES += \
    ../src/CwmsInitAdmin.cpp

TRANSLATIONS += ./wmsdevelopmentplatform_en.ts

RESOURCES += ../resources/emresources.qrc

