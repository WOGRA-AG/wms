/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsObjectListPropertiesDlg.cpp
 ** Started Implementation: 2012/12/13
 ** Description:
 **
 ** Implements the editor for objectlistproperties
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsRightsManagerIf.h"
#include "CwmsObjectListPropertiesDlg.h"

/** +-=---------------------------------------------------------Do 13. Dez 15:02:40 2012----------*
 * @method  CwmsObjectListPropertiesDlg::CwmsObjectListPropertiesDlg // public                    *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:02:40 2012----------*/
CwmsContainerPropertiesDlg::CwmsContainerPropertiesDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpList(nullptr)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Do 13. Dez 15:07:14 2012----------*
 * @method  CwmsObjectListPropertiesDlg::~CwmsObjectListPropertiesDlg // public, virtual          *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectListPropertiesDlg                                   *
 *----------------last changed: --------------------------------Do 13. Dez 15:07:14 2012----------*/
CwmsContainerPropertiesDlg::~CwmsContainerPropertiesDlg()
{
}

/** +-=---------------------------------------------------------Do 13. Dez 15:07:54 2012----------*
 * @method  CwmsObjectListPropertiesDlg::FillDialog          // public                            *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pList                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:07:54 2012----------*/
void CwmsContainerPropertiesDlg::FillDialog(CdmObjectContainer* p_pList)
{
   m_rpList = p_pList;

   if (CHKPTR(m_rpList))
   {
      m_pqleKeyname->setText(m_rpList->GetKeyname());
      m_pqleCaption->setText(m_rpList->GetCaption());
      m_pqteDescription->setPlainText(m_rpList->GetComment());
      m_pqchbIsTree->setChecked(m_rpList->IsTree());
      m_pqchbImmutable->setChecked(m_rpList->IsImmutable());
   }
}

/** +-=---------------------------------------------------------Do 13. Dez 15:33:59 2012----------*
 * @method  CwmsObjectListPropertiesDlg::RightsClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:33:59 2012----------*/
void CwmsContainerPropertiesDlg::RightsClickedSlot()
{
   if (CHKPTR(m_rpList))
   {
      CwmsRightsManagerIf* pCwmsRightsManagerIf = new CwmsRightsManagerIf(m_rpList, this);
      pCwmsRightsManagerIf->exec();
      delete pCwmsRightsManagerIf;
   }
}

/** +-=---------------------------------------------------------Do 13. Dez 15:08:15 2012----------*
 * @method  CwmsObjectListPropertiesDlg::Validate            // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:08:15 2012----------*/
bool CwmsContainerPropertiesDlg::Validate()
{
   return true;
}

/** +-=---------------------------------------------------------Do 13. Dez 15:08:34 2012----------*
 * @method  CwmsObjectListPropertiesDlg::Save                // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:08:34 2012----------*/
bool CwmsContainerPropertiesDlg::Save()
{
   bool bRet = false;

   if (CHKPTR(m_rpList))
   {
      m_rpList->SetTree(m_pqchbIsTree->isChecked());
      m_rpList->SetCaption(m_pqleCaption->text());
      m_rpList->SetComment(m_pqteDescription->toPlainText());
      m_rpList->SetImmutable(m_pqchbImmutable->isChecked());
      bRet = m_rpList->Commit();
   }
   
   return bRet;
}

/** +-=---------------------------------------------------------Do 13. Dez 15:08:03 2012----------*
 * @method  CwmsObjectListPropertiesDlg::OKClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Dez 15:08:03 2012----------*/
void CwmsContainerPropertiesDlg::OKClickedSlot()
{
   if (Validate() && Save())
   {
      accept();
   }
}
