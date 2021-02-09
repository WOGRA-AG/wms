/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsHelp.cpp
 ** Started Implementation: 2012/09/05
 ** Description:
 **
 **  implements a simple help viewer
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CwmsHelp.h"

CwmsHelp::CwmsHelp(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

CwmsHelp::~CwmsHelp()
{
}

void CwmsHelp::ShowTextHelp(QString p_qstrHelp, QWidget* p_pqwParent)
{
   CwmsHelp* pHelp = new CwmsHelp(p_pqwParent);
   pHelp->m_pqtbContent->setPlainText(p_qstrHelp);
   pHelp->exec();
   DELPTR(pHelp);
}

void CwmsHelp::ShowHtmlHelp(QString p_qstrHelp, QWidget* p_pqwParent)
{
   CwmsHelp* pHelp = new CwmsHelp(p_pqwParent);
   pHelp->m_pqtbContent->setHtml(p_qstrHelp);
   pHelp->exec();
   DELPTR(pHelp);
}

void CwmsHelp::ShowLicence(QString p_qstrHelp, QWidget* p_pqwParent)
{
   CwmsHelp* pHelp = new CwmsHelp(p_pqwParent);
   pHelp->setWindowTitle(tr("Lizenzinformationen"));
   pHelp->m_pqtbContent->setHtml(p_qstrHelp);
   pHelp->exec();
   DELPTR(pHelp);
}
