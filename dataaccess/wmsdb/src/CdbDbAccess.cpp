
// System and QT Includes
#include <qsqlquery.h>
#include <qvariant.h>
#include <QList>

// WMS Includes
#include "CdmLogging.h"
#include "CdmScheme.h"

// own Includes
#include "CdbCommandExistScheme.h"
#include "CdbCommandCleanupDB.h"
#include "CdbCommandCreateScheme.h"
#include "CdbCommandDeleteScheme.h"
#include "CdbCommandFindScheme.h"
#include "CdbCommandGetSchemeList.h"
#include "CdbCommandUpdateScheme.h"
#include "CdbCommandAddSchemeLanguage.h"
#include "CdbCommandDeleteSchemeLanguage.h"
#include "CdbDataAccess.h"
#include "CdbDbAccess.h"


CdbSchemeAccess::CdbSchemeAccess(CdbDataAccess* p_pCdbDataAccess)
   : m_rpCdbDataAccess(p_pCdbDataAccess)
{
   // nothing todo
}

CdbSchemeAccess::~CdbSchemeAccess(  )
{
   // nothing todo
}

qint64 CdbSchemeAccess::CreateScheme(QString p_qstrKeyname, CdmScheme*& p_rpCdmDatabase)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandCreateScheme command(p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();
   p_rpCdmDatabase = command.GetResult();
   return lRet;
}

qint64 CdbSchemeAccess::DeleteDb(QString p_qstrKeyname)
{
    CdbCommandDeleteScheme command(p_qstrKeyname, m_rpCdbDataAccess);
    return command.Run();
}

bool CdbSchemeAccess::CleanupDb() 
{
    CdbCommandCleanupDB command(m_rpCdbDataAccess);

    if (SUCCESSFULL(command.Run()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

qint64 CdbSchemeAccess::ExistDb(QString p_qstrKeyname, bool& p_bRet)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandExistScheme command(p_qstrKeyname, m_rpCdbDataAccess);
  qint64 lId = command.Run();

   if (lId > 0)
   {
      p_bRet = true;
      lRet = EC(eDmOk);
   }
   else if (lId == 0)
   {
      p_bRet = false;
      lRet = EC(eDmFalse);
   }
   else
   {
      lRet = lId;
      p_bRet = false;
   }
  
   return lRet;
}

qint64 CdbSchemeAccess::FindScheme(QString p_qstrKeyname, CdmScheme*& p_pCdmDatabaseManager)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandFindScheme command(p_qstrKeyname, m_rpCdbDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

qint64 CdbSchemeAccess::FindScheme(qint64 p_lId, CdmScheme*& p_pCdmDatabaseManager)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandFindScheme command(p_lId, m_rpCdbDataAccess);
   lRet = command.Run();
   p_pCdmDatabaseManager = command.GetResult();
   return lRet;
}

qint64 CdbSchemeAccess::GetSchemeList(QList<QString>& p_rqvlDatabases)
{
  qint64 lRet = CdmLogging::eDmUnknownDbAccessError;
   CdbCommandGetSchemeList command(m_rpCdbDataAccess);
   lRet = command.Run();
   p_rqvlDatabases.clear();

   if (SUCCESSFULL(lRet))
   {
     p_rqvlDatabases = command.GetSchemes();
   }

   return lRet;
}

qint64 CdbSchemeAccess::UpdateScheme(CdmScheme* p_pCdmDatabase)
{
   CdbCommandUpdateScheme command(p_pCdmDatabase, m_rpCdbDataAccess);
   return command.Run();
}


int CdbSchemeAccess::DeleteLanguage(qint64 p_lDatabaseId, int p_iLanguageId)
{
    CdbCommandDeleteSchemeLanguage command(p_lDatabaseId, p_iLanguageId, m_rpCdbDataAccess);
    return command.Run();
}

int CdbSchemeAccess::AddLanguage(qint64 p_lDatabaseId, QString p_qstrLanguage)
{
    CdbCommandAddSchemeLanguage command(p_lDatabaseId, p_qstrLanguage, m_rpCdbDataAccess);
    return command.Run();
}


