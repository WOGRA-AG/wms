/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: CwmsAddMemberIf.cpp
 ** Started Implementation: 2008/05/22
 ** Description:
 ** 
 ** implements the form for adding and editing members 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <qlineedit.h>
#include <qcombobox.h>
#include <QScriptEngine>
#include <QScriptValue>
#include <qcheckbox.h>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"
#include "CdmLogging.h"
#include "CdmClassGroup.h"
#include "CdmExecutor.h"
#include "CdmExecutorValidator.h"
#include "CdmExecutorPreProcessor.h"
#include "CdmClass.h"
#include "CdmMember.h"

// Own Includes
#include "CwmsTranslationEditorDlg.h"
#include "CwmsAddMemberIf.h"
#include "CwmsUniversalRightsManager.h"
#include "CwmsClassSelectionIf.h"



/** +-=---------------------------------------------------------Di 21. Aug 18:20:16 2012----------*
 * @method  CwmsAddMemberIf::CwmsAddMemberIf                 // public                            *
 * @return                                                   //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Aug 18:20:16 2012----------*/
CwmsAddMemberIf::CwmsAddMemberIf(CdmClass* p_pCdmClass, QWidget* parent)
   : QDialog(parent),
  m_rpCdmMember(nullptr),
  m_rpCdmClass(p_pCdmClass)
{
   setupUi(this);
   m_pqpbRights->hide();
   m_qstrValidationOriginalText = m_pqlValidation->text();
   m_pqcbDataType->clear();
   int iIndex = 0;
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueBool), eDmValueBool);
   m_qmTypeIndexMapper.insert(eDmValueBool, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueLong), eDmValueLong);
   m_qmTypeIndexMapper.insert(eDmValueLong, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDouble), eDmValueDouble);
   m_qmTypeIndexMapper.insert(eDmValueDouble, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueString), eDmValueString);
   m_qmTypeIndexMapper.insert(eDmValueString, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueCounter), eDmValueCounter);
   m_qmTypeIndexMapper.insert(eDmValueCounter, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDate), eDmValueDate);
   m_qmTypeIndexMapper.insert(eDmValueDate, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueTime), eDmValueTime);
   m_qmTypeIndexMapper.insert(eDmValueTime, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDateTime), eDmValueDateTime);
   m_qmTypeIndexMapper.insert(eDmValueDateTime, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueObjectRef), eDmValueObjectRef);
   m_qmTypeIndexMapper.insert(eDmValueObjectRef, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueContainerRef), eDmValueContainerRef);
   m_qmTypeIndexMapper.insert(eDmValueContainerRef, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueBinaryDocument), eDmValueBinaryDocument);
   m_qmTypeIndexMapper.insert(eDmValueBinaryDocument, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueCharacterDocument), eDmValueCharacterDocument);
   m_qmTypeIndexMapper.insert(eDmValueCharacterDocument, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueEnum), eDmValueEnum);
   m_qmTypeIndexMapper.insert(eDmValueEnum, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueListInt), eDmValueListInt);
   m_qmTypeIndexMapper.insert(eDmValueListInt, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueListDouble), eDmValueListDouble);
   m_qmTypeIndexMapper.insert(eDmValueListDouble, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueListString), eDmValueListString);
   m_qmTypeIndexMapper.insert(eDmValueListString, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictStringInt), eDmValueDictStringInt);
   m_qmTypeIndexMapper.insert(eDmValueDictStringInt, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictStringString), eDmValueDictStringString);
   m_qmTypeIndexMapper.insert(eDmValueDictStringString, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictStringDouble), eDmValueDictStringDouble);
   m_qmTypeIndexMapper.insert(eDmValueDictStringDouble, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictIntInt), eDmValueDictIntInt);
   m_qmTypeIndexMapper.insert(eDmValueDictIntInt, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictIntString), eDmValueDictIntString);
   m_qmTypeIndexMapper.insert(eDmValueDictIntString, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueDictIntDouble), eDmValueDictIntDouble);
   m_qmTypeIndexMapper.insert(eDmValueDictIntDouble, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueListObjects), eDmValueListObjects);
   m_qmTypeIndexMapper.insert(eDmValueListObjects, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueFormula), eDmValueFormula);
   m_qmTypeIndexMapper.insert(eDmValueFormula, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueUser), eDmValueUser);
   m_qmTypeIndexMapper.insert(eDmValueUser, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueUserGroup), eDmValueUserGroup);
   m_qmTypeIndexMapper.insert(eDmValueUserGroup, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueInt), eDmValueInt);
   m_qmTypeIndexMapper.insert(eDmValueInt, iIndex++);
   m_pqcbDataType->addItem(CdmMember::GetValueTypeAsString(eDmValueFloat), eDmValueFloat);
   m_qmTypeIndexMapper.insert(eDmValueFloat, iIndex++);
}

