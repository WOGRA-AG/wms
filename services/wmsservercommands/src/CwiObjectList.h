/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiObjectContainer.h
 ** Started Implementation: 2012/04/15
 ** Description:
 ** 
 ** Implements the ping interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSOBJECTLIST_H
#define CBIWMSOBJECTLIST_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSCOM Includes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"
#include "IdmEventStoreManager.h"

// Forwards
class CwmscomController;
class CwmscomData;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class Implements the container server side interface
 */
class WMSINTERFACE_API CwiObjectContainer : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiObjectContainer::CwiObjectContainer                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiObjectContainer( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiObjectContainer::~CwiObjectContainer                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiObjectContainer( );

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:17:19 2012-------*
    * @method  CwiObjectContainer::ExecutePut                  // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:17:19 2012----------*/
    void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiObjectContainer::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012--------*
    * @method  CwiObjectContainer::GetResourceDescription            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:19:08 2012-----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:17:10 2012-------*
    * @method  CwiObjectContainer::ExecuteDelete               // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:17:10 2012----------*/
    void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:29:56 2012-------*
    * @method  CwiObjectContainer::ExecuteGet                  // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:29:56 2012----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 11:04:58 2012-------*
    * @method  CwiObjectContainer::GetEmptyObjectList          // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 11:04:58 2012----------*/
    CdmObjectContainer* GetEmptyObjectList(long p_lDatabaseId, long p_lObjectListId);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:53:25 2012-------*
    * @method  CwiObjectContainer::Refresh                     // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_ObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:53:25 2012----------*/
    void Refresh(CwmscomData* p_pData, long p_lDbId, long p_ObjectListId);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:53:39 2012-------*
    * @method  CwiObjectContainer::Count                       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_ObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:53:39 2012----------*/
    void Count(CwmscomData* p_pData, long p_lDbId, long p_ObjectListId);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:54:08 2012-------*
    * @method  CwiObjectContainer::GetEmptyList                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_ObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:54:08 2012----------*/
    void GetEmptyList(CwmscomData* p_pData, long p_lDbId, long p_ObjectListId);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:54:23 2012-------*
    * @method  CwiObjectContainer::GetCompleteList             // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_ObjectListId                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:54:23 2012----------*/
    void GetCompleteList(CwmscomData* p_pData, long p_lDbId, long p_ObjectListId);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 15:18:11 2012-------*
    * @method  CwiObjectContainer::GetObjectListInternal       // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   QVariant qValue                               //                                   *
    * @param   bool p_bEmpty                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 15:18:11 2012----------*/
    CdmObjectContainer* GetObjectListInternal(long p_lDatabaseId, QVariant qValue, bool p_bEmpty);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 13:23:28 2012-------*
    * @method  CwiObjectContainer::GetCompleteObjectList       // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 13:23:28 2012----------*/
    CdmObjectContainer* GetCompleteObjectList(long p_lDatabaseId, QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 13:24:07 2012-------*
    * @method  CwiObjectContainer::GetEmptyObjectList          // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 13:24:07 2012----------*/
    CdmObjectContainer* GetEmptyObjectList(long p_lDatabaseId, QString p_qstrKeyname);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 13:42:48 2012-------*
    * @method  CwiObjectContainer::GetCompleteList             // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 13:42:48 2012----------*/
    void GetCompleteList(CwmscomData* p_pData, long p_lDbId, QString p_qstrKeyname);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 13:43:04 2012-------*
    * @method  CwiObjectContainer::GetEmptyList                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 13:43:04 2012----------*/
    void GetEmptyList(CwmscomData* p_pData, long p_lDbId, QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 15:29:10 2012-------*
    * @method  CwiObjectContainer::GetNewId                    // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 15:29:10 2012----------*/
    void GetNewId(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 18:22:21 2012-------*
    * @method  CwiObjectContainer::GetCompleteObjectList       // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 18:22:21 2012----------*/
    CdmObjectContainer* GetCompleteObjectList(long p_lDatabaseId, long p_lObjectListId);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 19:08:42 2012-------*
    * @method  CwiObjectContainer::Exist                       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 19:08:42 2012----------*/
    void Exist(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 19. Apr 10:44:11 2012-------*
    * @method  CwiObjectContainer::Query                       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Apr 10:44:11 2012----------*/
    void Query(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Di 1. Mai 11:31:59 2012--------*
    * @method  CwiObjectContainer::GetEmptyObjectList          // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 1. Mai 11:31:59 2012-----------*/
    CdmObjectContainer* GetEmptyObjectList(long p_lObjectListId);

   private:
   /** +-=---------------------------------------------------------Do 14. Mrz 14:15:45 2013-------*
    * @method  CwiObjectContainer::CreateObject                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 14. Mrz 14:15:45 2013----------*/
    void CreateObject(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mi 8. Mai 16:15:22 2013--------*
    * @method  CwiObjectContainer::DeleteObject                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 8. Mai 16:15:22 2013-----------*/
    void DeleteObject(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:28:56 2013-------*
    * @method  CwiObjectContainer::GetVersion                  // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:28:56 2013----------*/
    QString getVersion();

    private:
    void GetContainerList(CwmscomData* p_pData, long p_lDbId);
    void saveEvent(CdmObjectContainer *pContainer);
    void subcribeSubscribersForEventSourcing(CdmClassManager *pClassManager, IdmEventStoreManager *pEventStoreManager);
};

#endif // CBIWMSOBJECTLIST_H
