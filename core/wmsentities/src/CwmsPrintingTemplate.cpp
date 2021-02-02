/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CbmsPrintingTemplate.cpp
 ** Started Implementation: 2010/11/03
 ** Description:
 ** 
 ** This class implements the printing template for one document
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QFile>
#include <QTextStream>

// WMS Includes
#include "CdmScheme.h"
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsPrintingTemplate.h"



/** +-=---------------------------------------------------------Mo 27. Aug 10:27:45 2012----------*
 * @method  CwmsPrintingTemplate::CwmsPrintingTemplate       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:27:45 2012----------*/
CwmsPrintingTemplate::CwmsPrintingTemplate(CdmObject* p_pCdmObject)
: CdmObjectAdaptor(p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:27:25 2012----------*
 * @method  CwmsPrintingTemplate::CwmsPrintingTemplate       // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:27:25 2012----------*/
CwmsPrintingTemplate::CwmsPrintingTemplate()
: CdmObjectAdaptor(nullptr)
{
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:14 2012----------*
 * @method  CwmsPrintingTemplate::~CwmsPrintingTemplate      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbmsPrintingTemplate                                          *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:14 2012----------*/
CwmsPrintingTemplate::~CwmsPrintingTemplate()
{
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:20 2012----------*
 * @method  CwmsPrintingTemplate::GetName                    // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:20 2012----------*/
QString CwmsPrintingTemplate::GetName()
{
   return GetString("Name");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:25 2012----------*
 * @method  CwmsPrintingTemplate::SetName                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:25 2012----------*/
void CwmsPrintingTemplate::SetName(QString p_qstrName)
{
   SetValue("Name", p_qstrName);
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:30:25 2012----------*
 * @method  CwmsPrintingTemplate::SetLanguage                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:30:25 2012----------*/
void CwmsPrintingTemplate::SetLanguage(QString p_iId)
{
   SetValue("Language", p_iId);
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:30:36 2012----------*
 * @method  CwmsPrintingTemplate::GetLanguage                // public                            *
 * @return  QString                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:30:36 2012----------*/
QString CwmsPrintingTemplate::GetLanguage()
{
   return GetString("Language");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:44 2012----------*
 * @method  CwmsPrintingTemplate::GetLanguageId              // public                            *
 * @return  long                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:44 2012----------*/
long CwmsPrintingTemplate::GetLanguageId()
{
   return GetObjectRef("Language");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:49 2012----------*
 * @method  CwmsPrintingTemplate::SetTemplate                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrContent                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:49 2012----------*/
void CwmsPrintingTemplate::SetTemplate(QString p_qstrContent)
{
   SetValue("Template", p_qstrContent);
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:28:54 2012----------*
 * @method  CwmsPrintingTemplate::GetTemplate                // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:28:54 2012----------*/
QString CwmsPrintingTemplate::GetTemplate()
{
   return GetString("Template");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:29:07 2012----------*
 * @method  CwmsPrintingTemplate::ReadTemplateFromFile       // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:29:07 2012----------*/
bool CwmsPrintingTemplate::ReadTemplateFromFile(QString p_qstrFilename)
{
   bool bSuccess = false;
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::ReadOnly))
   {
      QTextStream qTextStream(&qFile);
      QString qstrTemplate = qTextStream.readAll();
      SetTemplate(qstrTemplate);
      qFile.close();
      bSuccess = true;
   }

   return bSuccess;
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:29:13 2012----------*
 * @method  CwmsPrintingTemplate::SaveTemplateToFile         // public                            *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:29:13 2012----------*/
bool CwmsPrintingTemplate::SaveTemplateToFile(QString p_qstrFilename)
{
   bool bSuccess = false;
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::WriteOnly))
   {
      QTextStream qTextStream(&qFile);
      qTextStream << GetTemplate();
      qFile.close();
      bSuccess = true;
   }

   return bSuccess;
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:24:35 2012----------*
 * @method  CwmsPrintingTemplate::SetClass                   // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_rpCdmClass                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:24:35 2012----------*/
void CwmsPrintingTemplate::SetClass(CdmClass* p_rpCdmClass)
{
   if (p_rpCdmClass)
   {
      SetValue("Class", p_rpCdmClass->GetFullQualifiedName());
   }
   else
   {
      SetValue("Class", "");
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:32:28 2012----------*
 * @method  CwmsPrintingTemplate::GetClass                   // public                            *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:32:28 2012----------*/
CdmClass* CwmsPrintingTemplate::GetClass()
{
   CdmClass* pCdmClass = nullptr;
   QString qstrKeyname = GetString("Class");

   if (!qstrKeyname.isEmpty())
   {
      CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

      if (CHKPTR(pCdmManager) && CHKPTR(pCdmManager->GetCurrentScheme()))
      {
         CdmClassManager* pCdmClassManager = pCdmManager->GetClassManager(pCdmManager->GetCurrentScheme()->GetId());

         if (CHKPTR(pCdmClassManager))
         {
            pCdmClass = pCdmClassManager->FindClassByKeyname(qstrKeyname);
         }
      }
   }

   return pCdmClass;
}

/** +-=---------------------------------------------------------Mo 27. Aug 11:30:48 2012----------*
 * @method  CwmsPrintingTemplate::SetType                    // public                            *
 * @return  void                                             //                                   *
 * @param   EwmsTemplateType p_eWmsType                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:30:48 2012----------*/
void CwmsPrintingTemplate::SetType(EwmsTemplateType p_eWmsType)
{
   SetValue("Type", p_eWmsType);
}
// depricated
void CwmsPrintingTemplate::SetType(int p_eWmsType) // for keep old bms code working
{
   SetValue("Type", p_eWmsType);
}

// depricated
int CwmsPrintingTemplate::GetTypeAsInt()// for keep old bms code working
{
   return GetInt("Type");
}


/** +-=---------------------------------------------------------Mo 27. Aug 11:32:01 2012----------*
 * @method  CwmsPrintingTemplate::GetType                    // public                            *
 * @return  EwmsTemplateType                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 11:32:01 2012----------*/
EwmsTemplateType CwmsPrintingTemplate::GetType()
{
   return (EwmsTemplateType)GetInt("Type");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:29:40 2012----------*
 * @method  CwmsPrintingTemplate::IsDefault                  // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:29:40 2012----------*/
bool CwmsPrintingTemplate::IsDefault()
{
   return GetBool("Default");
}

/** +-=---------------------------------------------------------Mo 27. Aug 10:29:46 2012----------*
 * @method  CwmsPrintingTemplate::SetDefault                 // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bDefault                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 10:29:46 2012----------*/
void CwmsPrintingTemplate::SetDefault(bool p_bDefault)
{
   SetValue("Default", p_bDefault);
}
