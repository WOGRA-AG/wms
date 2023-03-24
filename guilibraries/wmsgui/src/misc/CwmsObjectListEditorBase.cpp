// System and QT Includes
#include <QPair>

// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CwmsguiObjectEditorIf.h"
#include "CwmsObjectListEditorBase.h"


CwmsContainerEditorBase::CwmsContainerEditorBase()
: m_bShowEditButton(false)
{
}

void CwmsContainerEditorBase::AddReadOnlyValue(QString p_qstrValue)
{
   m_qstrlReadOnlyValues.append(p_qstrValue);
}

void CwmsContainerEditorBase::SetShowEditButton(bool p_bShowEditButton)
{
   m_bShowEditButton = p_bShowEditButton;
}

void CwmsContainerEditorBase::AddHiddenValue(QString p_qstrValue)
{
   m_qstrlHiddenValues.append(p_qstrValue);
}

void CwmsContainerEditorBase::SetCaptionValue(QString p_qstrValue)
{
   m_qstrCaptionValue = p_qstrValue;
}

void CwmsContainerEditorBase::SetSortedList(QStringList p_qstrlSorting)
{
   m_qstrlSortedList = p_qstrlSorting;
}

bool CwmsContainerEditorBase::OpenEditor(CdmObject* p_pCdmObject)
{
   bool bRet = false;

   if (CHKPTR(p_pCdmObject))
   {
      CwmsguiObjectEditorIf* pCoeObjectEditor = new CwmsguiObjectEditorIf(p_pCdmObject);
      pCoeObjectEditor->SetCaptionValue(m_qstrCaptionValue);

      FillReadOnlyMembers(pCoeObjectEditor);
      FillHiddenMembers(pCoeObjectEditor);
      FillObjectRefData(pCoeObjectEditor);
      pCoeObjectEditor->SetSortedList(m_qstrlSortedList);

      pCoeObjectEditor->FillDialog();

      if (pCoeObjectEditor->exec() == QDialog::Accepted)
      {
         bRet = true;
      }

      DELPTR(pCoeObjectEditor);
   }

   return bRet;
}

void CwmsContainerEditorBase::FillReadOnlyMembers(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   for (int iCounter = 0; iCounter < m_qstrlReadOnlyValues.size(); ++iCounter)
   {
      p_pCoeEditor->AddReadOnlyValue(m_qstrlReadOnlyValues.at(iCounter));
   }
}

void CwmsContainerEditorBase::FillHiddenMembers(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   for (int iCounter = 0; iCounter < m_qstrlHiddenValues.size(); ++iCounter)
   {
      p_pCoeEditor->AddReadOnlyValue(m_qstrlHiddenValues.at(iCounter));
   }
}

void CwmsContainerEditorBase::FillObjectRefData(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   QMap<QString, TStringPair>::iterator qmIt = m_qmObjectRefData.begin();
   QMap<QString, TStringPair>::iterator qmItEnd = m_qmObjectRefData.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      p_pCoeEditor->AddObjectRefData(qmIt.key(), qmIt.value().first, qmIt.value().second);
   }
}

void CwmsContainerEditorBase::AddObjectRefData(QString p_qstrMember,
                                                QString p_qstrRef,
                                                QString p_qstrDisplayCaption)
{
   m_qmObjectRefData.insert(p_qstrMember, TStringPair(p_qstrRef, p_qstrDisplayCaption));
}
