/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CbgMandatorSelectionIf.cpp
 ** Started Implementation: 14.7.2006
 ** Description:
 ** Implements the mandatorselectiondialog
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 


// System and QT Includes
#include <QApplication>
#include <QList>
#include <QQuickWindow>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmRights.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "IdmDataAccess.h"

// WMSQML
#include "CwqQmlObjectViewer.h"

// own Includes
#include "CwmsInitApplication.h"
#include "CwmsQmlDatabaseSelection.h"


/** +-=---------------------------------------------------------Di 4. Sep 14:26:47 2012-----------*
 * @method  CwmsDatabaseSelection::CwmsDatabaseSelection     // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment The constructor of the chosse mandatorif class it initializes the members.            *
 *----------------last changed: --------------------------------Di 4. Sep 14:26:47 2012-----------*/
CwmsQmlDatabaseSelection::CwmsQmlDatabaseSelection(CwmsInitApplication* p_pInit)
: m_pInit(p_pInit),
  m_bNeedToShow(true)
{
}

/** +-=---------------------------------------------------------Di 4. Sep 14:26:57 2012-----------*
 * @method  CwmsDatabaseSelection::~CwmsDatabaseSelection    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CfbChooseMandatorIf                                           *
 *----------------last changed: --------------------------------Di 4. Sep 14:26:57 2012-----------*/
CwmsQmlDatabaseSelection::~CwmsQmlDatabaseSelection()
{
   // nothing to do here :-) 
}

QStringList CwmsQmlDatabaseSelection::getDatabaseList()
{
    QStringList qstrlDatabases;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if(CHKPTR(pCdmManager))
    {
       QList<QString> qllDatabases;
       pCdmManager->GetSchemeList(qllDatabases);

       QList<QString>::iterator qvlIt = qllDatabases.begin();
       QList<QString>::iterator qvlItEnd = qllDatabases.end();

       for (; qvlIt != qvlItEnd; ++ qvlIt)
       {
          QString qstrDatabase = *qvlIt;

          if (!qstrDatabase.isEmpty())
          {
             qstrlDatabases.append(qstrDatabase);
          }
       }
    }

    return qstrlDatabases;
}

void CwmsQmlDatabaseSelection::cancel()
{
    m_pInit->StateFinished(false);
}

void CwmsQmlDatabaseSelection::ok()
{
    m_pInit->StateFinished(true);
}

/** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012-----------*
 * @method  CwmsDatabaseSelection::LoadSelection              // private                           *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrDatabase                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 15:17:02 2012-----------*/
bool CwmsQmlDatabaseSelection::loadSelection(QString p_qstrDatabase)
{
    bool bRet = false;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = nullptr;
      if(pCdmManager->LoadScheme(p_qstrDatabase) > 0)
      {
         pCdmDatabase = pCdmManager->FindSchemeByName(p_qstrDatabase);

         if (CHKPTR(pCdmDatabase))
         {
            pCdmManager->SetCurrentScheme(pCdmDatabase);
            bRet = true;
         }
         else
         {
            CdmMessageManager::critical(tr("Fehler bei der Datenbankauswahl"), 
                                  tr("Datenbank konnten nicht geladen werden!!!"));
         }
      }
   }

   return bRet;
}
