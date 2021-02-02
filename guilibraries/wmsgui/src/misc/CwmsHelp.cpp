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

/** +-=---------------------------------------------------------Mi 5. Sep 11:48:11 2012-----------*
 * @method  CwmsHelp::CwmsHelp                               // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 11:48:11 2012-----------*/
CwmsHelp::CwmsHelp(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 5. Sep 11:49:20 2012-----------*
 * @method  CwmsHelp::~CwmsHelp                              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsHelp                                                      *
 *----------------last changed: --------------------------------Mi 5. Sep 11:49:20 2012-----------*/
CwmsHelp::~CwmsHelp()
{
}

/** +-=---------------------------------------------------------Mi 5. Sep 11:49:44 2012-----------*
 * @method  CwmsHelp::ShowHelp                               // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrHelp                               //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 11:49:44 2012-----------*/
void CwmsHelp::ShowHelp(QString p_qstrHelp, QWidget* p_pqwParent)
{
   CwmsHelp* pHelp = new CwmsHelp(p_pqwParent);
   pHelp->m_pqtbContent->setHtml(p_qstrHelp);
   pHelp->exec();
   DELPTR(pHelp);
}

/** +-=---------------------------------------------------------Mi 5. Sep 11:50:50 2012-----------*
 * @method  CwmsHelp::ShowLicence                            // public, static                    *
 * @return  void                                             //                                   *
 * @param   QString p_qstrHelp                               //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 11:50:50 2012-----------*/
void CwmsHelp::ShowLicence(QString p_qstrHelp, QWidget* p_pqwParent)
{
   CwmsHelp* pHelp = new CwmsHelp(p_pqwParent);
   pHelp->setWindowTitle(tr("Lizenzinformationen"));
   pHelp->m_pqtbContent->setHtml(p_qstrHelp);
   pHelp->exec();
   DELPTR(pHelp);
}