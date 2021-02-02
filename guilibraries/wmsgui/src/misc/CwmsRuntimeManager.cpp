/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsRuntimeManager.cpp
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 ** implements the manager for the runtime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QApplication>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"

// own Includes
#include "CwmsQmlApplicationSelection.h"
#include "CwmsApplication.h"
#include "CwmsObjectSelectionIf.h"
#include "CwmsApplicationModule.h"
#include "CwmsRuntime.h"
#include "CwmsRuntimeManager.h"


/** +-=---------------------------------------------------------Do 30. Aug 14:06:09 2012----------*
 * @method  CwmsRuntimeManager::CwmsRuntimeManager           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:06:09 2012----------*/
CwmsRuntimeManager::CwmsRuntimeManager()
    : m_pCwmsRuntime(nullptr)
{
    // All the hard work was done above
}

/** +-=---------------------------------------------------------Do 30. Aug 14:06:19 2012----------*
 * @method  CwmsRuntimeManager::~CwmsRuntimeManager          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsRuntimeManager                                            *
 *----------------last changed: --------------------------------Do 30. Aug 14:06:19 2012----------*/
CwmsRuntimeManager::~CwmsRuntimeManager()
{
   DELPTR(m_pCwmsRuntime)
}

/** +-=---------------------------------------------------------Do 30. Aug 14:06:38 2012----------*
 * @method  CwmsRuntimeManager::SetApplicationName           // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:06:38 2012----------*/
void CwmsRuntimeManager::SetApplicationName(QString p_qstrName)
{
   m_qstrApplicationName = p_qstrName;
}

/** +-=---------------------------------------------------------Do 30. Aug 14:07:13 2012----------*
 * @method  CwmsRuntimeManager::GetApplicationName           // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:07:13 2012----------*/
QString CwmsRuntimeManager::GetApplicationName()
{
   return m_qstrApplicationName;
}

/** +-=---------------------------------------------------------Do 30. Aug 14:33:25 2012----------*
 * @method  CwmsRuntimeManager::StartApplication             // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:33:25 2012----------*/
void CwmsRuntimeManager::StartApplication()
{
   if (m_qstrApplicationName.isEmpty())
   {
      OpenApplicationSelection();
   }

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager) && !m_qstrApplicationName.isEmpty())
   {
      if (m_pCwmsRuntime)
      {
         DELPTR(m_pCwmsRuntime)
      }

      CwmsApplication cApp = GetApplication();

      if (cApp.IsValid())
      {
         m_pCwmsRuntime = new CwmsRuntime(nullptr);
         QString qstrCaption = m_qstrApplicationName + QStringLiteral(" V");
         qstrCaption += QString::number(cApp.GetVersionMajor()) +
                        QStringLiteral(".") + QString::number(cApp.GetVersionMinor()) +
                        QStringLiteral(".") + QString::number(cApp.GetVersionBugfix());

         if (pCdmManager->IsDemo() && cApp.GetLicenceCheck())
         {
            m_pCwmsRuntime->setWindowTitle(qstrCaption + " Demo");
         }
         else
         {
            m_pCwmsRuntime->setWindowTitle(qstrCaption);
         }

         m_pCwmsRuntime->SetApplication(cApp);
         m_pCwmsRuntime->FillWidget();
         m_pCwmsRuntime->show();
      }
      else
      {
         qApp->quit();
         exit(0);
      }
   }
}

/** +-=---------------------------------------------------------Do 30. Aug 14:20:08 2012----------*
 * @method  CwmsRuntimeManager::OpenApplicationSelection     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 30. Aug 14:20:08 2012----------*/
void CwmsRuntimeManager::OpenApplicationSelection()
{
//   m_qstrApplicationName = CwmsApplicationSelectionIf::GetApplicationString();
}

/** +-=---------------------------------------------------------Di 4. Sep 08:57:51 2012-----------*
 * @method  CwmsRuntimeManager::GetApplication               // public                            *
 * @return  CwmsApplication                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 08:57:51 2012-----------*/
CwmsApplication CwmsRuntimeManager::GetApplication()
{
   CwmsApplication cApp;
   
   CdmObject* pCdmObject = CwmsApplication::GetApplication(m_qstrApplicationName);
   cApp.SetObject(pCdmObject);
   
   return cApp;
}
