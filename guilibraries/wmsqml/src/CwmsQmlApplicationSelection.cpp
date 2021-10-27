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
#include <qquickwindow.h>
#include <qstringlist.h>
#include <qdir.h>
#include <qapplication.h>

// WMS Includes
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmLogging.h"

// WMSQML Includes
#include "CwqQmlObjectViewer.h"

// Own Includes
#include "CwmsApplication.h"
#include "CwmsInitApplication.h"
#include "CwmsQmlApplicationSelection.h"


/** +-=---------------------------------------------------------Di 28. Sep 08:15:10 2010----------*
 * @method  CwmsApplicationSelectionIf::CwmsApplicationSelectionIf // public                      *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 08:15:10 2010----------*/
CwmsQmlApplicationSelection::CwmsQmlApplicationSelection(CwmsInitApplication* p_pInit)
: m_pInit(p_pInit)
{
}

/** +-=---------------------------------------------------------Mi 26. Nov 19:30:04 2008----------*
 * @method  CwmsApplicationSelectionIf::~CwmsApplicationSelectionIf // public, virtual            *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsApplicationSelectionIf                                    *
 *----------------last changed: --------------------------------Mi 26. Nov 19:30:04 2008----------*/
CwmsQmlApplicationSelection::~CwmsQmlApplicationSelection()
{
}

/** +-=---------------------------------------------------------Mi 26. Nov 20:11:01 2008----------*
 * @method  CwmsApplicationSelectionIf::SelectApplication           // public                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 26. Nov 20:11:01 2008----------*/
void CwmsQmlApplicationSelection::selectApplication()
{
   QStringList qstrlApps = CwmsApplication::GetApplicationList();

   if (qstrlApps.count() == 1)
   {
      loadSelection(qstrlApps[0]);
      m_pInit->StateFinished(true);
      deleteLater();
   }
   else if(qstrlApps.count() == 0)
   {
      MSG_CRIT("Keine Anwendung installiert",
         "Es ist keine Anwendung installiert für das das Programm geöffnet werden könnte.\n Oder Sie haben keine ausreichende Berechtigung.");
      m_pInit->StateFinished(false);
      deleteLater();
   }
   else
   {
      openSelectionDialog(qstrlApps);
   }
}

void CwmsQmlApplicationSelection::openSelectionDialog(QStringList& qstrlApplications)
{
    QObject* pThis = dynamic_cast<QObject*>(this);
    CwqQmlObjectViewer* pViewer = new CwqQmlObjectViewer(this);
    pViewer->addContextPropertyToEngine("selectionModel", QVariant::fromValue(qstrlApplications));
    QQuickWindow* view = pViewer->CreateView("qrc:/qml/WmsSelection.qml", "selector", pThis);

    if (CHKPTR(view))
    {
        pViewer->ShowModal();
        connect(pViewer, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
    }
}

/** +-=---------------------------------------------------------Di 4. Sep 14:29:02 2012-----------*
 * @method  CwmsDatabaseSelection::Cancel        // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the user wants to cancel this application.                *
 *----------------last changed: --------------------------------Di 4. Sep 14:29:02 2012-----------*/
void CwmsQmlApplicationSelection::cancel()
{
    m_pInit->StateFinished(false);
}


void CwmsQmlApplicationSelection::ok()
{
    m_pInit->StateFinished(true);
}

/** +-=---------------------------------------------------------Di 4. Sep 15:17:02 2012-----------*
 * @method  CwmsDatabaseSelection::LoadSelection              // private                           *
 * @return  bool                                             //                                   *
 * @param   QString p_qstrSelection                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 4. Sep 15:17:02 2012-----------*/
bool CwmsQmlApplicationSelection::loadSelection(QString p_qstrSelection)
{
   m_pInit->SetApplication(p_qstrSelection);
   return true;
}