/** +-=---------------------------------------------------------Do 22. Mai 21:09:57 2008----------*
 * @method  CwmsAddMemberIf::~CwmsAddMemberIf                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsAddMemberIf                                               *
 *----------------last changed: --------------------------------Do 22. Mai 21:09:57 2008----------*/
CwmsAddMemberIf::~CwmsAddMemberIf()
{
}


/** +-=---------------------------------------------------------Do 22. Mai 21:11:57 2008----------*
 * @method  CwmsAddMemberIf::SetMember                       // public                            *
 * @return  void                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment sets the member to the dialog.                                                        *
 *----------------last changed: --------------------------------Do 22. Mai 21:11:57 2008----------*/
void CwmsAddMemberIf::SetMember(CdmMember* p_pCdmMember)
{
   m_rpCdmMember = p_pCdmMember;

   if (m_rpCdmMember)
   {
      m_pqleKeyname->setText(m_rpCdmMember->GetKeyname());

      m_pqleCaption->setText(m_rpCdmMember->CdmModelElement::GetCaption());
      QString qstrDefault = m_rpCdmMember->GetDefaultValue().toString();
      m_pqleDefault->setText(qstrDefault);
      m_pqteComment->setPlainText(m_rpCdmMember->GetComment());
      m_pqleCounterStart->setText(QString::number(m_rpCdmMember->GetCounterStart()));
      m_pqleCounterStart->setEnabled(false);
      m_pqleSize->setText(QString::number(m_rpCdmMember->GetSize()));
      m_pqchbNeeded->setChecked(m_rpCdmMember->IsMust());
      m_pqchbOwner->setChecked(m_rpCdmMember->IsOwner());
      m_pqchbUnique->setChecked(m_rpCdmMember->IsUnique());
      m_pqteValidation->setPlainText(m_rpCdmMember->GetValidationCode());
      long lClassId = m_rpCdmMember->GetClassReference();
      m_pqchbPersistent->setChecked(m_rpCdmMember->IsPersistent());
      m_pqchbIsTree->setChecked(m_rpCdmMember->IsTree());
      m_pqlePrefix->setText(m_rpCdmMember->GetPrefix());
      m_pqleSuffix->setText(m_rpCdmMember->GetSuffix());
      m_pqsbDecimalCountInput->setValue(m_rpCdmMember->GetDecimalCountInput());
      m_pqsbDecimalCountOutput->setValue(m_rpCdmMember->GetDecimalCountOutput());
      m_pqteEnabledCheck->setPlainText(m_rpCdmMember->GetEnabledCheck());
      m_pqteRenderedCheck->setPlainText(m_rpCdmMember->GetRenderedCheck());
      m_pqleDisplayConfig->setText(m_rpCdmMember->GetDisplayConfig());

      if (lClassId > 0)
      {
         CdmClassManager* pCdmClassManager = p_pCdmMember->GetClassManager();

         if (CHKPTR(pCdmClassManager))
         {
            CdmClass* pCdmClass = pCdmClassManager->FindClassById(lClassId);

            if (pCdmClass)
            {
               m_pqleClassReference->setText(pCdmClass->GetFullQualifiedName());
            }
         }
      }

      EdmValueType eDmValue = m_rpCdmMember->GetValueType();
      m_pqcbDataType->setCurrentIndex(m_qmTypeIndexMapper[eDmValue]);

      if (eDmValue == eDmValueString || eDmValue == eDmValueCharacterDocument)
      {
         m_pqcbDisplayType->setCurrentIndex(m_rpCdmMember->GetClassReference());
      }

      if (eDmValue != eDmValueDouble && eDmValueFloat != eDmValue &&  eDmValueInt != eDmValue && eDmValueLong != eDmValue)
      {
          m_pqgbDoubleFloatGroupBox->hide();
      }

      switch (m_rpCdmMember->GetAccessMode())
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
      default:
         m_pqrbPublic->setChecked(true);
      }

      m_pqchbSystem->setChecked(m_rpCdmMember->IsSystemMember());
      FillTranslations();
      m_pqpbRights->show();
      Init();      
   }
}

/** +-=---------------------------------------------------------Mo 10. Dez 11:46:21 2012----------*
 * @method  CwmsAddMemberIf::Init                            // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Dez 11:46:21 2012----------*/
void CwmsAddMemberIf::Init()
{
   DataTypeSelectionChangedSlot();
   FillGroups();
}

