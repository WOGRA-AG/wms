/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsViewManager.h
 ** Started Implementation: 2012/08/24
 ** Description:
 ** 
 ** implements the manager for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSVIEWMANAGER_H
#define CWMSVIEWMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsView.h"
#include "basetools.h"

// Forwards
class CdmClassManager;
class CdmObject;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the manager for views
 */
class BASETOOLS_API CwmsViewManager : public QObject
{


   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:08:34 2012-------*
    * @method  CwmsViewManager::CwmsViewManager              // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:08:34 2012----------*/
    CwmsViewManager( );

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:08:44 2012-------*
    * @method  CwmsViewManager::~CwmsViewManager             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsViewManager                                            *
    *----------------last changed: -----------------------------Fr 24. Aug 10:08:44 2012----------*/
    virtual ~CwmsViewManager( );

   private:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:09:13 2012-------*
    * @method  CwmsViewManager::CheckViewDataStructure       // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:09:13 2012----------*/
    void CheckViewDataStructure();

   private:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:09:29 2012-------*
    * @method  CwmsViewManager::CreateViewClass              // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:09:29 2012----------*/
    void CreateViewClass(CdmClassManager* p_pCdmClassManager);

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:10:31 2012-------*
    * @method  CwmsViewManager::GetObjectList                // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:10:31 2012----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 10:15:45 2012-------*
    * @method  CwmsViewManager::GetViewList                  // public                            *
    * @return  void                                          //                                   *
    * @param   QLinkedList<CdmObject*>& p_rqlViews           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 10:15:45 2012----------*/
    void GetViewList(QLinkedList<CdmObject*>& p_rqlViews);

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:06:02 2012-------*
    * @method  CwmsViewManager::GetView                      // public                            *
    * @return  CwmsView                                      //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:06:02 2012----------*/
    CwmsView GetView(long p_lObjectId);

   public:
   /** +-=---------------------------------------------------------Fr 24. Aug 11:06:21 2012-------*
    * @method  CwmsViewManager::GetView                      // public                            *
    * @return  CwmsView                                      //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 24. Aug 11:06:21 2012----------*/
    CwmsView GetView(QString p_qstrName);
};

#endif // CWMSVIEWMANAGER_H
