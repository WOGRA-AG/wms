/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsFunctionEditor.cpp
 ** Started Implementation: 2012/09/20
 ** Description:
 **
 ** implements the function editor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFileDialog>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmClassManager.h"
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmExecutorFunction.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmClass.h"
#include "CdmRights.h"
#include "CdmClassMethod.h"
#include "CdmMessageManager.h"

// WMS GUI Includes
#include "CwmsObjectSelectionIf.h"
#include "CwmsObjectListSelectionIf.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsUniversalRightsManager.h"
#include "CwmsClassDataFiller.h"
#include "CwmsFunctionEditor.h"
#include "CwmsJson.h"
#include "CsaFactory.h"

/** +-=---------------------------------------------------------Do 20. Sep 14:54:01 2012----------*
 * @method  CwmsFunctionEditor::CwmsFunctionEditor           // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 14:54:01 2012----------*/
CwmsFunctionEditor::CwmsFunctionEditor(QWidget* p_pqwParent)
: QWidget(p_pqwParent),
  m_rpItem(nullptr),
  m_bModified(false)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Do 20. Sep 14:54:26 2012----------*
 * @method  CwmsFunctionEditor::~CwmsFunctionEditor          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsFunctionEditor                                            *
 *----------------last changed: --------------------------------Do 20. Sep 14:54:26 2012----------*/
CwmsFunctionEditor::~CwmsFunctionEditor()
{
    if (IsModified())
    {
        if (CdmMessageManager::Ask(tr("Änderungen vorhanden"), tr("Sie haben Änderungen an der Funktion vorgenommen.\n Wollen Sie die Speichern?")))
        {
            Save();
        }
    }
}

/** +-=---------------------------------------------------------Do 20. Sep 16:35:47 2012----------*
 * @method  CwmsFunctionEditor::FillDialog                   // public                           *
 * @return  void                                             //                                   *
 * @param   CdmClassMethod* p_pMethod                        //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   bool p_bNew                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 16:35:47 2012----------*/
void CwmsFunctionEditor::FillDialog(CdmClassMethod* p_pMethod, CdmClass* p_pCdmClass, bool p_bNew)
{
   if (CHKPTR(p_pMethod) && CHKPTR(p_pCdmClass))
   {
      m_rpCdmClass = p_pCdmClass;
      m_rpCdmFunction = p_pMethod;

      if (!p_bNew)
      {
         m_pqleName->setText(m_rpCdmFunction->GetMethodName());
         m_pqleCaption->setText(m_rpCdmFunction->GetCaption());
         QPixmap qPixmap = m_rpCdmFunction->GetIcon();
         
         if (!qPixmap.isNull())
         {
            m_qbaIcon = m_rpCdmFunction->GetIconAsByteArray();
            QIcon qIcon(qPixmap);
            m_pqpbSelectIcon->setIcon(qIcon);
         }
         
         switch (m_rpCdmFunction->GetAccess())
         {
         case eDmMemberAccessPublic:
            m_pqrbPublic->setChecked(true);
            break;
         case eDmMemberAccessProtected:
            m_pqrbProtected->setChecked(true);
            break;
         case eDmMemberAccessPrivate:
            m_pqrbPrivate->setChecked(true);
            break;
         }

         if (!m_rpCdmFunction->IsStatic())
         {
            m_pqrbObject->setChecked(true);
         }
         else
         {
            m_pqrbStatic->setChecked(true);
         }
      }
   
      AddTypesToTypeBox();
      AddClassesToComboBox(); 
      FillParameters();
      int iIndex = m_pqcbReturnType->findData(m_rpCdmFunction->GetReturnType());
      m_pqcbReturnType->setCurrentIndex(iIndex);
      m_pjsEditor->setTextWrapEnabled(false);
      m_pjsEditor->setPlainText(m_rpCdmFunction->GetSourceCode());
      m_pjsEditor->SetClass(m_rpCdmClass);
      m_pjsEditor->setCodeFoldingEnabled(true);
      m_pjsEditor->document()->setModified(false);

      if (!p_bNew)
      {
          m_bModified = false;
      }
   }
}

