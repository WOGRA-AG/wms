/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwqQmlObjectViewer.cpp
 ** Started Implementation: 2013/08/30
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>
#include <QQuickView>
#include <qquickitem.h>
#include <QQmlApplicationEngine>
#include <qqmlengine.h>
#include <qqmlcomponent.h>
#include <qqmlcontext.h>
#include <QQmlError>
#include <qqmlcontext.h>
#include <qcoreapplication.h>

// WMS Basetools includes
#include "cwmsbtplattforminformation.h"
#include "CwmsScriptableLogger.h"
#include "CwmsScriptableMailer.h"
#include "CwmsScriptableMessage.h"
#include "CwmsScriptablePlugin.h"
#include "CwmsScriptablePrinter.h"
#include "CwmsScriptableStatic.h"
#include "CwmsScriptableWorkflow.h"
#include "CwmsScriptableWql.h"
#include "CwmsScriptableUi.h"

// WMS Includes
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CdmLogging.h"
#include "CdmExecutor.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmMessageManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CsaManager.h"

// own Includes
#include "CwmsqmlImageProvider.h"
#include "CwmsQmlHelper.h"
#include "CwqQmlObjectViewer.h"

/** +-=---------------------------------------------------------Fr 30. Aug 21:22:03 2013----------*
 * @method  CwqQmlObjectViewer::CwqQmlObjectViewer           // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 30. Aug 21:22:03 2013----------*/
CwqQmlObjectViewer::CwqQmlObjectViewer(QObject* p_pParent)
: CwmsQmlEngineInitializer(p_pParent),
  m_bDevelopmentMode(false)
{
}

/** +-=---------------------------------------------------------Fr 30. Aug 21:22:17 2013----------*
 * @method  CwqQmlObjectViewer::~CwqQmlObjectViewer          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwqQmlObjectViewer                                            *
 *----------------last changed: --------------------------------Fr 30. Aug 21:22:17 2013----------*/
CwqQmlObjectViewer::~CwqQmlObjectViewer()
{
}

/** +-=---------------------------------------------------------Fr 27. Sep 12:18:29 2013----------*
 * @method  CwqQmlObjectViewer::ValidateCode                 // public                    *
 * @return  bool                                             //                                   *
 * @param   CdmLocatedElement* p_pObject                     //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QString p_qstrQml                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 27. Sep 12:18:29 2013----------*/
bool CwqQmlObjectViewer::ValidateCode(CdmLocatedElement* p_pObject,
                                      QString p_qstrName,
                                      QString p_qstrQml)
{
   bool result = false;
   
   QQmlContext* pContext = m_pEngine->rootContext();

   if (CHKPTR(pContext))
   {
      pContext->setContextProperty("Element", p_pObject);
   }

   QQuickWindow* pView = CreateView(p_qstrName, p_qstrQml);

   DELPTR(pView);

return result;
}

/** +-=---------------------------------------------------------Mi 25. Sep 21:48:38 2013----------*
 * @method  CwqQmlObjectViewer::CreateView                   // public                    *
 * @return  QQuickWindow*                                      //                                   *
 * @param   CdmLocatedElement* p_pObject                     //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QString p_qstrQml                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 25. Sep 21:48:38 2013----------*/
QQuickWindow* CwqQmlObjectViewer::CreateView(CdmLocatedElement* p_pObject,
                                           QString p_qstrName,
                                           QString p_qstrQml)
{
    if (p_pObject->IsObject())
    {
       CsaLocatedElement* pElement =
       m_pFactory->createScriptObject(dynamic_cast<CdmModelElement*>(p_pObject));
       if (pElement)
       {
          CsaObject* pObject = dynamic_cast<CsaObject*>(pElement);

          if (pObject)
          {
             m_pEngine->rootContext()->setContextProperty("object", pObject);
          }
       }
    }
    else if (p_pObject->IsContainer())
    {
       CsaLocatedElement* pElement =
          m_pFactory->createScriptObject(dynamic_cast<CdmModelElement*>(p_pObject));

       if (pElement)
       {
          CsaObjectContainer* pObject = dynamic_cast<CsaObjectContainer*>(pElement);

          if (pObject)
          {
             m_pEngine->rootContext()->setContextProperty("container", pObject);
          }
       }
    }

    m_pEngine->rootContext()->setContextProperty("wms", m_pFactory->getManager());

    return CreateView(p_qstrName, p_qstrQml);
}

