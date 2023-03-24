// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsRightsManagerIf.h"
#include "CwmsObjectListPropertiesDlg.h"

CwmsContainerPropertiesDlg::CwmsContainerPropertiesDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent),
  m_rpList(nullptr)
{
   setupUi(this);
}

CwmsContainerPropertiesDlg::~CwmsContainerPropertiesDlg()
{
}

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

void CwmsContainerPropertiesDlg::RightsClickedSlot()
{
   if (CHKPTR(m_rpList))
   {
      CwmsRightsManagerIf* pCwmsRightsManagerIf = new CwmsRightsManagerIf(m_rpList, this);
      pCwmsRightsManagerIf->exec();
      delete pCwmsRightsManagerIf;
   }
}

bool CwmsContainerPropertiesDlg::Validate()
{
   return true;
}

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

void CwmsContainerPropertiesDlg::OKClickedSlot()
{
   if (Validate() && Save())
   {
      accept();
   }
}
