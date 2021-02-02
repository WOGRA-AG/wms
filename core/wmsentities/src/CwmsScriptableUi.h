/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptableUi.h
 ** Started Implementation: 2012/11/27
 ** Description:
 ** 
 ** implements ui calls for the script environment.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLEUI_H
#define CWMSSCRIPTABLEUI_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CdmObject;
class CdmObjectContainer;

// TypeDefs



/* 
 * This class implements ui calls for the script environment.
 */
class BASETOOLS_API CwmsScriptableUi: public CwmsScriptableBase
{

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:42:15 2012-------*
    * @method  CwmsScriptableUi::CwmsScriptableUi            // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:42:15 2012----------*/
    CwmsScriptableUi( );

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:42:22 2012-------*
    * @method  CwmsScriptableUi::~CwmsScriptableUi           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptableUi                                           *
    *----------------last changed: -----------------------------Di 27. Nov 16:42:22 2012----------*/
    virtual ~CwmsScriptableUi( );

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:43:00 2012-------*
    * @method  CwmsScriptableUi::OpenUi                      // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:43:00 2012----------*/
void openUi( CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:43:34 2012-------*
    * @method  CwmsScriptableUi::OpenUi                      // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:43:34 2012----------*/
void openUi( CdmObjectContainer* p_pContainer);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:43:52 2012-------*
    * @method  CwmsScriptableUi::OpenSearch                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:43:52 2012----------*/
void openSearch( CdmObjectContainer* p_pContainer);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:44:44 2012-------*
    * @method  CwmsScriptableUi::OpenImport                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:44:44 2012----------*/
void openImport( CdmObjectContainer* p_pContainer);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:45:03 2012-------*
    * @method  CwmsScriptableUi::OpenExport                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:45:03 2012----------*/
void openExport( CdmObjectContainer* p_pContainer);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:46:13 2012-------*
    * @method  CwmsScriptableUi::OpenHistory                 // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:46:13 2012----------*/
void openHistory( CdmObjectContainer* p_pContainer);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:46:31 2012-------*
    * @method  CwmsScriptableUi::OpenHistory                 // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:46:31 2012----------*/
void openHistory( CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:47:35 2012-------*
    * @method  CwmsScriptableUi::SelectObject                // public                            *
    * @return  QObject*                                      //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:47:35 2012----------*/
    QObject* selectObject(CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:47:59 2012-------*
    * @method  CwmsScriptableUi::SelectObjectList            // public                            *
    * @return  QObject*                                      //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:47:59 2012----------*/
    QObject* selectObjectList(CdmClass* p_pCdmClass);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:48:54 2012-------*
    * @method  CwmsScriptableUi::EditPrintingTemplate        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:48:54 2012----------*/
void editPrintingTemplate( CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:49:03 2012-------*
    * @method  CwmsScriptableUi::EditPrintingTemplate        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:49:03 2012----------*/
void editPrintingTemplate( CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Di 27. Nov 16:49:32 2012-------*
    * @method  CwmsScriptableUi::SelectClass                 // public                            *
    * @return  QObject*                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:49:32 2012----------*/
    QObject* selectClass();
};

#endif // CWMSSCRIPTABLEUI_H

