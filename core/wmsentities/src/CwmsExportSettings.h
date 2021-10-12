/******************************************************************************
 ** WOGRA Middleware Tools Exportsettings Module
 **
 ** @Author Wolfgang GraÃŸof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSEXPORTSETTINGS_H
#define CWMSEXPORTSETTINGS_H



// System and QT Includes
#include <qstring.h>
#include <QList>

// own Includes
#include "basetools.h"

// forwards
class CdmQuery;

// enumerations

enum EwmsExportType
{
   eWmsExportTypeXml,
   eWmsExportTypeHtml,
   eWmsExportTypeCsv
};

class BASETOOLS_API CwmsExportSettings
{

   private:
      QList<qint64> m_qllExportList;
      EwmsExportType m_eWmsExportType;
     qint64 m_lContainerId;
      bool m_bExportHeader;
     qint64 m_lSchemeId;
     qint64 m_lCassId;
      QString m_qstrFilename;
      QString m_qstrCsvSeperator;
      QString m_qstrCsvStringEnclosing;
      QString m_qstrDatabaseName;
      QString m_qstrEncoding;
      QList<QString> m_qvlMembers;
      QString m_qstrQuery;
      QString m_qstrLogin;
      QString m_qstrPassword;
      QString m_qstrApplicationName;
      QString m_qstrSettingsName;

   public:
    CwmsExportSettings( );
    virtual ~CwmsExportSettings( );
    void SetExportType(EwmsExportType p_eWmsExportType);
    EwmsExportType GetExportType() const;
    void SetContainerId(qint64 p_lObjectListId);
   qint64 GetContainerId() const;
    void SetExportHeader(bool p_bExport);
    bool GetExportHeader() const;
    void SetSchemeId(qint64 p_lDbId);
   qint64 GetSchemeId() const;
    void SetFilename(QString p_qstrFilename);
    QString GetFilename() const;
    void SetCsvSeperator(QString p_qstrSeperator);
    QString GetCsvSeperator() const;
    void SetCsvStringEnclosing(QString p_qstrCsvStringEnclosing);
    void SetSchemeName(QString p_qstrName);
    void AddMember(QString p_qstrMember);
    const QList<QString>& GetMemberList() const;
    void SetQuery(QString p_qstrQuery);
    QString GetQuery() const;
    void SetLogin(QString p_qstrLogin);
    QString GetLogin();
    void SetPassword(QString p_qstrPassword);
    QString GetPassword() const;
    QString GetSchemeName() const;
    QString GetCsvStringEnclosing() const;
    void SetApplicationName(QString p_qstrName);
    QString GetApplicationName() const;
    void SetQuery(CdmQuery* p_pCdmQuery);
    CdmQuery* GetQueryObject();
    void Save(QString p_qstFilename);
    void Load(QString p_qstFilename, QString p_qstrConfiguration);
    void SetExportList(QList<qint64> p_qllExportList);
    QList<qint64> GetExportList();
    void SetClassId(qint64 p_lCassId);
   qint64 GetClassId();
    void Load(QString p_qstFilename,qint64 p_lClassId);
    void SetSettingName(QString p_qstrName);
    QString GetSettingsName() const;
    void ClearMembers();
    void SetEncoding(QString p_qstrName);
    QString GetEncoding() const;
};

#endif //