/** +-=---------------------------------------------------------Do 20. Sep 15:06:26 2012----------*
 * @method  CwmsFunctionEditor::FillParameters               // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:06:26 2012----------*/
void CwmsFunctionEditor::FillParameters()
{
   m_pqtwParameters->clear();
   QList<CdmClassMethodParameter> qmParams = m_rpCdmFunction->GetParameters();

   for (int iCounter = 0; iCounter < qmParams.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = qmParams[iCounter];
      QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwParameters);
      pItem->setText(0, QString::number(cParam.m_iPos));
      pItem->setText(1, CdmMember::GetValueTypeAsString(cParam.m_eType));
      pItem->setText(2, cParam.GetName());
      pItem->setData(0, Qt::UserRole, cParam.m_eType);
      pItem->setData(1, Qt::UserRole, (int)cParam.m_lReference);
   }
}

/** +-=---------------------------------------------------------Do 20. Sep 15:43:48 2012----------*
 * @method  CwmsFunctionEditor::AddTypesToTypeBox            // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:43:48 2012----------*/
void CwmsFunctionEditor::AddTypesToTypeBox()
{
    AddTypesToTypeBox(m_pqcbType);
    m_pqcbReturnType->addItem(tr("Keiner"), eDmValueNone);
    AddTypesToTypeBox(m_pqcbReturnType);
    m_pqcbReturnType->addItem(tr("Binärdokument"), eDmValueBinaryDocument);
}

void CwmsFunctionEditor::AddTypesToTypeBox(QComboBox* p_pComboBox)
{
    p_pComboBox->addItem(tr("Wahrheitsausdruck"), eDmValueBool);
    p_pComboBox->addItem(tr("Ganze Zahl"), eDmValueInt);
    p_pComboBox->addItem(tr("Fließkommazahl"), eDmValueDouble);
    p_pComboBox->addItem(tr("Textdokument"), eDmValueCharacterDocument);
    p_pComboBox->addItem(tr("Datum"), eDmValueDate);
    p_pComboBox->addItem(tr("Uhrzeit"), eDmValueTime);
    p_pComboBox->addItem(tr("Zeitstempel"), eDmValueDateTime);
    p_pComboBox->addItem(tr("Objektcontainer"), eDmValueContainerRef);
    p_pComboBox->addItem(tr("Objekt"), eDmValueObjectRef);
    p_pComboBox->addItem(tr("Zeichenkette"), eDmValueString);
    p_pComboBox->addItem(tr("Benutzer"), eDmValueUser);
    p_pComboBox->addItem(tr("Benutzergruppe"), eDmValueUserGroup);
    p_pComboBox->addItem(tr("Array"), eDmValueArray);
    p_pComboBox->addItem(tr("QObject"), eDmValueQObject);
}


/** +-=---------------------------------------------------------Do 22. Nov 11:22:56 2012----------*
 * @method  CwmsFunctionEditor::AddClassesToComboBox         // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 11:22:56 2012----------*/
void CwmsFunctionEditor::AddClassesToComboBox()
{
   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      CdmClassManager* pClassManager = pManager->GetClassManager();

      if (CHKPTR(pClassManager))
      {
         QList<CdmClass*> qlClasses;
         pClassManager->GetClassList(qlClasses);

         QList<CdmClass*>::iterator qlIt = qlClasses.begin();
         QList<CdmClass*>::iterator qlItEnd = qlClasses.end();

         for (; qlIt != qlItEnd; ++qlIt)
         {
            CdmClass* pClass = *qlIt;

            if (CHKPTR(pClass))
            {
               m_pqcbClass->addItem(pClass->GetCaption() + "(" + pClass->GetKeyname() + ")", 
                                    (int)pClass->GetId());
            }
         }

      }
   }
}

/** +-=---------------------------------------------------------Do 22. Nov 11:16:30 2012----------*
 * @method  CwmsFunctionEditor::TypeIndexChangedSlot         // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 11:16:30 2012----------*/
