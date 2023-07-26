// System and QT Includes
#include <QObject>


// own Includes
#include "CdmLogging.h"
#include "CsaQuery.h"
#include "CsaFactory.h"
#include "CwmsScriptableWql.h"

CwmsScriptableWql::CwmsScriptableWql()
{
}

CwmsScriptableWql::~CwmsScriptableWql()
{
}

QObject* CwmsScriptableWql::execute(QString p_qstrWql)
{
   CsaQuery* pQuery = nullptr;
   CsaFactory* pFactory = CsaFactory::getCurrentFunctionFactory();

   if (pFactory)
   {
      pQuery = dynamic_cast<CsaQuery*> (pFactory->createQuery(p_qstrWql));

      if (CHKPTR(pQuery))
      {
         addObjectForGarbageCollection(pQuery);
         pQuery->execute();
      }
   }

   return pQuery;
}
