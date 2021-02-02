/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsObjectContainerDataFiller.h
 ** Started Implementation: 2013/09/18
 ** Description:
 **
 ** implements the ui for creating new objectlists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/


// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "CdmDataProvider.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"

// own Includes
#include "CwmsClassSelectionIf.h"
#include "CwmsCreateobjectContainerDlg.h"

/** +-=---------------------------------------------------------Mo 23. Sep 19:39:38 2013----------*
 * @method  CwmsCreateObjectContainerDlg::CwmsCreateObjectContainerDlg // public                  *
 * @return                                                   //                                   *
 * @param   QWidget* p_pParent                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 19:39:38 2013----------*/
CwmsCreateObjectContainerDlg::CwmsCreateObjectContainerDlg(QWidget* p_pParent)
    : QDialog(p_pParent),
      m_rpClass(nullptr)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------Mo 23. Sep 19:39:57 2013----------*
 * @method  CwmsCreateObjectContainerDlg::~CwmsCreateObjectContainerDlg // public, virtual        *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCreateObjectContainerDlg                                  *
 *----------------last changed: --------------------------------Mo 23. Sep 19:39:57 2013----------*/
CwmsCreateObjectContainerDlg::~CwmsCreateObjectContainerDlg()
{
}

/** +-=---------------------------------------------------------Mo 23. Sep 19:40:19 2013----------*
 * @method  CwmsCreateObjectContainerDlg::SelectClassClickedSlot // private, slots                *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 19:40:19 2013----------*/
void CwmsCreateObjectContainerDlg::SelectClassClickedSlot()
{
    m_rpClass = CwmsClassSelectionIf::GetClass(this);

    if (m_rpClass)
    {
        m_pqleClass->setText(m_rpClass->GetKeyname());
    }
}

void CwmsCreateObjectContainerDlg::OKClickedSlot()
{
    QString qstrKeyname = m_pqleKeyname->text();
    QString qstrCaption = m_pqleCaption->text();
    QString qstrComment = m_pqteComment->toPlainText();

    if (!qstrKeyname.isEmpty() && !qstrCaption.isEmpty() && !qstrComment.isEmpty() && m_rpClass)
    {
        if (CdmModelElement::CheckKeyname(qstrKeyname))
        {
            accept();
        }
        else
        {
            CdmMessageManager::critical(tr("Schlüsselbezeichnung entspricht nicht den Regeln"),
                                        tr("Schlüsselbezeichnung nicht erlaubt (muss mit einem Buchstaben beginnen und darf keine Umlaute oder Sonderzeichen außer \"_\" enthalten."));
        }
    }
    else
    {
        CdmMessageManager::information(tr("Objektcontainer konnte nicht angelegt werden"),
                                       tr("Keyname, Caption, Klasse und Comment sind Pflichtfelder"));

    }
}

/** +-=---------------------------------------------------------Mo 23. Sep 19:34:02 2013----------*
 * @method  CwmsCreateObjectContainerDlg::CreateObjectContainer // public, static                 *
 * @return  CdmObjectContainer*                              //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Sep 19:34:02 2013----------*/
CdmObjectContainer* CwmsCreateObjectContainerDlg::CreateObjectContainer(QWidget* p_pqwParent)
{
    CdmObjectContainer*  pContainer = nullptr;
    CwmsCreateObjectContainerDlg dialog(p_pqwParent);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString qstrKeyname = dialog.m_pqleKeyname->text();
        QString qstrCaption = dialog.m_pqleCaption->text();
        QString qstrComment = dialog.m_pqteComment->toPlainText();
        CdmClass* pClass = dialog.m_rpClass;

        if (!qstrKeyname.isEmpty() && !qstrCaption.isEmpty() && !qstrComment.isEmpty() && pClass)
        {
            if (CdmModelElement::CheckKeyname(qstrKeyname))
            {
                CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();
                if (CHKPTR(pManager))
                {
                    CdmContainerManager* pContainerManager = pManager->GetContainerManager();
                    if (pContainerManager->CreateContainer(pClass, qstrKeyname) > 0)
                    {
                        pContainer = pContainerManager->FindContainerByKeyname(qstrKeyname);

                        if (CHKPTR(pContainer))
                        {
                            pContainer->SetCaption(qstrCaption);
                            pContainer->SetComment(qstrComment);
                            pContainer->Commit();
                        }
                    }
                    else
                    {
                        CdmMessageManager::information(tr("Objektcontainer konnte nicht angelegt werden"),
                                                       tr("Die Objektcontainer konnte nicht angelegt werden (Interner Fehler)."));
                    }
                }
            }
            else
            {
                CdmMessageManager::critical(tr("Schlüsselbezeichnung entspricht nicht den Regeln"),
                                            tr("Schlüsselbezeichnung nicht erlaubt (muss mit einem Buchstaben beginnen und darf keine Umlaute oder Sonderzeichen außer \"_\" enthalten."));
            }
        }
        else
        {
            CdmMessageManager::information(tr("Objektcontainer konnte nicht angelegt werden"),
                                           tr("Keyname, Caption, Klasse und Comment sind Pflichtfelder"));

        }
    }

    return pContainer;
}
