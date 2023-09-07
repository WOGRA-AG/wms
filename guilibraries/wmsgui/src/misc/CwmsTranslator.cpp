/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsTranslator.cpp
 ** Started Implementation: 2012/09/07
 ** Description:
 **
 ** implements the translator for apps.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmQueryBuilder.h"
#include "CdmQuery.h"

// own Includes
#include "CwmsTranslator.h"

/** +-=---------------------------------------------------------Fr 7. Sep 11:10:52 2012-----------*
 * @method  CwmsTranslator::CwmsTranslator                   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:10:52 2012-----------*/
CwmsTranslator::CwmsTranslator()
: QTranslator(),
m_iObjectListId(0)
{
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:15:22 2012-----------*
 * @method  CwmsTranslator::LoadTranslations                 // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplication p_cApp                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:15:22 2012-----------*/
void CwmsTranslator::LoadTranslations(CwmsApplication p_cApp)
{
   if (p_cApp.IsValid())
   {
      CdmObjectContainer* pCdmList = p_cApp.GetTranslations();
      QString qstrLanguage = GetCurrentLanguage();

      if (CHKPTR(pCdmList) && !qstrLanguage.isEmpty())
      {
          m_qmTranslations.clear();
         m_iObjectListId = pCdmList->GetId();
         QString qstrWql = "select Original, Translation from \"" + 
                           pCdmList->GetKeyname() + "\" where Language = \"" +
                           qstrLanguage + "\"";

         CdmQuery* pCdmQuery = (CdmQuery*)CdmQueryBuilder::ExecuteQuery(qstrWql);

         if (pCdmQuery)
         {
            for (int iCounter = 0; iCounter < pCdmQuery->GetResultCount(); ++iCounter)
            {
               QString qstrSource = pCdmQuery->GetResultAt(0, iCounter).toString();
               QString qstrTranslation = pCdmQuery->GetResultAt(1, iCounter).toString();
               m_qmTranslations.insert(qstrSource, qstrTranslation);
            }
         }

         DELPTR(pCdmQuery);
      }
   }
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:11:00 2012-----------*
 * @method  CwmsTranslator::~CwmsTranslator                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsTranslator                                                *
 *----------------last changed: --------------------------------Fr 7. Sep 11:11:00 2012-----------*/
CwmsTranslator::~CwmsTranslator()
{
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:50:35 2012-----------*
 * @method  CwmsTranslator::translate                        // public, const                     *
 * @return  QString                                          //                                   *
 * @param   const char * context                             //                                   *
 * @param   const char * sourceText                          //                                   *
 * @param   const char *# disambiguation = 0                 //                                   *
 * @comment const char * context, const char * sourceText, const char * disambiguation = 0        *
 *----------------last changed: --------------------------------Fr 7. Sep 11:50:35 2012-----------*/
QString CwmsTranslator::translate(const char * context, const char * sourceText, const char *) const
{
   QString qstrTranslation;
   QString qstrContext(context);
   QString qstrText(sourceText);

   QString qstrLanguage = GetCurrentLanguage();

   if (!qstrLanguage.isEmpty())
   {
       if (m_qmTranslations.contains(qstrText))
       {
          qstrTranslation = m_qmTranslations[qstrText];
       }
       else
       {
          // const cast
          CwmsTranslator* p = const_cast<CwmsTranslator*>(this);
          p->AddTranslation(qstrText);
       }
   }
   else
   {
       qstrTranslation = qstrText;
   }

   return qstrTranslation;
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:58:17 2012-----------*
 * @method  CwmsTranslator::AddTranslation                   // private                           *
 * @return  void                                             //                                   *
 * @param   QString p_qstrTranslation                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:58:17 2012-----------*/
void CwmsTranslator::AddTranslation(QString p_qstrTranslation)
{
   CdmObjectContainer* pCdmList = GetObjectList();

   if (CHKPTR(pCdmList))
   {
      CdmObject* pCdmObject = pCdmList->CreateNewObject();
      pCdmObject->SetValue("Language", GetCurrentLanguage());
      pCdmObject->SetValue("Original", p_qstrTranslation);
      pCdmObject->SetValue("Translation", p_qstrTranslation);
      pCdmObject->Commit();

      m_qmTranslations.insert(p_qstrTranslation, p_qstrTranslation);
   }
}

/** +-=---------------------------------------------------------Fr 7. Sep 12:00:41 2012-----------*
 * @method  CwmsTranslator::translate                        // public, const                     *
 * @return  QString                                          //                                   *
 * @param   const char * context                             //                                   *
 * @param   const char * sourceText                          //                                   *
 * @param   const char * disambiguation                      //                                   *
 * @param   int n                                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 12:00:41 2012-----------*/
QString CwmsTranslator::translate(const char * context,
                                  const char * sourceText,
                                  const char * disambiguation,
                                  int n) const
{
   Q_UNUSED(n);
   return translate(context, sourceText, disambiguation);
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:18:25 2012-----------*
 * @method  CwmsTranslator::GetObjectList                    // public                            *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:18:25 2012-----------*/
CdmObjectContainer* CwmsTranslator::GetObjectList()
{
   CdmObjectContainer* pContainer = nullptr;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pCdmOLManager = pCdmManager->GetContainerManager();

      if (CHKPTR(pCdmOLManager))
      {
         pContainer = pCdmOLManager->FindContainerById(m_iObjectListId);
      }
   }

   return pContainer;
}

/** +-=---------------------------------------------------------Fr 7. Sep 11:22:03 2012-----------*
 * @method  CwmsTranslator::GetCurrentLanguage             // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 7. Sep 11:22:03 2012-----------*/
QString CwmsTranslator::GetCurrentLanguage() const
{
   QString qstrLanguage = 0;
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
	   qstrLanguage = pCdmManager->GetCurrentLanguage();
   }

   return qstrLanguage;
}  
