/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwqQmlObjectViewer.h
 ** Started Implementation: 2013/08/30
 ** Description:
 ** 
 ** 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWQQMLOBJECTVIEWER_H
#define CWQQMLOBJECTVIEWER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <qqmlapplicationengine.h>

// WMS Includes
#include "CsaFactory.h"

// own Includes
#include "CwmsQmlEngineInitializer.h"
#include "wmsqml_global.h"

// Forwards
class QQuickWindow;
class QQuickView;
class CdmObject;
class CdmLocatedElement;
class CdmObjectContainer;

// TypeDefs

// enums

/* 
 * This class implements the main test class which starts all tests
 */
class WMSQML_EXPORT CwqQmlObjectViewer : public CwmsQmlEngineInitializer
{
   Q_OBJECT

    private:
    bool m_bDevelopmentMode;
    
   public:
   /** +-=---------------------------------------------------------Fr 30. Aug 21:22:03 2013-------*
    * @method  CwqQmlObjectViewer::CwqQmlObjectViewer        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 30. Aug 21:22:03 2013----------*/
    CwqQmlObjectViewer(QObject* p_pParent = NULL);

   public:
   /** +-=---------------------------------------------------------Fr 30. Aug 21:22:17 2013-------*
    * @method  CwqQmlObjectViewer::~CwqQmlObjectViewer       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwqQmlObjectViewer                                         *
    *----------------last changed: -----------------------------Fr 30. Aug 21:22:17 2013----------*/
    virtual ~CwqQmlObjectViewer( );


   public:
   /** +-=---------------------------------------------------------Mi 25. Sep 21:48:38 2013-------*
    * @method  CwqQmlObjectViewer::CreateView                // public                    *
    * @return  QQuickWindow*                                   //                                   *
    * @param   CdmLocatedElement* p_pObject                  //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QString p_qstrQml                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 25. Sep 21:48:38 2013----------*/
    QQuickWindow* CreateView(CdmLocatedElement* p_pObject,
                                  QString p_qstrName,
                                  QString p_qstrQml);

   public:
   /** +-=---------------------------------------------------------Mi 25. Sep 21:38:43 2013-------*
    * @method  CwqQmlObjectViewer::CreateView                // public                    *
    * @return  QQuickWindow*                                   //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QString p_qstrQml                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 25. Sep 21:38:43 2013----------*/
    QQuickWindow* CreateView(QString p_qstrName, QString p_qstrQml);

public:
   /** +-=---------------------------------------------------------Fr 27. Sep 12:18:29 2013-------*
    * @method  CwqQmlObjectViewer::ValidateCode              // public                    *
    * @return  bool                                          //                                   *
    * @param   CdmLocatedElement* p_pObject                  //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   QString p_qstrQml                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 27. Sep 12:18:29 2013----------*/
    bool ValidateCode(CdmLocatedElement* p_pObject, QString p_qstrName, QString p_qstrQml);
    void SetDevelopmentMode(bool bDevelopmentMode);
    QQuickWindow *CreateView(QString p_qstrFilename, QString p_qstrObjectName, QObject *p_pObject);
    QQuickWindow *CreateView(QUrl p_Url);
    void Show(bool p_bModal);
    void ShowNoneModal();
    void ShowModal();
};

#endif //