void CwmsFunctionEditor::TypeIndexChangedSlot()
{
   m_pqlClass->hide();
   m_pqcbClass->hide();

   EdmValueType eValue = (EdmValueType)m_pqcbType->itemData(m_pqcbType->currentIndex()).toInt();

   if (eValue == eDmValueContainerRef ||
       eValue == eDmValueObjectRef)
   {
      m_pqlClass->show();
      m_pqcbClass->show();         
   }
}

/** +-=---------------------------------------------------------Do 22. Nov 10:38:16 2012----------*
 * @method  CwmsFunctionEditor::AddParameterClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 10:38:16 2012----------*/
void CwmsFunctionEditor::AddParameterClickedSlot()
{
   QString qstrName = m_pqleParameterName->text();
   EdmValueType eValue = (EdmValueType)m_pqcbType->itemData(m_pqcbType->currentIndex()).toInt();
   int iClassId = 0;

   if (eValue == eDmValueContainerRef || 
       eValue == eDmValueObjectRef)
   {
      iClassId = m_pqcbClass->itemData(m_pqcbClass->currentIndex()).toInt();
   }

   m_rpCdmFunction->AddParameter(qstrName, eValue, iClassId);
   m_pqcbType->setCurrentIndex(0);
   m_pqcbClass->setCurrentIndex(0);
   m_pqleParameterName->clear();
   FillParameters();
}

/** +-=---------------------------------------------------------Do 20. Sep 15:56:02 2012----------*
 * @method  CwmsFunctionEditor::DeleteParameterClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:56:02 2012----------*/
void CwmsFunctionEditor::DeleteParameterClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->DeleteParameter(qstrName);
      FillParameters();
   }
}

/** +-=---------------------------------------------------------Do 20. Sep 15:57:20 2012----------*
 * @method  CwmsFunctionEditor::MoveParameterDownClickedSlot // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:57:20 2012----------*/
void CwmsFunctionEditor::MoveParameterDownClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->MoveParameterDown(qstrName);
      FillParameters();
      SetParameterSelected(qstrName);
   }
}

void CwmsFunctionEditor::SetParameterSelected(QString p_qstrName)
{
    CwmsTreeWidgetHelper::SelectItem(m_pqtwParameters, 2, p_qstrName);
}

/** +-=---------------------------------------------------------Do 20. Sep 15:57:46 2012----------*
 * @method  CwmsFunctionEditor::MoveParameterUpClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:57:46 2012----------*/
void CwmsFunctionEditor::MoveParameterUpClickedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqtwParameters);

   if (pItem)
   {
      QString qstrName = pItem->text(2);
      m_rpCdmFunction->MoveParameterUp(qstrName);
      FillParameters();
      SetParameterSelected(qstrName);
   }
}


/** +-=---------------------------------------------------------Do 20. Sep 15:58:14 2012----------*
 * @method  CwmsFunctionEditor::EnlargeCodeViewClickedSlot   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:58:14 2012----------*/
void CwmsFunctionEditor::EnlargeCodeViewClickedSlot()
{
   if (m_pqgbComment->isVisible())
   {
      m_pqgbComment->hide();
      m_pqgbAccess->hide();
      m_pqgbFunctionType->hide();
   }
   else
   {
      m_pqgbComment->show();
      m_pqgbAccess->show();
      m_pqgbFunctionType->show();
   }
}

/** +-=---------------------------------------------------------Do 20. Sep 15:58:45 2012----------*
 * @method  CwmsFunctionEditor::RightsClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:58:45 2012----------*/
void CwmsFunctionEditor::RightsClickedSlot()
{
   if (m_rpCdmFunction)
   {
      CdmRights* pCdmRights = &m_rpCdmFunction->GetRights();
      CwmsUniversalRightsManagerIf* pCwmsRighstManager =
         new CwmsUniversalRightsManagerIf(pCdmRights, this);
      pCwmsRighstManager->exec();
      DELPTR(pCwmsRighstManager);
      m_rpCdmClass->Commit();
   }
}



/** +-=---------------------------------------------------------Mo 4. Feb 16:47:07 2013-----------*
 * @method  CwmsFunctionEditor::SelectIconClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Feb 16:47:07 2013-----------*/
