/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsAboutDlg.cpp
 ** Started Implementation: 2012/09/05
 ** Description:
 **
 ** implements the about dlg for displaying in apps
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QApplication>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsHelp.h"
#include "CwmsRuntime.h"
#include "CwmsAboutDlg.h"

/** +-=---------------------------------------------------------Mi 5. Sep 10:46:26 2012-----------*
 * @method  CwmsAboutDlg::CwmsAboutDlg                       // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 10:46:26 2012-----------*/
CwmsAboutDlg::CwmsAboutDlg(QWidget* p_pqwParent)
: QDialog(p_pqwParent)
{
   setupUi(this);
}

/** +-=---------------------------------------------------------Mi 5. Sep 10:46:34 2012-----------*
 * @method  CwmsAboutDlg::~CwmsAboutDlg                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsAboutDlg                                                  *
 *----------------last changed: --------------------------------Mi 5. Sep 10:46:34 2012-----------*/
CwmsAboutDlg::~CwmsAboutDlg()
{
}

/** +-=---------------------------------------------------------Mi 5. Sep 10:51:15 2012-----------*
 * @method  CwmsAboutDlg::FillDialog                         // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplication p_cApp                           //                                   *
 * @param   CwmsRuntime* p_pCwmsRuntime                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 10:51:15 2012-----------*/
void CwmsAboutDlg::FillDialog(CwmsApplication p_cApp, CwmsRuntime* p_pCwmsRuntime)
{
   if (p_cApp.IsValid())
   {
      m_pqleAppName->setText(p_cApp.GetName());
      QString qstrVersion = QString::number(p_cApp.GetVersionMajor()) + "." + QString::number(p_cApp.GetVersionMinor()) + "." + QString::number(p_cApp.GetVersionBugfix());
      m_pqleAppVersion->setText(qstrVersion);
      m_pqleEmail->setText(p_cApp.GetEmail());
      m_pqleHotline->setText(p_cApp.GetHotline());
      m_pqleManufacturer->setText(p_cApp.GetManufacturer());
      m_pqleWeb->setText(p_cApp.GetWebaddress());
      qstrVersion = qApp->applicationVersion();
      
      if (p_pCwmsRuntime)
      {  
         qstrVersion += " " + p_pCwmsRuntime->GetBuild();
      }

      m_pqleRuntimeVersion->setText(qstrVersion);
      m_pqleWmsVersion->setText(CdmDataProvider::GetVersion());
      m_qstrLicence = p_cApp.GetLicence();
   }
}

/** +-=---------------------------------------------------------Mi 5. Sep 11:13:20 2012-----------*
 * @method  CwmsAboutDlg::LicenceClickedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 11:13:20 2012-----------*/
void CwmsAboutDlg::LicenceClickedSlot()
{
   CwmsHelp::ShowLicence(m_qstrLicence, this);
}

/** +-=---------------------------------------------------------Mi 5. Sep 10:52:19 2012-----------*
 * @method  CwmsAboutDlg::ShowAboutDialog                    // public, static                    *
 * @return  void                                             //                                   *
 * @param   CwmsApplication p_cApp                           //                                   *
 * @param   CwmsRuntime* p_pCwmsRuntime                      //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 5. Sep 10:52:19 2012-----------*/
void CwmsAboutDlg::ShowAboutDialog(CwmsApplication p_cApp,
                                   CwmsRuntime* p_pCwmsRuntime,
                                   QWidget* p_pqwParent)
{
   CwmsAboutDlg* pAbout = new CwmsAboutDlg(p_pqwParent);
   pAbout->FillDialog(p_cApp, p_pCwmsRuntime);
   pAbout->exec();
   DELPTR(pAbout);
}

