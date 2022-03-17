/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsScriptableWql.cpp
 ** Started Implementation: 2012/11/13
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QObject>


// own Includes
#include "CdmLogging.h"
#include "CsaQuery.h"
#include "CsaFactory.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"
#include "CdmQueryEnhanced.h"
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
