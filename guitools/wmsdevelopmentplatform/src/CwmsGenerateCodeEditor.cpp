/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsGenerateCodeEditor.cpp
 ** Started Implementation: 2011/11/09
 ** Description:
 **
 ** Implements the Configuration ui for generating code
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFileDialog>

// WMS Includes
#include "CdmMessageManager.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsCodeGeneratorC.h"
#include "CwmsCodeGeneratorJ.h"
#include "CwmsGenerateCodeEditor.h"

/** +-=---------------------------------------------------------Mi 9. Nov 19:55:57 2011-----------*
 * @method  CwmsGenerateCodeEditor::CwmsGenerateCodeEditor   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 19:55:57 2011-----------*/
CwmsGenerateCodeEditor::CwmsGenerateCodeEditor(QWidget* p_pqwParent)
: QDialog (p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 9. Nov 19:56:05 2011-----------*
 * @method  CwmsGenerateCodeEditor::~CwmsGenerateCodeEditor  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsGenerateCodeEditor                                        *
 *----------------last changed: --------------------------------Mi 9. Nov 19:56:05 2011-----------*/
CwmsGenerateCodeEditor::~CwmsGenerateCodeEditor()
{
}

/** +-=---------------------------------------------------------Mi 9. Nov 19:56:54 2011-----------*
 * @method  CwmsGenerateCodeEditor::SearchClickedSlot        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 19:56:54 2011-----------*/
void CwmsGenerateCodeEditor::SearchClickedSlot()
{
   QString qstrDirectory = QFileDialog::getExistingDirectory(nullptr, "");
   m_pqleFilename->setText(qstrDirectory);
}

/** +-=---------------------------------------------------------Fr 8. Jun 10:25:52 2012-----------*
 * @method  CwmsGenerateCodeEditor::OKClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 10:25:52 2012-----------*/
void CwmsGenerateCodeEditor::OKClickedSlot()
{
   if (Validate())
   {
      accept();
   }
}

/** +-=---------------------------------------------------------Fr 8. Jun 10:26:13 2012-----------*
 * @method  CwmsGenerateCodeEditor::Validate                 // private                           *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Jun 10:26:13 2012-----------*/
bool CwmsGenerateCodeEditor::Validate()
{
   bool bRet = true;
   if (!m_pqchbGenerateStandardObjectList->isChecked() && 
       m_pqgbWebInterface->isChecked() && 
       m_pqleObjectListKeyname->text() == "")
   {
      bRet = false;
      CdmMessageManager::critical(tr("Fehlende Informationen"), 
         tr("Wenn Sie ein Web Interface erzeugen wollen, muss entweder die Standard Objekliste erzeugt werden oder der Name der Objektliste angegeben werden."));
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 9. Nov 19:57:55 2011-----------*
 * @method  CwmsGenerateCodeEditor::ShowCodeGenerator        // public, static                    *
 * @return  void                                             //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 9. Nov 19:57:55 2011-----------*/
void CwmsGenerateCodeEditor::ShowCodeGenerator(QWidget* p_pqwParent, CdmClass* p_pCdmClass)
{
   CwmsGenerateCodeEditor* pCwmsGenerator = new CwmsGenerateCodeEditor(p_pqwParent);

   if (pCwmsGenerator->exec() == QDialog::Accepted)
   {
      QString qstrFilename = pCwmsGenerator->m_pqleFilename->text() + "/" + pCwmsGenerator->m_pqleClassName->text();

      if (pCwmsGenerator->m_pqchbCplusplusQt->isChecked())
      {
         CwmsCodeGeneratorC cCodeGenerator(p_pCdmClass, pCwmsGenerator->m_pqleClassName->text(), pCwmsGenerator->m_pqleFilename->text());
         cCodeGenerator.AddBaseClassData(pCwmsGenerator->m_pqleBaseClassName->text(), 
            pCwmsGenerator->m_pqleBaseClassFilename->text());

         cCodeGenerator.SetCreateBaseClassMemberFunctions(pCwmsGenerator->m_pqchbGenerateBaseClassMethods->isChecked());
         cCodeGenerator.SetGenerateBusinessLogicCode(pCwmsGenerator->m_pqchbGenerateBLClass->isChecked());
         cCodeGenerator.SetGenerateStandardObjectList(pCwmsGenerator->m_pqchbGenerateStandardObjectList->isChecked());
         cCodeGenerator.SetGenerateTempClassCode(pCwmsGenerator->m_pqchbGenerateTemporaryDataClass->isChecked());
         cCodeGenerator.SetGenerateTestCode(pCwmsGenerator->m_qpchbGenerateTestClass->isChecked());
         cCodeGenerator.SetGenerateWebInterfaceCode(pCwmsGenerator->m_pqgbWebInterface->isChecked());
         cCodeGenerator.SetWebInterfaceClassName(pCwmsGenerator->m_pqleWebIfClassName->text());
         cCodeGenerator.SetWebInterfaceObjectListName(pCwmsGenerator->m_pqleObjectListKeyname->text());
         cCodeGenerator.GenerateCode();
      }
     
      if (pCwmsGenerator->m_pqchbJavaGwt->isChecked())
      {
			CwmsCodeGeneratorJ cCodeGenerator(p_pCdmClass, 
                                           pCwmsGenerator->m_pqleClassName->text(), 
                                           pCwmsGenerator->m_pqlePackage->text(), 
                                           pCwmsGenerator->m_pqleObjectListKeyname->text(), 
                                           pCwmsGenerator->m_pqleFilename->text(), 
                                           pCwmsGenerator->m_pqleBaseClassName->text());
         cCodeGenerator.GenerateCode();
      }
      
      CdmMessageManager::information(tr("Code erzeugt"), 
                               tr("Der Code wurde im Zielverzeichnis erzeugt."));
   }

   DELPTR(pCwmsGenerator);
}