void CwmsFunctionEditor::SelectIconClickedSlot()
{
   QString qstrIconName = QFileDialog::getOpenFileName(this, tr("Bitte wählen Sie ein Icon aus dem Dateisystem aus"),
      "", "*.png *.jpg *.gif *.ico");

   if (!qstrIconName.isEmpty())
   {
      QFile qFile(qstrIconName);

      if (qFile.open(QIODevice::ReadOnly))
      {
         m_qbaIcon = qFile.readAll();
         QPixmap qPixmap;
         qPixmap.loadFromData(m_qbaIcon);

         if (!qPixmap.isNull())
         {
            QIcon qIcon(qPixmap);
            m_pqpbSelectIcon->setIcon(qIcon);
            m_bModified = true;
         }  
      }
   }
}

bool CwmsFunctionEditor::Save()
{
    bool bSuccess = SaveData();

    if (bSuccess)
    {
        if (m_rpItem) // refesh treewidgetitem
        {
          m_rpItem->setText(0, m_rpCdmFunction->GetMethodName());
          m_rpItem->setData(0, Qt::UserRole, m_rpCdmFunction->GetUriInternal());
        }

        m_bModified = false;
    }

    return bSuccess;
}

void CwmsFunctionEditor::Revert()
{
    FillDialog(m_rpCdmFunction, m_rpCdmClass, false);
}

void CwmsFunctionEditor::SetItem(QTreeWidgetItem * p_pItem)
{
    m_rpItem = p_pItem;
}

bool CwmsFunctionEditor::IsModified()
{
    bool bRet = m_bModified;

    if (!bRet)
    {
        bRet = m_pjsEditor->document()->isModified();
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetMethodName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetMethodName() != m_pqleName->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetCaption() != m_pqleCaption->text());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetComment() != m_pqteComment->toPlainText());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessPrivate && m_pqrbPrivate->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessProtected && m_pqrbProtected->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetAccess() != eDmMemberAccessPublic && m_pqrbPublic->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->IsStatic() != m_pqrbStatic->isChecked());
    }

    if (!bRet)
    {
        bRet = (m_rpCdmFunction->GetReturnType() != m_pqcbReturnType->currentIndex());
    }


    return bRet;
}

void CwmsFunctionEditor::Debug()
{
    ExecuteFunction(true);
}

void CwmsFunctionEditor::Execute()
{
    ExecuteFunction(false);
}

void CwmsFunctionEditor::ExecuteFunction(bool p_bDebugger)
{
    QVariant qvResult;

    if (Save())
    {
         if (CHKPTR(m_rpCdmFunction))
         {
            if (m_rpCdmFunction->IsStatic())
            {
               QVariantList qlParameters;

               if (p_bDebugger)
               {
                  qvResult = CdmExecutor::DebugFunction(m_rpCdmFunction, nullptr, qlParameters, true, true);
               }
               else
               {
                  qvResult = CdmExecutor::ExecuteFunction(m_rpCdmFunction, nullptr, qlParameters, true, true, false, false);
               }
            }
            else
            {
               CdmObjectContainer* pList = CwmsContainerSelectionIf::GetObjectContainer(m_rpCdmClass->GetSchemeId(), m_rpCdmClass->GetId(), this);

               if (pList)
               {
                  CdmObject* pObject = CwmsObjectSelectionIf::GetObject(pList, nullptr, this);

                  if (pObject)
                  {
                     QVariantList qlParameters;
                     if (p_bDebugger)
                     {
                        qvResult = CdmExecutor::DebugFunction(m_rpCdmFunction, pObject, qlParameters, true, true);
                     }
                     else
                     {
                        qvResult = CdmExecutor::ExecuteFunction(m_rpCdmFunction, pObject, qlParameters, true, true, false, false);
                     }
                  }
                  else
                  {
                      CdmMessageManager::information(tr("Funktion wird nicht ausgeführt"), tr("Die Funktion kann nicht ausgeführt werden, da kein Objekt gewählt wurde."));
                  }
               }
            }
         }
  }

  QVariant qConvertedValue = CsaFactory::convertToResultVariant(qvResult);
  CwmsJson CwmsJson;
  QString qstrResult = CwmsJson.serialize(qConvertedValue);

  if (qstrResult.isEmpty())
  {
     qstrResult = tr("Kein Rückgabewert");
  }

  CdmMessageManager::information(tr("Ergebnis"), tr("Funktion beendet. Rückgabewert: %1").arg(qstrResult));
}



