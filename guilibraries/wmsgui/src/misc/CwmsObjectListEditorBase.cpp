/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsObjectListEditorBase.cpp
 ** Started Implementation: 2008/08/19
 ** Description:
 ** 
 ** Implements the interfaceclass for objectlisteditorwidget and objectlisteditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QPair>

// WMS Includes
#include "CdmLogging.h"

// Own Includes
#include "CwmsguiObjectEditorIf.h"
#include "CwmsObjectListEditorBase.h"


/** +-=---------------------------------------------------------So 14. Mrz 12:17:01 2010----------*
 * @method  CwmsObjectListEditorBase::CwmsObjectListEditorBase // public                          *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 12:17:01 2010----------*/
CwmsContainerEditorBase::CwmsContainerEditorBase()
: m_bShowEditButton(false)
{
}

/** +-=---------------------------------------------------------So 14. Mrz 12:15:14 2010----------*
 * @method  CwmsObjectListEditorBase::AddReadOnlyValue       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method adds readonly values.                                                     *
 *----------------last changed: --------------------------------So 14. Mrz 12:15:14 2010----------*/
void CwmsContainerEditorBase::AddReadOnlyValue(QString p_qstrValue)
{
   m_qstrlReadOnlyValues.append(p_qstrValue);
}

/** +-=---------------------------------------------------------So 14. Mrz 12:16:02 2010----------*
 * @method  CwmsObjectListEditorBase::SetShowEditButton      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   bool p_bShowEditButton                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 12:16:02 2010----------*/
void CwmsContainerEditorBase::SetShowEditButton(bool p_bShowEditButton)
{
   m_bShowEditButton = p_bShowEditButton;
}

/** +-=---------------------------------------------------------So 14. Mrz 12:16:15 2010----------*
 * @method  CwmsObjectListEditorBase::AddHiddenValue         // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 12:16:15 2010----------*/
void CwmsContainerEditorBase::AddHiddenValue(QString p_qstrValue)
{
   m_qstrlHiddenValues.append(p_qstrValue);
}

/** +-=---------------------------------------------------------So 14. Mrz 12:18:57 2010----------*
 * @method  CwmsObjectListEditorBase::SetCaptionValue        // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment Over this method you can set, from which value the objectcaption will be              *
 *          autmatically copied.                                                                  *
 *----------------last changed: --------------------------------So 14. Mrz 12:18:57 2010----------*/
void CwmsContainerEditorBase::SetCaptionValue(QString p_qstrValue)
{
   m_qstrCaptionValue = p_qstrValue;
}

/** +-=---------------------------------------------------------So 14. Mrz 12:22:17 2010----------*
 * @method  CwmsObjectListEditorBase::SetSortedList          // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QStringList p_qstrlSorting                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 12:22:17 2010----------*/
void CwmsContainerEditorBase::SetSortedList(QStringList p_qstrlSorting)
{
   m_qstrlSortedList = p_qstrlSorting;
}

/** +-=---------------------------------------------------------Di 16. Mrz 08:24:47 2010----------*
 * @method  CwmsObjectListEditorBase::OpenEditor             // protected                         *
 * @return  bool                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 16. Mrz 08:24:47 2010----------*/
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

/** +-=---------------------------------------------------------So 14. Mrz 13:55:35 2010----------*
 * @method  CwmsObjectListEditorBase::FillReadOnlyMembers    // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsguiObjectEditorIf* p_pCoeEditor              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 13:55:35 2010----------*/
void CwmsContainerEditorBase::FillReadOnlyMembers(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   for (int iCounter = 0; iCounter < m_qstrlReadOnlyValues.size(); ++iCounter)
   {
      p_pCoeEditor->AddReadOnlyValue(m_qstrlReadOnlyValues.at(iCounter));
   }
}

/** +-=---------------------------------------------------------So 14. Mrz 13:55:51 2010----------*
 * @method  CwmsObjectListEditorBase::FillHiddenMembers      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsguiObjectEditorIf* p_pCoeEditor              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 13:55:51 2010----------*/
void CwmsContainerEditorBase::FillHiddenMembers(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   for (int iCounter = 0; iCounter < m_qstrlHiddenValues.size(); ++iCounter)
   {
      p_pCoeEditor->AddReadOnlyValue(m_qstrlHiddenValues.at(iCounter));
   }
}

/** +-=---------------------------------------------------------So 14. Mrz 14:32:47 2010----------*
 * @method  CwmsObjectListEditorBase::FillObjectRefData      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsguiObjectEditorIf* p_pCoeEditor              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 14:32:47 2010----------*/
void CwmsContainerEditorBase::FillObjectRefData(CwmsguiObjectEditorIf* p_pCoeEditor)
{
   QMap<QString, TStringPair>::iterator qmIt = m_qmObjectRefData.begin();
   QMap<QString, TStringPair>::iterator qmItEnd = m_qmObjectRefData.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      p_pCoeEditor->AddObjectRefData(qmIt.key(), qmIt.value().first, qmIt.value().second);
   }
}

/** +-=---------------------------------------------------------So 14. Mrz 14:37:08 2010----------*
 * @method  CwmsObjectListEditorBase::AddObjectRefData       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   QString p_qstrRef                                //                                   *
 * @param   QString p_qstrDisplayCaption                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 14. Mrz 14:37:08 2010----------*/
void CwmsContainerEditorBase::AddObjectRefData(QString p_qstrMember,
                                                QString p_qstrRef,
                                                QString p_qstrDisplayCaption)
{
   m_qmObjectRefData.insert(p_qstrMember, TStringPair(p_qstrRef, p_qstrDisplayCaption));
}

/** +-=---------------------------------------------------------So 14. Mrz 12:15:37 2010----------*
* @method  CwmsObjectListEditorBase::AddColumn              // public, p virtual                 *
* @return  void                                             //                                   *
* @param   QString p_qstrColumn                             //                                   *
* @comment                                                                                       *
*----------------last changed: --------------------------------So 14. Mrz 12:15:37 2010----------*/

/** +-=---------------------------------------------------------Di 19. Aug 21:50:35 2008----------*
 * @method  CwmsObjectListEditorBase::SetObjectList          // public, p virtual                 *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 19. Aug 21:50:35 2008----------*/

/** +-=---------------------------------------------------------Di 25. Sep 15:08:27 2012----------*
 * @method  CwmsObjectListEditorIf::SetModel              // public, p virtual                    *
 * @return  void                                          //                                      *
 * @param   CdmQueryModel* p_pModel                     //                                        *
 * @comment This method sets the proxy for this gui component.                                    *
 *----------------last changed: -----------------------------Di 25. Sep 15:08:27 2012-------------*/

/** +-=---------------------------------------------------------Di 19. Aug 21:56:24 2008----------*
 * @method  CwmsObjectListEditorBase::FillDialog             // public, p virtual                 *
 * @return  void                                             //                                   *
 * @comment This method fills the dialog after all settings were done.                            *
 *----------------last changed: --------------------------------Di 19. Aug 21:56:24 2008----------*/

/** +-=---------------------------------------------------------Di 19. Aug 22:00:44 2008----------*
 * @method  CwmsObjectListEditorBase::SetDefaultValueForNewObject // public, p virtual            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValueName                          //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @param   QString p_qstrValue2                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 19. Aug 22:00:44 2008----------*/