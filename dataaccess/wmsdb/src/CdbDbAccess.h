#ifndef CODBCDBACCESS_H
#define CODBCDBACCESS_H

// System and QT Includes
#include <QList>

// own Includes
#include "CdbDataAccess.h"

// forwards
class CdbDataAccess;
class CdmScheme;

/*
 * This class implements the dataaccess to
 * virtual databases.
 */
class WMSDB_API CdbSchemeAccess
{

protected:
    /*
       * The dataaccess
       */
    CdbDataAccess* m_rpCdbDataAccess;

public:
    CdbSchemeAccess(  CdbDataAccess* p_pCdbDataAccess );
    virtual ~CdbSchemeAccess(  );
    virtual qint64 CreateScheme(  QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase );
    virtual qint64 DeleteDb(  QString p_qstrKeyname );
    qint64 ExistDb(  QString p_qstrKeyname, bool& p_bRet );
    qint64 FindScheme(  QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager );
    qint64 GetSchemeList(  QList<QString>& p_rqvlDatabases );
    qint64 UpdateScheme(CdmScheme* p_pCdmDatabase);
    virtual int AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage);
    int DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId);
    bool CleanupDb();
    qint64 FindScheme(qint64 p_lId, CdmScheme *&p_pCdmDatabaseManager);
};


#endif //