QQuickWindow* CwqQmlObjectViewer::CreateView(QString p_qstrFilename, QString p_qstrObjectName, QObject* p_pObject)
{
    INFO("Creating the View");
    addContextPropertyToEngine(p_qstrObjectName, p_pObject);
    INFO("Context Properties added to Engine");
    return CreateView(QUrl(p_qstrFilename));
}

QQuickWindow* CwqQmlObjectViewer::CreateView(QUrl p_Url)
{
    QQuickWindow::setDefaultAlphaBuffer(false);
    QQuickWindow* pWindow = nullptr;
    QString qstrImportPath = "qrc:/qml/";
    m_pEngine->addImportPath(qstrImportPath);
    INFO("Importpath: " + qstrImportPath);
    INFO("Loading Url: " + p_Url.toDisplayString());
    m_pEngine->load(p_Url);
    INFO("Looking for first root Object")
    QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);

    if (pFirstTopLevelObject)
    {
       INFO("First root object found")
       pWindow = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);
    }
    else
    {
      ERR("No root Object created.")
    }

    if (pWindow)
    {
      INFO("Connect to destructor")
      connect(pWindow, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
    }
    else
    {
      ERR("QML Window not created!")
    }

    return pWindow;
}

/** +-=---------------------------------------------------------Mi 25. Sep 21:38:43 2013----------*
 * @method  CwqQmlObjectViewer::CreateView                   // public                    *
 * @return  QQuickWindow*                                      //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   QString p_qstrQml                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 25. Sep 21:38:43 2013----------*/
QQuickWindow* CwqQmlObjectViewer::CreateView(QString p_qstrName, QString p_qstrQml)
{
   QQuickWindow* pWindow = nullptr;

   QQmlComponent component(m_pEngine);
   QQmlContext *context = new QQmlContext(m_pEngine->rootContext());
   QByteArray qbaSource;
   qbaSource.append(p_qstrQml);
   component.setData(qbaSource, QUrl(p_qstrName));
   QObject *pFirstTopLevelObject = component.create(context);

   QList<QQmlError> errors = component.errors();

   if (!errors.isEmpty())
   {
       for (int iPos = 0; iPos < errors.count(); ++iPos)
       {
           QQmlError error = errors[iPos];
           ERR(error.toString());
       }
   }

   if (pFirstTopLevelObject)
   {
	  pWindow = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);

	  if (!pWindow)
	  {
		  QQuickItem* pItem = qobject_cast<QQuickItem*>(pFirstTopLevelObject);

		  if (pItem)
		  {
			  pWindow = new QQuickWindow();
			  pItem->setParentItem(pWindow->contentItem());
		  }
	  }
   }

   if (pWindow)
   {
      // destroy the CwqObjectViewer when the dialog will be destroyed
      connect(pWindow, SIGNAL(destroyed(QObject*)), this, SLOT(deleteLater()));
   }
   
   return pWindow;
}

void CwqQmlObjectViewer::SetDevelopmentMode(bool bDevelopmentMode)
{
    m_bDevelopmentMode = bDevelopmentMode;
}

void CwqQmlObjectViewer::ShowModal()
{
   Show(true);
}

void CwqQmlObjectViewer::ShowNoneModal()
{
   Show(false);
}

void CwqQmlObjectViewer::Show(bool p_bModal)
{
   QQuickWindow* pWindow = nullptr;
   QObject* pFirstTopLevelObject = m_pEngine->rootObjects().value(0);

   if (pFirstTopLevelObject)
   {
      pWindow = qobject_cast<QQuickWindow*>(pFirstTopLevelObject);
   }

   if (pWindow)
   {
      if (p_bModal)
      {
         pWindow->setModality(Qt::WindowModal);
      }

      CwmsbtPlattformInformation info;

      if ((info.isMobile() || info.isTablet()) && !info.IsSimulating())
      {
         pWindow->showMaximized();
      }
      else
      {
         pWindow->show();
      }
   }
   else
   {
      ERR(tr("Could not create Window."));
   }
}