/** +-=---------------------------------------------------------Mi 15. Aug 14:39:13 2012----------*
 * @method  CwmsAddMemberIf::SetSystemValuesReadOnly         // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Aug 14:39:13 2012----------*/
void CwmsAddMemberIf::SetSystemValuesReadOnly()
{
   m_pqwMember->setEnabled(false);
   m_pqwComment->setEnabled(false);
   m_pqwValidation->setEnabled(false);
   m_pqcbDataType->setEnabled(false);
   m_pqcbDisplayType->setEnabled(false);
   m_pqgbDoubleFloatGroupBox->setEnabled(false);
}

/** +-=---------------------------------------------------------Fr 23. Mai 16:39:47 2008----------*
 * @method  CwmsAddMemberIf::ClassSelectionClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to select a class reference.               *
 *----------------last changed: --------------------------------Fr 23. Mai 16:39:47 2008----------*/
void CwmsAddMemberIf::ClassSelectionClickedSlot()
{
   EdmValueType eDmValue = m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex());

   if (eDmValue == eDmValueContainerRef || eDmValue == eDmValueObjectRef || eDmValue == eDmValueListObjects)
   {
      CdmClass* pCdmClass = CwmsClassSelectionIf::GetClass(this);

      if (pCdmClass)
      {
         m_pqleClassReference->setText(pCdmClass->GetFullQualifiedName());
      }
   }
   else
   {
      CdmMessageManager::critical(tr("Fehler beim Datentyp"), 
                            tr("Für diesen Datentyp wird keine Klassenreferenz benötigt.\n"
                               "Diese Funktion steht nur für Objektcontainer, Listen von Objekten und Objektreferenzen zur Verfügung."));
   }
}

/** +-=---------------------------------------------------------Mo 10. Dez 10:49:23 2012----------*
 * @method  CwmsAddMemberIf::OwnerClickedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Dez 10:49:23 2012----------*/
void CwmsAddMemberIf::OwnerClickedSlot()
{
   if (m_pqchbOwner->isChecked() && m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex()) == eDmValueContainerRef)
   {
      m_pqchbIsTree->show();
   }
   else
   {
      m_pqchbIsTree->hide();
   }
}

/** +-=---------------------------------------------------------Do 22. Mai 21:18:04 2008----------*
 * @method  CwmsAddMemberIf::CancelClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Mai 21:18:04 2008----------*/
void CwmsAddMemberIf::CancelClickedSlot()
{
   reject();
}

/** +-=---------------------------------------------------------Do 22. Mai 21:18:20 2008----------*
 * @method  CwmsAddMemberIf::OKClickedSlot                   // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Mai 21:18:20 2008----------*/
void CwmsAddMemberIf::OKClickedSlot()
{
   if (Validate())
   {
      if (SaveData())
      {
         accept();
      }
   }
}

/** +-=---------------------------------------------------------Fr 16. Nov 15:38:12 2012----------*
 * @method  CwmsAddMemberIf::Validate                        // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 16. Nov 15:38:12 2012----------*/
