/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMDATAMANAGEMENT_H
#define CDMDATAMANAGEMENT_H

// System and QT Includes
#include <QString>
#include <QTextStream>
#include <QVariant>
#include <QThreadStorage>
#include <QDateTime>

// own Includes
#include "CdmLocatedElement.h"
#include "CdmRights.h"
#include "datamanager.h"


// forwards
class QDomElement;
class CumUserManager;
class CdmModelElement;
class QString;
class IdmDataAccess;
class IdmPluginManager;
class CdmContainerManager;
class CdmClassManager;
class CdmJournalItem;
class CdmLogging;
class CdmDataProvider;


/*
 * This class is the implementation of
 * a virtual objectoriented database.
 */
class WMSMANAGER_API CdmScheme : public CdmLocatedElement
{
    Q_OBJECT

private:
    CdmDataProvider* m_rpCdmManager;
    QThreadStorage <CdmContainerManager*> m_pCdmContainerManager;
    QAtomicInteger<long> m_lId;
    QString m_qstrSchemeName;
    QAtomicInteger<int> m_iVersion;
    CdmRights m_cCdmRights;
    QMap<int, QString> m_qmLanguages;
    QString m_qstrCurrentLanguage;
    CumUserManager* m_pCumSchemeUserManager;
    QAtomicInteger<bool> m_bDeploymentMode;
    QList<QString> m_qlDeploymentRelevantEelements; // contains the uri.
    QList<long> m_qlDeployedContainerIds;

    friend class IdmDataAccess;
    friend class CdmDataAccessHelper;

public:
    CdmScheme(long p_lId, QString p_qstrDatabaseName, int p_iVersion);
    virtual ~CdmScheme();
    IdmDataAccess* GetDataAccess(  );
    void SetVersion(int p_iVersion);
    QVariant GetVariant() const;
    CdmScheme(QVariantMap& p_rqvHash);
    void SetCurrentLanguage(QString& p_qstrName);
    QMap<int, QString> GetLanguageMap();
    void AddLanguage(QString& p_qstrName);
    void AddLanguage(int p_iId, QString& p_qstrName);
    long Commit();
    QString GetLanguage(int p_iId) const;
    void RemoveLanguage(int p_iId);
    QVariant GetVariantCompleteDatabase() const;
    bool GenerateDeploymentFile(QString &p_qstrFilename);
    bool Deploy(QString &p_qstrFilename);
    bool IsInDeploymentMode() const;
    void AddDeploymentRelevantElement(QString &p_qstrUri);
    void AddDeployedContainerId(long p_Id);
    bool IsDeployedContainerId(long p_Id);
    bool DeployJsonContent(QString &p_rqstrJson);
    bool IsScheme() const;
    QString GetUri() const;
    QString GetUriInternal() const;
    CumUserManager *GetSchemeUserManager() const;

    void ResetContainerManager();
public slots:
    long GetId() const;
    QString GetSchemeName() const;
    CdmClassManager* GetClassManager( );
    CdmContainerManager* GetContainerManager( ) const;
    long GetUserId() const;
    int GetVersion( ) const;
    CdmRights& GetRights( );
    bool CheckReadAccess( ) const;
    bool CheckWriteAccess( ) const;
    QString GetCurrentLanguageName( ) const;
    int GetLanguageId( QString& p_qstrLanguage) const;
    void GetChanges(QDate &p_qdFrom, QDate &p_qdTo, QList<CdmJournalItem*>& p_rqllChanges);
    void GetChanges( QList<CdmJournalItem*>& p_rqllChanges);
    CdmLocatedElement* GetBaseObject(QString &p_qstrType,
                                     QString &p_qstrMajorKeyname,
                                     QString &p_qstrMinorKeyname,
                                     QString p_qstrValueKeyname);

};
#endif // //CDMDATAMANAGEMENT_H