/** +-=---------------------------------------------------------Do 20. Sep 15:59:25 2012----------*
 * @method  CwmsFunctionEditor::Validate                     // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Sep 15:59:25 2012----------*/
bool CwmsFunctionEditor::Validate()
{
   bool bRet = true;

   if (m_pqleName->text().isEmpty())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Funktionsname fehlt"), tr("Funktion ohne Name kann nicht gespeichert werden!"));
   }
   else
   {
       if (!CdmModelElement::CheckKeyname(m_pqleName->text()))
       {
           bRet = false;
           CdmMessageManager::critical(tr("Funktionsname ungültig"), tr("Funktionsname muss mit einem Buchstaben beginnen und darf keine Umlaute und Sonderzeichen auße r\"_\" enthalten."));
       }
   }

   if (m_pjsEditor->toPlainText().isEmpty())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Sourcecode fehlt"), tr("Funktion ohne Sourcecode kann nicht gespeichert werden!"));
   }

   if (m_pqtwParameters->topLevelItemCount() > 10)
   {
      bRet = false;
      CdmMessageManager::critical(tr("Zu viele Aufrufparameter"), 
                                  tr("Funktion mit mehr als 10 Aufrufparametern ist nicht erlaubt.\n"
                                     "Überprüfen Sie Ihren Programmierstil ;-)\n"
                                     "Lehrgänge zur effizienten Programmierung können Sie bei WOGRA Consulting buchen."));
   }

   if (m_rpCdmClass->HasMethod(m_pqleName->text()))
   {
      if (m_rpCdmClass->FindMethod(m_pqleName->text()) != m_rpCdmFunction)
      {
         bRet = false;
         CdmMessageManager::critical(tr("Funktion existiert bereits"), 
            tr("Eine Funktion mit dem gleichen Namen existiert bereits."));
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 9. Nov 15:27:40 2012-----------*
 * @method  CwmsFunctionEditor::SaveData                     // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 9. Nov 15:27:40 2012-----------*/
bool CwmsFunctionEditor::SaveData()
{
   bool bRet = false;

   if (m_rpCdmFunction)
   {
      m_rpCdmFunction->SetComment(m_pqteComment->toPlainText());
      m_rpCdmFunction->SetMethodName(m_pqleName->text());
      EdmValueType eReturnType = (EdmValueType)m_pqcbReturnType->itemData(m_pqcbReturnType->currentIndex()).toInt();
      m_rpCdmFunction->SetReturnType(eReturnType);

      if (m_pqrbPublic->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessPublic);
      }
      else if (m_pqrbProtected->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessProtected);
      }
      else if (m_pqrbPrivate->isChecked())
      {
         m_rpCdmFunction->SetAccess(eDmMemberAccessPrivate);
      }

      int iParameterCount = m_pqtwParameters->topLevelItemCount();
      QList<CdmClassMethodParameter> qlParams;

      for (int iCounter = 0; iCounter < iParameterCount; ++iCounter)
      {  
         QTreeWidgetItem* pItem = m_pqtwParameters->topLevelItem(iCounter);

         if (pItem)
         {
            CdmClassMethodParameter cParam;
            cParam.SetName(pItem->text(2));
            cParam.m_eType = (EdmValueType)pItem->data(0, Qt::UserRole).toInt();
            cParam.m_iPos = iCounter;
            cParam.m_lReference = pItem->data(1, Qt::UserRole).toInt();
            qlParams.append(cParam);
         }
      }
    
      m_rpCdmFunction->SetParameters(qlParams);
      m_rpCdmFunction->SetStatic(m_pqrbStatic->isChecked());
      m_rpCdmFunction->SetSourceCode(m_pjsEditor->toPlainText());
      m_rpCdmFunction->SetVersion(m_rpCdmFunction->GetVersion() + 1);

      CdmExecutor::GetExecutor()->GetFunction()->CreateEngine();

      if (CdmExecutor::GetExecutor()->GetFunction()->GetEngine()->SyntaxCheck(m_pjsEditor->toPlainText()))
      {
        bRet = true;
      }

      m_rpCdmFunction->SetCaption(m_pqleCaption->text());
      m_rpCdmFunction->SetIcon(m_qbaIcon);
      m_rpCdmClass->Commit();
      m_pjsEditor->document()->setModified(false);
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mo 12. Nov 13:53:47 2012----------*
 * @method  CwmsFunctionEditor::SyntaxCheckClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 12. Nov 13:53:47 2012----------*/
void CwmsFunctionEditor::SyntaxCheckClickedSlot()
{
   QString qstrCode = m_pjsEditor->toPlainText();
   CdmExecutor::GetExecutor()->GetFunction()->CreateEngine();

   if (CdmExecutor::GetExecutor()->GetFunction()->GetEngine()->SyntaxCheck(qstrCode))
   {
      CdmMessageManager::information(tr("Syntax gültig"), tr("Die Syntax des Codes ist gültig."));
   }
}


void CwmsFunctionEditor::FindNextClickedSlot()
{
    if (!Find(0))
    {
        if (CdmMessageManager::Ask(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden.\n Soll die Suche von Beginn an weitergeführt werden?")))
        {
            QTextCursor startPos;
            startPos.setPosition(0);
            m_pjsEditor->setTextCursor(startPos);

            if (!Find(0))
            {
                CdmMessageManager::information(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden."));
            }
        }
    }
}

void CwmsFunctionEditor::FindPreviousClickedSlot()
{
    if (!Find(QTextDocument::FindBackward))
    {
        if (CdmMessageManager::Ask(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden.\n Soll die Suche vom Ende weitergeführt werden?")))
        {
            QTextCursor startPos;
            startPos.setPosition(m_pjsEditor->document()->characterCount() - 1);
            m_pjsEditor->setTextCursor(startPos);

            if (!Find(QTextDocument::FindBackward))
            {
                CdmMessageManager::information(tr("Keine weiteren Treffer gefunden"), tr("Es wurden keine weiteren Treffer gefunden."));
            }
        }
    }
}

bool CwmsFunctionEditor::Find(QTextDocument::FindFlags flag)
{
    bool bRet = false;
    QTextDocument::FindFlags iConfig = flag;

    if (m_pqchbCaseSensitive->isChecked())
    {
        iConfig = iConfig & QTextDocument::FindCaseSensitively;
    }

    if (m_pqchbWholeWord->isChecked())
    {
        iConfig = iConfig & QTextDocument::FindWholeWords;
    }

    if (m_pqchbRegExp->isChecked())
    {
        bRet = m_pjsEditor->find(QRegExp(m_pqleSearch->text()), iConfig);
    }
    else
    {
        bRet = m_pjsEditor->find(m_pqleSearch->text(), iConfig);
    }

    return bRet;
}

void CwmsFunctionEditor::ReplaceClickedSlot()
{
    if (m_pjsEditor->textCursor().hasSelection() && m_pjsEditor->textCursor().selectedText() == m_pqleSearch->text())
    {
        m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
    }
    else
    {
        if (Find(0))
        {
            m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
        }
    }
}

void CwmsFunctionEditor::ReplaceAllClickedSlot()
{
    int iReplaceCount = 0;
    QTextCursor currentCursor = m_pjsEditor->textCursor();
    QTextCursor startPos;
    startPos.setPosition(0);
    m_pjsEditor->setTextCursor(startPos);

    while (Find(0))
    {
        m_pjsEditor->textCursor().insertText(m_pqleReplace->text());
        ++iReplaceCount;
    }

    CdmMessageManager::information(tr("Ersetzung durchgeführt"), tr("Es wurden ") + QString::number(iReplaceCount) + tr(" Ersetzungen durchgeführt."));
    m_pjsEditor->setTextCursor(currentCursor);
}