bool CwmsAddMemberIf::Validate()
{
   bool bRet = true;

   if (m_pqleCaption->text().isEmpty())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Pflichtfeldangabe fehlt"), tr("Der Member braucht einen Namen"));
   }

   if (m_pqleKeyname->text().isEmpty())
   {
      bRet = false;
      CdmMessageManager::critical(tr("Pflichtfeldangabe fehlt"), tr("Der Member braucht einen Schlüssel"));
   }
   else
   {
       if (!CdmModelElement::CheckKeyname(m_pqleKeyname->text()))
       {
           bRet = false;
           CdmMessageManager::critical(tr("Schlüsselbezeichnung entspricht nicht den Regeln"),
                                       tr("Schlüsselbezeichnung nicht erlaubt (muss mit einem Buchstaben beginnen und darf keine Umlaute oder Sonderzeichen außer \"_\" enthalten."));
       }
   }

   QString qstrDefault = m_pqleDefault->text();
   bool bConvertSuccess = true;
   EdmValueType eDmValue = m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex());

   if (eDmValue == eDmValueContainerRef || eDmValue == eDmValueObjectRef)
   {
      if (m_pqchbOwner->isChecked() && m_pqleClassReference->text().isEmpty())
      {
         bRet = false;
         CdmMessageManager::critical(tr("Pflichtfeldangabe fehlt"), 
            tr("Wenn einer Referenz als Owner gekennzeichnet wird, muss eine Klassenreferenz ausgewählt werden!"));
      }
      else if (m_pqchbOwner->isChecked())
      {
         QString qstrClass = m_pqleClassReference->text();

         CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

         if (pManager)
         {
            CdmClassManager* pClassManager = pManager->GetClassManager();

            if (pClassManager)
            {
               CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

               if (pClass && pClass->IsAbstract())
               {
                  bRet = false;
                  CdmMessageManager::critical(tr("Abstrakte Klasse nicht erlaubt"), 
                     tr("Wenn das Besitzerflag gesetzt ist, darf keine Abstrakte Klasse gewählt werden."));
               }
               else if (!pClass)
               {
                  bRet = false;
                  CdmMessageManager::critical(tr("Pflichtfeldangabe fehlt"), 
                     tr("Wenn einer Referenz als Owner gekennzeichnet wird, muss eine Klassenreferenz ausgewählt werden! Die Klasse ist unbekannt."));
               }
            }
         }
      }

      if (!qstrDefault.isEmpty())
      {
          ERR(tr("Für diesen Datentyp gibt es keine Standardwerte"));
      }
   }
   else if (eDmValue == eDmValueEnum && !qstrDefault.isEmpty())
   {
       QString qstrEnum = m_pqteValidation->toPlainText();
       qstrEnum = qstrEnum.simplified();
       QStringList qstrlEntries = qstrEnum.split(",");

       for (int i = 0; i < qstrlEntries.count(); ++i)
       {
           QString qstrEntry = qstrlEntries[i];
           if (qstrlEntries.count(qstrEntry) > 1)
           {
               ERR(tr("Auswahlliste enthält doppelte Einträge. Eintrag: ") + qstrEntry);
               bRet = false;
               break;
           }
       }

       if (bRet)
       {
            int iValue = qstrDefault.toInt(&bConvertSuccess);
            if (bConvertSuccess)
            {
                if (iValue >= qstrlEntries.count())
                {
                    ERR(tr("Der Standardwert muss zwischen 0 und %1 sein").arg(qstrlEntries.count() - 1));
                    bRet = false;
                }
            }
            else
            {
                ERR(tr("Der Standardwert muss zwischen 0 und %1 sein").arg(qstrlEntries.count() - 1));
                bRet = false;
            }
        }
   }
   else if ((eDmValue == eDmValueInt ||
            eDmValue == eDmValueLong ||
            eDmValue == eDmValueCounter ||
            eDmValue == eDmValueUser ||
            eDmValue == eDmValueUserGroup) && !qstrDefault.isEmpty())
   {
       qstrDefault.toInt(&bConvertSuccess);

       if (!bConvertSuccess)
       {
           if (!qstrDefault.startsWith("${"))
           {
               if (eDmValue == eDmValueUser ||
                   eDmValue == eDmValueUserGroup)
               {
                   ERR(tr("Der Standardwert muss eine Benutzer oder Gruppen ID sein"));
               }
               else
               {
                    ERR(tr("Der Standardwert muss eine ID (BenutzerId oder BenutzergruppenId) sein."));
               }

                bRet = false;
           }
       }
   }
   else if ((eDmValue == eDmValueDouble ||
            eDmValue == eDmValueDimDouble ||
            eDmValue == eDmValueFloat) && !qstrDefault.isEmpty())
   {
       qstrDefault.toDouble(&bConvertSuccess);

       if (!bConvertSuccess)
       {
           if (!qstrDefault.startsWith("${"))
           {
                ERR(tr("Der Standardwert muss eine Fließkommazahl sein"));
                bRet = false;
           }
       }
   }
   else if ((eDmValue == eDmValueBinaryDocument ||
            eDmValue == eDmValueDictIntDouble ||
            eDmValue == eDmValueDictIntString ||
            eDmValue == eDmValueDictIntInt ||
            eDmValue == eDmValueDictStringDouble ||
            eDmValue == eDmValueDictStringInt ||
            eDmValue == eDmValueDictStringString ||
            eDmValue == eDmValueListDouble ||
            eDmValue == eDmValueListInt ||
            eDmValue == eDmValueListString ||
            eDmValue == eDmValueListObjects ||
            eDmValue == eDmValueFormula) && !qstrDefault.isEmpty())
   {
        if (!qstrDefault.isEmpty())
        {
            ERR(tr("Für diesen Datentyp gibt es keine Standardwerte"));
            bRet = false;
        }
   }
   else if (eDmValue == eDmValueBool && !qstrDefault.isEmpty())
   {
       if (qstrDefault != "true" && qstrDefault != "false")
       {
           ERR(tr("Der Standardwert für einen Bool kann nur \"true\" oder \"false\" sein"));
           bRet = false;
       }
   }
   else if (eDmValue == eDmValueDate && !qstrDefault.isEmpty())
   {
       if (!QDate::fromString(qstrDefault).isValid())
       {
           if (!qstrDefault.startsWith("${"))
           {
                ERR(tr("Der Standardwert für ein Datum muss im ISO Format angegeben werden."));
                   bRet = false;
           }
       }
   }
   else if (eDmValue == eDmValueDateTime && !qstrDefault.isEmpty())
   {
       if (!QDateTime::fromString(qstrDefault).isValid())
       {
           if (!qstrDefault.startsWith("${"))
           {
                ERR(tr("Der Standardwert für einen Zeitstempel muss im ISO Format angegeben werden."));
                bRet = false;
           }
       }
   }
   else if (eDmValue == eDmValueTime && !qstrDefault.isEmpty())
   {
       if (!QTime::fromString(qstrDefault).isValid())
       {
           if (!qstrDefault.startsWith("${"))
           {
                ERR(tr("Der Standardwert für eine Uhrzeit muss im ISO Format angegeben werden."));
                bRet = false;
           }
       }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 16. Nov 15:38:36 2012----------*
 * @method  CwmsAddMemberIf::SaveData                        // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 16. Nov 15:38:36 2012----------*/
bool CwmsAddMemberIf::SaveData()
{
   bool bRet = false;

   if (m_rpCdmClass)
   {
      EdmValueType eDmValue = m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex());

      if (!m_rpCdmMember)
      {
         m_rpCdmMember = m_rpCdmClass->CreateMember(m_pqleKeyname->text(), 
            eDmValue, 
            m_pqchbNeeded->isChecked(), 
            m_pqleSize->text().toInt());
      }
      else
      {
         m_rpCdmMember->SetValueType(eDmValue);
         m_rpCdmMember->SetKeyname(m_pqleKeyname->text());
      }

      if (m_rpCdmMember)
      {
          m_rpCdmMember->SetComment(m_pqteComment->toPlainText());
          m_rpCdmMember->SetCounterStart(m_pqleCounterStart->text().toInt());
          m_rpCdmMember->SetDefaultValue(m_pqleDefault->text());
          m_rpCdmMember->SetCaption(m_pqleCaption->text());
          m_rpCdmMember->SetSize(m_pqleSize->text().toInt());
          m_rpCdmMember->SetUnique(m_pqchbUnique->isChecked());
          m_rpCdmMember->SetOwner(m_pqchbOwner->isChecked());
          m_rpCdmMember->SetMustValue(m_pqchbNeeded->isChecked());
          m_rpCdmMember->SetValidationCode(m_pqteValidation->toPlainText());
          m_rpCdmMember->SetPersistent(m_pqchbPersistent->isChecked());
          m_rpCdmMember->SetTree(m_pqchbIsTree->isChecked());
          m_rpCdmMember->SetDecimalCountInput(m_pqsbDecimalCountInput->value());
          m_rpCdmMember->SetDecimalCountOutput(m_pqsbDecimalCountOutput->value());
          m_rpCdmMember->SetPrefix(m_pqlePrefix->text());
          m_rpCdmMember->SetSuffix(m_pqleSuffix->text());
          m_rpCdmMember->SetRenderedCheck(m_pqteRenderedCheck->toPlainText());
          m_rpCdmMember->SetEnabledCheck(m_pqteEnabledCheck->toPlainText());
          m_rpCdmMember->SetDisplayConfig(m_pqleDisplayConfig->text());

          if (eDmValue == eDmValueString || eDmValue == eDmValueCharacterDocument)
          {
             m_rpCdmMember->SetClassReference(m_pqcbDisplayType->currentIndex());
          }

          m_rpCdmMember->SetSystemFlag(m_pqchbSystem->isChecked());

          if (m_pqrbPublic->isChecked())
          {
             m_rpCdmMember->SetMemberAccess(eDmMemberAccessPublic);
          }
          else if (m_pqrbProtected->isChecked())
          {
             m_rpCdmMember->SetMemberAccess(eDmMemberAccessProtected);
          }
          else if (m_pqrbPrivate->isChecked())
          {
             m_rpCdmMember->SetMemberAccess(eDmMemberAccessPrivate);
          }

          QString qstrReferenceClass = m_pqleClassReference->text();

          if (!qstrReferenceClass.isEmpty())
          {
             CdmClassManager* pCdmClassManager = m_rpCdmMember->GetClassManager();

             if (CHKPTR(pCdmClassManager))
             {
                CdmClass* pCdmClass = pCdmClassManager->FindClassByKeyname(qstrReferenceClass);

                if (CHKPTR(pCdmClass))
                {
                   m_rpCdmMember->SetClassReference(pCdmClass->GetId());
                }
             }
          }

          int iCurrentIndex = m_pqcbGroup->currentIndex();
          int iGroupId = m_pqcbGroup->itemData(iCurrentIndex).toInt();

          if (iGroupId >= 0)
          {
             m_rpCdmMember->SetGroup(m_rpCdmClass->FindGroupById(iGroupId));
          }

          if (m_rpCdmMember->IsModified())
          {
             m_rpCdmClass->SetModified();
          }

          bRet = m_rpCdmClass->Commit();
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 15. Aug 14:17:37 2012----------*
 * @method  CwmsAddMemberIf::TestValidationClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Aug 14:17:37 2012----------*/
void CwmsAddMemberIf::TestValidationClickedSlot()
{
   QString qstrTag = "value";
   QString qstrCode = m_pqteValidation->toPlainText();
   QScriptEngine qEngine;
   QString qstrValidation = qstrCode;
   QString qstrInput = 
      CdmMessageManager::AskForInputText(tr("Bitte Testwert eingeben"), 
                                         tr("Bitte geben Sie den Wert für den Test ein"));
   QVariant qvValue(qstrInput);

   switch (m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex()))
   {
   case eDmValueBool:
      qEngine.globalObject().setProperty(qstrTag, qvValue.toBool());
      break;
   case eDmValueInt:
   case eDmValueLong:
   case eDmValueCounter:
   case eDmValueEnum:
      qEngine.globalObject().setProperty(qstrTag, qvValue.toInt());
      break;
   case eDmValueFloat:
   case eDmValueDouble:
      qEngine.globalObject().setProperty(qstrTag, qvValue.toDouble());
      break;
   case eDmValueString:
   case eDmValueCharacterDocument:
      qEngine.globalObject().setProperty(qstrTag, qvValue.toString());
      break;
   case eDmValueDate:
      qEngine.globalObject().setProperty(qstrTag, qEngine.newDate(qvValue.toDateTime()));
      break;
   case eDmValueDateTime:
      qEngine.globalObject().setProperty(qstrTag, qEngine.newDate(qvValue.toDateTime()));
      break;
   case eDmValueTime:
      qEngine.globalObject().setProperty(qstrTag, qEngine.newDate(qvValue.toDateTime()));
      break;
   default:
      ERR("Unknown type for parameter");
   }

   QScriptValue qScriptValue = qEngine.evaluate(qstrValidation);

   if (qEngine.hasUncaughtException()) 
   {
      int line = qEngine.uncaughtExceptionLineNumber();
      CdmMessageManager::critical(tr("Fehler im Validierungscode des Members "), 
         tr("In Zeile ") + QString::number(line)+ "\n" + qScriptValue.toString());
   }
   else
   {
      bool bRet = qScriptValue.toBool();

      if (!bRet)
      {
         CdmMessageManager::critical(tr("Validierung fehlgeschlagen "), 
                                     tr("Die Eingabeprüfung schlug fehl. Prüfung:\n") + qstrCode);
      }
      else
      {
         CdmMessageManager::information(tr("Validierung erfolgreich"), 
                                        tr("Die Validierung war erfolgreich!"));
      }
   }
}

/** +-=---------------------------------------------------------Mi 15. Aug 14:18:01 2012----------*
 * @method  CwmsAddMemberIf::DataTypeSelectionChangedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 15. Aug 14:18:01 2012----------*/
void CwmsAddMemberIf::DataTypeSelectionChangedSlot()
{
   tabWidget->setTabText(2, tr("Validierung"));
   m_pqgbValidation->setTitle(tr("Validierung"));
   m_pqlValidation->show();
   m_pqlValidation->setText(m_qstrValidationOriginalText);

   EdmValueType eDmValue = m_qmTypeIndexMapper.key(m_pqcbDataType->currentIndex());

   switch (eDmValue)
   {
   case eDmValueListObjects:
      // to show
      m_pqleClassReference->show();
      m_pqlRefClass->show();
      m_pqpbChooseClass->show();
      
      // to hide
      m_pqchbNeeded->hide();
      m_pqchbUnique->hide();
      m_pqchbOwner->hide();
      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqgbDoubleFloatGroupBox->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      break;
   case eDmValueContainerRef:
   case eDmValueObjectRef:
      // to show
      m_pqleClassReference->show();
      m_pqlRefClass->show();
      m_pqpbChooseClass->show();
      m_pqchbOwner->show();
      m_pqchbNeeded->show();
      m_pqchbUnique->show();


      // to hide
      m_pqgbDoubleFloatGroupBox->hide();
      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      break;
   case eDmValueString:
      // to show
      m_pqlDisplayType->show();
      m_pqcbDisplayType->show();
      m_pqleSize->show();
      m_pqlSize->show();
      m_pqleDefault->show();
      m_pqlDefault->show();
      m_pqchbNeeded->show();
      m_pqchbUnique->show();

      // to hide
      m_pqgbDoubleFloatGroupBox->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      break;
   case eDmValueCharacterDocument:
      // to show
      m_pqleSize->show();
      m_pqlSize->show();
      m_pqleDefault->show();
      m_pqlDefault->show();
      m_pqchbNeeded->show();
      m_pqchbUnique->show();
      m_pqcbDisplayType->show();

      // to hide
      m_pqgbDoubleFloatGroupBox->hide();
      m_pqlDisplayType->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      break;
   case eDmValueCounter:
      // to show
      m_pqleCounterStart->show();
      m_pqlCounterStart->show();

      // to hide
      m_pqgbDoubleFloatGroupBox->hide();
      m_pqchbUnique->hide();
      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      m_pqchbNeeded->hide();
      break;

   case eDmValueListInt:
   case eDmValueListDouble:
   case eDmValueListString:
   case eDmValueDictIntDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
      // to hide
       m_pqgbDoubleFloatGroupBox->hide();
       m_pqchbUnique->hide();
      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      m_pqchbNeeded->hide();
      break;
   case eDmValueFormula:
      // rename Validation to Formular
      // ... todo
      tabWidget->setTabText(2, tr("Formel"));
      m_pqgbValidation->setTitle(tr("Formel"));
      m_pqlValidation->setText(tr("Bitte Formel hier eintragen."));
      

      // to hide
      m_pqgbDoubleFloatGroupBox->hide();
       m_pqchbUnique->hide();
      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      m_pqchbNeeded->hide();
      break;
   case eDmValueEnum:
      // rename Validation to Enum
      tabWidget->setTabText(2, tr("Auflistung"));
      m_pqgbValidation->setTitle(tr("Auflistung"));
      m_pqlValidation->setText("Bitte die Auswahlwerte Kommagetrennt aufführen.");
       m_pqchbUnique->show();


      // to hide
       m_pqgbDoubleFloatGroupBox->hide();

      m_pqlDisplayType->hide();
      m_pqcbDisplayType->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      m_pqleDefault->hide();
      m_pqlDefault->hide();
      m_pqchbNeeded->hide();
      break;
   case eDmValueFloat:
   case eDmValueDouble:
   case eDmValueInt:
   case eDmValueLong:
       // to show
       m_pqleDefault->show();
       m_pqlDefault->show();
       m_pqchbNeeded->show();
       m_pqchbUnique->show();
       m_pqgbDoubleFloatGroupBox->show();

       // to hide
        m_pqlDisplayType->hide();
        m_pqcbDisplayType->hide();
       m_pqleCounterStart->hide();
       m_pqlCounterStart->hide();
       m_pqleSize->hide();
       m_pqlSize->hide();
       m_pqleClassReference->hide();
       m_pqlRefClass->hide();
       m_pqpbChooseClass->hide();
       m_pqchbOwner->hide();
       break;
   default:
      // to show
      m_pqleDefault->show();
      m_pqlDefault->show();
      m_pqchbNeeded->show();
       m_pqchbUnique->show();

      // to hide
       m_pqgbDoubleFloatGroupBox->hide();
       m_pqlDisplayType->hide();
       m_pqcbDisplayType->hide();
      m_pqleCounterStart->hide();
      m_pqlCounterStart->hide();
      m_pqleSize->hide();
      m_pqlSize->hide();
      m_pqleClassReference->hide();
      m_pqlRefClass->hide();
      m_pqpbChooseClass->hide();
      m_pqchbOwner->hide();
      break;
   }
}

/** +-=---------------------------------------------------------Do 16. Aug 14:54:15 2012----------*
 * @method  CwmsAddMemberIf::RightsClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 16. Aug 14:54:15 2012----------*/
void CwmsAddMemberIf::RightsClickedSlot()
{
   if (m_rpCdmMember)
   {
      CdmRights* pCdmRights = &m_rpCdmMember->GetRights();
      CwmsUniversalRightsManagerIf* pCwmsRighstManager = new CwmsUniversalRightsManagerIf(pCdmRights, this);
      pCwmsRighstManager->exec();
      DELPTR(pCwmsRighstManager);
      m_rpCdmClass->Commit();
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 10:52:47 2012----------*
 * @method  CwmsAddMemberIf::NewTranslationClickedSlot       // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 10:52:47 2012----------*/
void CwmsAddMemberIf::NewTranslationClickedSlot()
{
   CwmsTranslationEditorDlg* pEditor = new CwmsTranslationEditorDlg(this);
   pEditor->FillDialog();
   if (pEditor->exec() == QDialog::Accepted)
   {
       if (!m_rpCdmMember)
       {
           m_rpCdmMember = m_rpCdmClass->CreateMember("Test", eDmValueBool, false, 0);
       }

       if (CHKPTR(m_rpCdmMember))
       {
            m_rpCdmMember->SetTranslation(pEditor->GetLanguage(),
                                          pEditor->GetTranslation(),
                                          pEditor->GetComment());
       }
   }

   DELPTR(pEditor);
   FillTranslations();
}

/** +-=---------------------------------------------------------Mo 20. Aug 10:52:31 2012----------*
 * @method  CwmsAddMemberIf::EditTranslationClickedSlot      // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 10:52:31 2012----------*/
void CwmsAddMemberIf::EditTranslationClickedSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedTranslationItem();

   if (pqItem)
   {
      pqItem->text(0);
      pqItem->text(1);
      pqItem->text(2);
      QString iId = pqItem->data(0, Qt::UserRole).toString();

      CwmsTranslationEditorDlg* pEditor = new CwmsTranslationEditorDlg(this);
      pEditor->FillDialog(iId, pqItem->text(1), pqItem->text(2));

      if (pEditor->exec() == QDialog::Accepted)
      {
         m_rpCdmMember->DeleteTranslation(iId);
         m_rpCdmMember->SetTranslation(pEditor->GetLanguage(), pEditor->GetTranslation(), pEditor->GetComment());
      }
      
      DELPTR(pEditor);
      FillTranslations();
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 10:53:00 2012----------*
 * @method  CwmsAddMemberIf::DeleteTranslationClickedSlot    // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 10:53:00 2012----------*/
void CwmsAddMemberIf::DeleteTranslationClickedSlot()
{
   QTreeWidgetItem* pqItem = GetSelectedTranslationItem();

   if (pqItem)
   {
      QString iId = pqItem->data(0, Qt::UserRole).toString();
      m_rpCdmMember->DeleteTranslation(iId);
      DELPTR(pqItem);
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 10:53:11 2012----------*
 * @method  CwmsAddMemberIf::FillTranslations                // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 10:53:11 2012----------*/
void CwmsAddMemberIf::FillTranslations()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmScheme* pCdmDatabase = pCdmManager->GetCurrentScheme();
   
      if ( CHKPTR(pCdmDatabase) && m_rpCdmMember)
      {
         m_pqtwTranslations->clear();
         QMap<QString, StringPair>& qmTranslations = m_rpCdmMember->GetTranslations();

         if (qmTranslations.count() > 0)
         {
            QMap<QString, StringPair>::iterator qmIt = qmTranslations.begin();
            QMap<QString, StringPair>::iterator qmItEnd = qmTranslations.end();
           

            for (; qmIt != qmItEnd; ++qmIt)
            {
               StringPair qPair = qmIt.value();
               
               QTreeWidgetItem* pqItem = new QTreeWidgetItem(m_pqtwTranslations);
               pqItem->setText(0, qmIt.key());
               pqItem->setText(1, qPair.first);
               pqItem->setText(2, qPair.second);
               pqItem->setData(0, Qt::UserRole, QVariant(qmIt.key()));
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 20. Aug 13:10:56 2012----------*
 * @method  CwmsAddMemberIf::GetSelectedTranslationItem      // private                           *
 * @return  QTreeWidgetItem*                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 20. Aug 13:10:56 2012----------*/
QTreeWidgetItem* CwmsAddMemberIf::GetSelectedTranslationItem()
{
   QTreeWidgetItem* pItem = nullptr;
   QList<QTreeWidgetItem*> qlItems = m_pqtwTranslations->selectedItems();

   if (qlItems.count() > 0)
   {
      pItem = qlItems[0];
   }

   return pItem;
}

/** +-=---------------------------------------------------------Di 21. Aug 17:54:53 2012----------*
 * @method  CwmsAddMemberIf::FillGroups                      // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Aug 17:54:53 2012----------*/
void CwmsAddMemberIf::FillGroups()
{
   QMap<int, CdmClassGroup*> qmGroups = m_rpCdmClass->GetClassGroups();
   QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
   QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

   m_pqcbGroup->addItem(tr("Keine"), QVariant(-1));

   for (; qmIt != qmItEnd; ++qmIt)
   {
      CdmClassGroup* pCdmGroup = qmIt.value();

      if (CHKPTR(pCdmGroup))
      {
         m_pqcbGroup->addItem(pCdmGroup->GetName(), QVariant(pCdmGroup->GetId()));
      }
   }

   if (m_rpCdmMember && m_rpCdmMember->GetGroup())
   {
      m_pqcbGroup->setCurrentIndex(m_pqcbGroup->findData((m_rpCdmMember->GetGroup()->GetId())));
   }
}
