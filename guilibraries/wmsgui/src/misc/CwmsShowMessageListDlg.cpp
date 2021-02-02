/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsShowMessageListDlg.cpp
 ** Started Implementation: 2013/02/08
 ** Description:
 **
 ** implements the ui for displaying message lists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QTextStream>

// WMS Core Includes
#include "CdmLogging.h"
#include "CdmMessageManager.h"
#include "basetools.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsShowMessageListDlg.h"

/** +-=---------------------------------------------------------Fr 8. Feb 15:16:44 2013-----------*
 * @method  CwmsShowMessageListDlg::CwmsShowMessageListDlg   // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:16:44 2013-----------*/
CwmsShowMessageListDlg::CwmsShowMessageListDlg(QWidget* p_pqwParent)
    : WMS_BASE_QT_STANDARD_DIALOG
{
    BODY_TRY
    setupUi(this);
    BODY_CATCH
}

/** +-=---------------------------------------------------------Fr 8. Feb 15:17:07 2013-----------*
 * @method  CwmsShowMessageListDlg::~CwmsShowMessageListDlg  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsShowMessageListDlg                                        *
 *----------------last changed: --------------------------------Fr 8. Feb 15:17:07 2013-----------*/
CwmsShowMessageListDlg::~CwmsShowMessageListDlg()
{
    // Nothing to be done here
}

/** +-=---------------------------------------------------------Fr 8. Feb 15:21:25 2013-----------*
 * @method  CwmsShowMessageListDlg::FillDialog               // private                           *
 * @return  void                                             //                                   *
 * @param   QStringList m_qstrlMessage                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:21:25 2013-----------*/
void CwmsShowMessageListDlg::FillDialog(QStringList m_qstrlMessage)
{
    BODY_TRY
    m_qstrMessages = QString();

    for (int iCounter = 0; iCounter < m_qstrlMessage.count(); ++iCounter)
    {
        QString qstrLine = m_qstrlMessage[iCounter];

        QStringList qstrlContent = qstrLine.split("|", QString::SkipEmptyParts);

        if (qstrlContent.count() == 3)
        {
            QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pqtwEvents);
            pItem->setText(0, qstrlContent[0]);
            m_qstrMessages += qstrlContent[0] + ";";
            pItem->setText(1, qstrlContent[1]);
            m_qstrMessages += qstrlContent[1] + ";";
            pItem->setText(2, qstrlContent[2]);
            m_qstrMessages += qstrlContent[2] + ";";
            m_qstrMessages += "\n";
        }
    }

    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwEvents);
    BODY_CATCH
}

void CwmsShowMessageListDlg::SaveClickedSlot()
{
    BODY_TRY
    QString qstrFile = CdmMessageManager::GetSaveFile(tr("Bitte Dateiname und Speicherort angeben"));
    QFile qFile(qstrFile);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream qStream(&qFile);
        qStream << m_qstrMessages;
    }
    BODY_CATCH
}

/** +-=---------------------------------------------------------Fr 8. Feb 15:25:33 2013-----------*
 * @method  CwmsShowMessageListDlg::ShowMessages             // public, static                    *
 * @return  void                                             //                                   *
 * @param   QStringList p_qstrlMessages                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 8. Feb 15:25:33 2013-----------*/
void CwmsShowMessageListDlg::ShowMessages(QStringList p_qstrlMessages, QWidget* p_pqwParent)
{
    BODY_TRY
    CwmsShowMessageListDlg cDlg(p_pqwParent);
    cDlg.FillDialog(p_qstrlMessages);
    cDlg.exec();
    BODY_CATCH
}
