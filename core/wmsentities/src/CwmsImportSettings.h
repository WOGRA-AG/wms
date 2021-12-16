#ifndef CWMSIMPORTSETTINGS_H
#define CWMSIMPORTSETTINGS_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QList>
#include <QString>

// Own Includes
#include "basetools.h"

// Forwards
class CdmObjectContainer;
class CdmScheme;
class CwmsImportSettingsColumn;

// Enumerations
enum EwmsImportType
{
   eWmsImportTypeCsv,
   eWmsImportTypeText
};

enum EwmsLineBreak
{
   eWmsLineBreakWindows,
   eWmsLineBreakLinux
};

enum EwmsImportMode
{
   eWmsImportModeUpdate,
   eWmsImportModeAppend,
   eWmsImportModeOverwrite
};


/* 
 * This class implements the settings for the import.
 */
class BASETOOLS_API CwmsImportSettings
{

   private:
      EwmsImportMode m_eWmsImportMode;
      EwmsImportType m_eWmsImportType;
      EwmsLineBreak  m_eWmsLineBreak;

      QString m_qstrCsvSeparator;
      QString m_qstrStringEnclosing;
      QString m_qstrFilename;
      QString m_qstrApplication;
      QString m_qstrLogin;
      QString m_qstrPassword;
     qint64 m_lContainerId;
     qint64 m_lDbId;
     qint64 m_lClassId;
      QString m_qstrDbName;
      QString m_qstrSettingsName;
      bool m_bIgnoreFirstLine;
      bool m_bIgnoreLastLine;
      QString m_qstrPreProcessorCall;
      QString m_qstrPostProcessorCall;
      QString m_qstrEncoding;
      QList<CwmsImportSettingsColumn*> m_qlColumns;
      
   public:
    CwmsImportSettings();
    virtual ~CwmsImportSettings( );
    void SetImportMode(EwmsImportMode p_eWmsImportMode);
    EwmsImportMode GetImportMode();
    void SetImportType(EwmsImportType p_eWmsIMportType);
    EwmsImportType GetImportType();
    void SetLineBreak(EwmsLineBreak p_eWmsLineBreak);
    EwmsLineBreak GetLineBreak();
    void SetCsvSeperator(QString p_qstrSeperator);
    QString GetCsvSeperator();
    void SetStringEnclosing(QString p_qstrStringEnclosing);
    QString GetStringEnclosing();
    void SetFilename(QString p_qstrFilename);
    QString GetFilename();
    void SetContainer(CdmObjectContainer* p_pContainer);
   qint64 GetContainerId();
    void AddColumn(CwmsImportSettingsColumn* p_pCwmsColumn);
    void RemoveColumn(int p_iColumn);
    void GetColumns(QList<CwmsImportSettingsColumn*>& p_rqlList);
    void MoveUp(int p_iColumn);
    void MoveDown(int p_iColumn);
    void SaveSettings(QString p_qstrName);
    void LoadSettings(QString p_qstrName, QString p_qstrConfiguration);
    void SetApplication(QString p_qstrApplication);
    QString GetApplication();
    void SetLogin(QString p_qstrLogin);
    QString GetLogin();
    void SetPassword(QString p_qstrPassword);
    QString GetPassword();
   qint64 GetDatabaseId();
    QString GetDatabaseName();
    void ClearMembers();
    bool ColumnsValidForTextImport();
    bool HasUpdateRelevantColumn();
    bool HasNonUpdateRelevantColumn();
   qint64 GetClassId();
    void LoadSettings(QString p_qstrName,qint64 p_lClassId);
    void SetSettingName(QString p_qstrName);
    QString GetSettingsName() const;
    CdmObjectContainer* GetContainer();
    void SetIgnoreFirstLine(bool p_bIgnore);
    bool GetIgnoreFirstLine();
    void SetIgnoreLastLine(bool p_bIgnore);
    bool GetIgnoreLastLine();
    void SetPreprocessorCall(QString p_qstrFunction);
    QString GetPreprocessorCall() const;
    void SetPostprocessorCall(QString p_qstrFunction);
    QString GetPostprocessorCall() const;
    void SetEncoding(QString p_qstrEncoding);
    QString GetEncoding();
};

#endif //
