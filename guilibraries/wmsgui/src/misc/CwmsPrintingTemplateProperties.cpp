/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CbgPrintingTemplateProperties.cpp
 ** Started Implementation: 2010/11/09
 ** Description:
 ** 
 ** CwmsPrintingTemplateProperties
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes



// WMS Includes
#include "CdmClass.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsClassSelectionIf.h"
#include "CwmsPrintingTemplateProperties.h"



/** +-=---------------------------------------------------------Mo 27. Aug 13:50:48 2012----------*
 * @method  CwmsPrintingTemplateProperties::CwmsPrintingTemplateProperties // public              *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 13:50:48 2012----------*/
CwmsPrintingTemplateProperties::CwmsPrintingTemplateProperties(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpCdmClass(nullptr)
{
	setupUi(this);
}

/** +-=---------------------------------------------------------Mo 27. Aug 13:50:58 2012----------*
 * @method  CwmsPrintingTemplateProperties::~CwmsPrintingTemplateProperties // public, virtual    *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CbgPrintingTemplateProperties                                 *
 *----------------last changed: --------------------------------Mo 27. Aug 13:50:58 2012----------*/
CwmsPrintingTemplateProperties::~CwmsPrintingTemplateProperties()
{

}

/** +-=---------------------------------------------------------Mo 27. Aug 13:51:32 2012----------*
 * @method  CwmsPrintingTemplateProperties::FillDialog       // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsPrintingTemplate p_cCwmsTemplate             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 13:51:32 2012----------*/
void CwmsPrintingTemplateProperties::FillDialog(CwmsPrintingTemplate p_cCwmsTemplate)
{
   m_cCwmsTemplate = p_cCwmsTemplate;
   FillLanguages();
   QString qstrLanguage = m_cCwmsTemplate.GetLanguage();

   if (!qstrLanguage.isEmpty())
   {
       m_pqcbLanguage->setCurrentText(qstrLanguage);
   }
   
   m_pqleName->setText(m_cCwmsTemplate.GetName());
   m_pqchbDefault->setChecked(m_cCwmsTemplate.IsDefault());

   m_rpCdmClass = m_cCwmsTemplate.GetClass();

   if (m_rpCdmClass)
   {
      m_pqleClass->setText(m_rpCdmClass->GetCaption() + " (" + m_rpCdmClass->GetKeyname() + ")");
   }

   if (m_cCwmsTemplate.GetType() == eWmsTemplateTypeList)
   {
      m_pqrbObjectList->setChecked(true);
   }
   else
   {
      m_pqrbObject->setChecked(true);
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 13:52:54 2012----------*
 * @method  CwmsPrintingTemplateProperties::FillLanguages    // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 13:52:54 2012----------*/
void CwmsPrintingTemplateProperties::FillLanguages()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();

      if (CHKPTR(pCdmDatabase))
      {
         QMap<int, QString> qmLanguages = pCdmDatabase->GetLanguageMap();

         QMap<int, QString>::iterator qmIt = qmLanguages.begin();
         QMap<int, QString>::iterator qmItEnd = qmLanguages.end();

         QString strLanguage = m_cCwmsTemplate.GetLanguage();

         for (; qmIt != qmItEnd; ++qmIt)
         {
            m_pqcbLanguage->addItem(qmIt.value(), qmIt.key());

            if (qmIt.value() == strLanguage)
            {
                m_pqcbLanguage->setCurrentIndex(m_pqcbLanguage->count() - 1);
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 13:52:59 2012----------*
 * @method  CwmsPrintingTemplateProperties::SaveData         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 13:52:59 2012----------*/
void CwmsPrintingTemplateProperties::SaveData()
{
   if (m_cCwmsTemplate.IsValid())
   {
      m_cCwmsTemplate.SetName(m_pqleName->text());
      m_cCwmsTemplate.SetDefault(m_pqchbDefault->isChecked());
      m_cCwmsTemplate.SetLanguage(m_pqcbLanguage->currentText());
      m_cCwmsTemplate.SetClass(m_rpCdmClass);

      if (m_pqrbObject->isChecked())
      {
         m_cCwmsTemplate.SetType(eWmsTemplateTypeObject);
      }
      else
      {
         m_cCwmsTemplate.SetType(eWmsTemplateTypeList);
      }

      m_cCwmsTemplate.CommitObject();
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:34:17 2012----------*
 * @method  CwmsPrintingTemplateProperties::Validate         // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:34:17 2012----------*/
bool CwmsPrintingTemplateProperties::Validate()
{
   bool bRet = false;

   if (m_rpCdmClass && 
       !m_pqleName->text().isEmpty())
   {  
      bRet = true;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:38:39 2012----------*
 * @method  CwmsPrintingTemplateProperties::SelectClassClickedSlot // private, slots              *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:38:39 2012----------*/
void CwmsPrintingTemplateProperties::SelectClassClickedSlot()
{
   m_rpCdmClass = CwmsClassSelectionIf::GetClass(this);

   if (m_rpCdmClass)
   {
      m_pqleClass->setText(m_rpCdmClass->GetCaption() + " (" + m_rpCdmClass->GetKeyname() + ")");
   }
}

/** +-=---------------------------------------------------------Mo 27. Aug 16:33:09 2012----------*
 * @method  CwmsPrintingTemplateProperties::OKClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 16:33:09 2012----------*/
void CwmsPrintingTemplateProperties::OKClickedSlot()
{
   if (Validate())
   {
      SaveData();
      accept();
   }
}


/** +-=---------------------------------------------------------Mo 27. Aug 13:53:04 2012----------*
 * @method  CwmsPrintingTemplateProperties::EditProperties   // public, static                    *
 * @return  void                                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 27. Aug 13:53:04 2012----------*/
void CwmsPrintingTemplateProperties::EditProperties(QWidget* p_pqwParent,
                                                    CdmObject* p_pCdmObject,
                                                    bool p_bNew)
{
   if (CHKPTR(p_pCdmObject))
   {
      CwmsPrintingTemplateProperties* pCbgEditor = new CwmsPrintingTemplateProperties(p_pqwParent);
      CwmsPrintingTemplate cCbmsTemplate(p_pCdmObject);
      pCbgEditor->FillDialog(cCbmsTemplate);

      if (pCbgEditor->exec() != QDialog::Accepted)
      {
         if (p_bNew)
         {
            p_pCdmObject->SetDeleted();
            p_pCdmObject->Commit();
         }
      }
      DELPTR(pCbgEditor);
   }
}
