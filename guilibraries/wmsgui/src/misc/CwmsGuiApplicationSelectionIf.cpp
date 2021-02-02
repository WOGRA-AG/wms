/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsApplicationSelectionIf.cpp
 ** Started Implementation: 2008/05/18
 ** Description:
 ** 
 ** the interface for the application selection dlg
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <stdlib.h>
#include <qcombobox.h>
#include <qstringlist.h>
#include <qdir.h>
#include <qapplication.h>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsApplication.h"
#include "CwmsGuiApplicationSelectionIf.h"


/** +-=---------------------------------------------------------Di 28. Sep 08:15:10 2010----------*
 * @method  CwmsApplicationSelectionIf::CwmsApplicationSelectionIf // public                      *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 08:15:10 2010----------*/
CwmsGuiApplicationSelectionIf::CwmsGuiApplicationSelectionIf(QWidget* parent)
   : QDialog(parent)
{
   setupUi(this);
   FillDialog();
}

/** +-=---------------------------------------------------------Mi 26. Nov 19:30:04 2008----------*
 * @method  CwmsApplicationSelectionIf::~CwmsApplicationSelectionIf // public, virtual            *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsApplicationSelectionIf                                    *
 *----------------last changed: --------------------------------Mi 26. Nov 19:30:04 2008----------*/
CwmsGuiApplicationSelectionIf::~CwmsGuiApplicationSelectionIf()
{
}

/** +-=---------------------------------------------------------Mi 26. Nov 20:11:01 2008----------*
 * @method  CwmsApplicationSelectionIf::FillDialog           // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 26. Nov 20:11:01 2008----------*/
void CwmsGuiApplicationSelectionIf::FillDialog()
{
    QStringList qstrlApps = CwmsApplication::GetApplicationList(true, false, false);
    m_pqcbApplication->clear();
    m_pqcbApplication->addItems(qstrlApps);

}

/** +-=---------------------------------------------------------So 18. Mai 12:00:36 2008----------*
 * @method  CwmsApplicationSelectionIf::GetApplicationString // public, static                    *
 * @return  QString                                          //                                   *
 * @comment returns the application string which was selected by te user.                         *
 *----------------last changed: --------------------------------So 18. Mai 12:00:36 2008----------*/
QString CwmsGuiApplicationSelectionIf::GetApplicationString()
{
   QString qstrApplication; 
   CwmsGuiApplicationSelectionIf* pCwmsApplicationSelectionIf = new CwmsGuiApplicationSelectionIf();

   if (pCwmsApplicationSelectionIf->m_pqcbApplication->count() == 1)
   {
      qstrApplication = pCwmsApplicationSelectionIf->m_pqcbApplication->itemText(0);
   }
   else if (pCwmsApplicationSelectionIf->m_pqcbApplication->count() == 0)
   {
      CdmMessageManager::critical(tr("Keine Anwendung installiert"),
                            tr("Es ist keine Anwendung installiert für das das Programm geöffnet werden könnte.\n Oder keine ausreichenden Rechte vorhanden."));
   }
   else
   {
      if (pCwmsApplicationSelectionIf->exec() == QDialog::Accepted)
      {
         qstrApplication = pCwmsApplicationSelectionIf->m_pqcbApplication->currentText();
      }
   }

   DELPTR(pCwmsApplicationSelectionIf);
   return qstrApplication;
}

