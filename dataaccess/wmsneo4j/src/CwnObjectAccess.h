/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
  ******************************************************************************/

#ifndef CODBCOBJECTACCESS_H
#define CODBCOBJECTACCESS_H

// System and QT Includes
#include <QMap>
#include <QList>


// own Includes
#include "CdmLocatedElement.h"
#include "CwnDataAccess.h"


// forwards
class CwnDataAccess;
class CdmQuery;
class CdmObject;
class CdmObjectContainer;
class CdmValueBool;
class CdmValueInt;
class CdmValueFloat;
class CdmValueLong;
class CdmValueDouble;
class CdmValueString;
class CdmValueObjectRef;
class CdmValueContainerRef;
class CdmValueCharacterDocument;
class CdmValueBinaryDocument;
class CdmValueCounter;
class CdmValueDate;
class CdmValueTime;
class CdmValueDateTime;
class CdmValue;



/**
  * This class manages the object access over
  * the database. All objects queries will be done here.
  */
class CwnObjectAccess
{
   protected:
      /*
       * The dataaccess
       */
      CwnDataAccess* m_rpCwnDataAccess;

      /*
       * The new obejct counter
       */
      int m_iNewObjectCounter;

      /*
       * The newobjectlistcounter
       */
      int m_iNewObjectListCounter;

      /*
       * map of locked objects <ObjectId, SessionId>
       */
      QMap<int,int> m_qmLockedObjects;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:02:06 2005*
    * @method  CwnObjectAccess::CwnObjectAccess          // public                            *
    * @return                                                //                                   *
    * @param   CwnDataAccess* p_pCwnDataAccess           //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:02:06 2005----------*/
CwnObjectAccess(  CwnDataAccess* p_pCwnDataAccess );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:02:16 2005*
    * @method  CwnObjectAccess::~CwnObjectAccess         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwnObjectAccess                                          *
    *----------------last changed: -----------------------------Sa 20. Aug 12:02:16 2005----------*/
virtual ~CwnObjectAccess(  );

   public:
   /** +-=---------------------------------------------------------Di 23. Aug 15:50:10 2005*
    * @method  CwnObjectAccess::DeleteObjectList           // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment Deletes an objectlist from db.                                                     *
    *----------------last changed: -----------------------------Di 23. Aug 15:50:10 2005----------*/
virtual long DeleteContainer(  long p_lObjectListId );

   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 17:00:25 2010-------*
    * @method  CwnObjectAccess::ExecuteQuery               // public                            *
    * @return  long                                          //                                   *
    * @param   long# p_lDbId                                 //                                   *
    * @param   CdmObjectContainer*# p_pContainer              //                                   *
    * @param   CdmQuery* p_pCdmQuery                         //                                   *
    * @comment This emthod executes an query on Server Side.                                      *
    *----------------last changed: -----------------------------Mi 15. Sep 17:00:25 2010----------*/
    long ExecuteQuery(CdmQuery* p_pCdmQuery);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:02:31 2005*
    * @method  CwnObjectAccess::ExistObjectList            // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lClassId                               //                                   *
    * @param   QString p_qstrObjectListKeyname               //                                   *
    * @comment This method checks if exist th objectlist with the overgiven keyname.              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:02:31 2005----------*/
long ExistObjectList(  long p_lClassId, QString p_qstrObjectListKeyname );

   public:
   /** +-=---------------------------------------------------------So 11. Sep 12:22:14 2005*
    * @method  CwnObjectAccess::GetNewObjectId             // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment This method gets a new object id from datasource.                                  *
    *----------------last changed: -----------------------------So 11. Sep 12:22:14 2005----------*/
virtual long GetNewObjectId(  long p_lObjectListId, long p_lSessionId );

   public:
   /** +-=---------------------------------------------------------So 11. Sep 12:22:20 2005*
    * @method  CwnObjectAccess::GetNewObjectListId         // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lClassId                               //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 11. Sep 12:22:20 2005----------*/
virtual long GetNewObjectListId(  long p_lClassId, long p_lSessionId );

   public:
   /** +-=---------------------------------------------------------So 22. Jan 13:59:23 2006*
    * @method  CwnObjectAccess::GetObjectListsList         // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_lClassId                               //                                   *
    * @param   QMap<long,QString>& p_rqmObjectListsList      //                                   *
    * @comment This method returns a list of all objectlists.                                     *
    *----------------last changed: Wolfgang Gra�hof-------------So 22. Jan 13:59:23 2006----------*/
long GetObjectListsList(  long p_lDbId, long p_lClassId, QMap<long,QString>& p_rqmObjectListsList );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:02:49 2005*
    * @method  CwnObjectAccess::LoadObject                 // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   CdmObject*& p_pCdmObject                      //                                   *
    * @comment This method loads a aobject from DataAccess.                                       *
    *----------------last changed: -----------------------------Sa 20. Aug 12:02:49 2005----------*/
long LoadObject(  long p_lObjectListId, long p_lObjectId, CdmObject*& p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:02:53 2005*
    * @method  CwnObjectAccess::LoadObjectList             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:02:53 2005----------*/
long LoadContainer(  long p_lObjectListId, CdmObjectContainer*& p_pContainer );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:11 2005*
    * @method  CwnObjectAccess::LockObject                 // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   bool & p_bResult                              //                                   *
    * @comment This method locks objects on server side.                                          *
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:11 2005----------*/
long LockObject(  long p_lSessionId, long p_lObjectId, bool & p_bResult );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:22 2005*
    * @method  CwnObjectAccess::UnLockObject               // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   bool & p_bResult                              //                                   *
    * @comment This method unlocks objects on server side.                                        *
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:22 2005----------*/
long UnLockObject(  long p_lSessionId, long p_lObjectId, bool & p_bResult );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:26 2005*
    * @method  CwnObjectAccess::UpdateObject               // public                            *
    * @return  long                                          //                                   *
    * @param   CdmObject*& p_pCdmObject                      //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment This method updates an object. It sends the object changes to server. on which it  *
    *          will be merged and resend. This object can be invalid or delted and receiving the  *
    *          new object data because a other user has deleted it.                               *
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:26 2005----------*/
long UpdateObject(  CdmObject*& p_pCdmObject, long p_lSessionId );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:07:39 2005*
    * @method  CwnObjectAccess::UpdateObjectList           // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment This method updates an object. It sends the object changes to server. on which it  *
    *          will be merged and resend. This object can be invalid or delted and receiving the  *
    *          new object data because a other user has deleted it.                               *
    *----------------last changed: -----------------------------Mo 5. Sep 19:07:39 2005-----------*/
virtual long UpdateContainer(  CdmObjectContainer*& p_pContainer, long p_lSessionId );

   protected:
   /** +-=---------------------------------------------------------Di 23. Aug 15:50:01 2005*
    * @method  CwnObjectAccess::DeleteObject               // protected, virtual                *
    * @return  long                                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment This method deletes objects from db.                                               *
    *----------------last changed: -----------------------------Di 23. Aug 15:50:01 2005----------*/
virtual long DeleteObject(  long p_lObjectId, long p_lSessionId );

   protected:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:16 2005*
    * @method  CwnObjectAccess::IsObjectLocked             // protected                         *
    * @return  long                                          // SessionId of the locker or 0 if object is not locked*
    * @param   long p_lObjectId                              //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment returns if a object is locked or not.                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:16 2005----------*/
long IsObjectLocked(  long p_lObjectId, long p_lSessionId );


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:05 2005*
    * @method  CwnObjectAccess::LoadObjectList             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:05 2005----------*/
long LoadContainer(  long p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:03:00 2005*
    * @method  CwnObjectAccess::LoadEmptyObjectList        // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:03:00 2005----------*/
long LoadEmptyContainer(  long p_lDbId, QString p_qstrKeyname, CdmObjectContainer*& p_pContainer );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:07:25 2005*
    * @method  CwnObjectAccess::ReadBinaryDocument         // public                            *
    * @return  int                                           //                                   *
    * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument       //                                   *
    * @comment This method reads the BinaryDocument from database and set it to the local filesystem.*
    *----------------last changed: -----------------------------Sa 20. Aug 12:07:25 2005----------*/
QByteArray ReadBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument );

   public:
   /** +-=---------------------------------------------------------Mo 5. Sep 19:30:15 2005*
    * @method  CwnObjectAccess::UpdateBinaryDocument       // public, virtual                   *
    * @return  int                                           //                                   *
    * @param   CdmValueBinaryDocument* p_pCdmBinaryDocument       //                                   *
    * @comment This method updates the BinaryDocument on the database and synchronizes it to the  *
    *          local file.                                                                        *
    *----------------last changed: -----------------------------Mo 5. Sep 19:30:15 2005-----------*/
virtual int UpdateBinaryDocument(  CdmValueBinaryDocument* p_pCdmBinaryDocument );

   public:
   /** +-=---------------------------------------------------------Mi 15. Sep 17:05:22 2010-------*
    * @method  CwnObjectAccess::GetCounterValue            // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long# p_lDbId                                 //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lValueId                               //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 15. Sep 17:05:22 2010----------*/
    virtual long GetCounterValue(long p_lDbId,
                                 long p_lObjectListId,
                                 long p_lValueId,
                                 QString p_qstrKeyname);


   protected:
   /** +-=---------------------------------------------------------Fr 23. Dez 10:57:56 2005*
    * @method  CwnObjectAccess::UpdateRights               // protected                         *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Gra�hof-------------Fr 23. Dez 10:57:56 2005----------*/
long UpdateRights(  CdmObjectContainer*& p_pContainer );

   private:
   /** +-=---------------------------------------------------------Fr 23. Dez 11:13:49 2005*
    * @method  CwnObjectAccess::LoadObjectListRights       // private                           *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Gra�hof-------------Fr 23. Dez 11:13:49 2005----------*/
long LoadObjectListRights(  CdmObjectContainer*& p_pContainer );


   public:
   /** +-=---------------------------------------------------------Do 25. Mai 12:46:34 2006-------*
    * @method  CwnObjectAccess::LoadEmptyObjectList        // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   CdmObjectContainer*& p_pContainer              //                                   *
    * @comment This method loads the objectlist with the Id p_lObjectId from Database p_lDatabase. *
    *----------------last changed: Wolfgang Gra�hof-------------Do 25. Mai 12:46:34 2006----------*/
    long LoadEmptyContainer(long p_lDbId, long p_lId, CdmObjectContainer*& p_pContainer);

   public:
   /** +-=---------------------------------------------------------Do 17. Mai 15:37:35 2007-------*
    * @method  CwnObjectAccess::LoadObjects                // public                            *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QValueList<long>& p_rqvlObjectIds             //                                   *
    * @comment This method loads all objects overgiven in the objectid list.                      *
    *----------------last changed: Wolfgang Gra�hof-------------Do 17. Mai 15:37:35 2007----------*/
    long LoadObjects(CdmObjectContainer* p_pContainer, QList<long>& p_rqvlObjectIds);


   public:
   /** +-=---------------------------------------------------------Mo 17. Sep 17:55:28 2007-------*
    * @method  CwnObjectAccess::IsObjectUsed               // public                            *
    * @return  int                                           //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment This method returns if a object is used in a objectref or not.                     *
    *----------------last changed: -----------------------------Mo 17. Sep 17:55:28 2007----------*/
    int IsObjectUsed(long p_lObjectId, long p_lObjectListId);



   public:
   /** +-=---------------------------------------------------------Sa 8. Nov 10:59:19 2008--------*
    * @method  CwnObjectAccess::CountObjectsOnDb           // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment refreshes the objects from the overgiven objectlist.                               *
    *----------------last changed: -----------------------------Sa 8. Nov 10:59:19 2008-----------*/
    virtual long CountObjectsOnDb(CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Sa 8. Nov 10:59:01 2008--------*
    * @method  CwnObjectAccess::RefreshObjectList          // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment refreshes the objects from the overgiven objectlist.                               *
    *----------------last changed: -----------------------------Sa 8. Nov 10:59:01 2008-----------*/
    virtual long RefreshObjectList(CdmObjectContainer* p_pContainer);

   public:
   /** +-=---------------------------------------------------------Sa 8. Nov 10:57:29 2008--------*
    * @method  CwnObjectAccess::RefreshObject              // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment refreshes the values from the overgiven object.                                    *
    *----------------last changed: -----------------------------Sa 8. Nov 10:57:29 2008-----------*/
    virtual long RefreshObject(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------Sa 8. Nov 11:12:25 2008--------*
    * @method  CwnObjectAccess::FindObjectIdToObjectList   // private                           *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeynameObjectList               //                                   *
    * @param   QList<long>& p_rqvlIds                  //                                   *
    * @comment Finds the objectId's of the objectlist.                                            *
    *----------------last changed: -----------------------------Sa 8. Nov 11:12:25 2008-----------*/
    long FindObjectIdToObjectList(long p_lDbId,
                                  QString p_qstrKeynameObjectList,
                                  QList<long>& p_rqvlIds);

   private:
   /** +-=---------------------------------------------------------Di 21. Jul 19:07:15 2009-------*
    * @method  CwnObjectAccess::UpdateObjects              // private                           *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QList<CdmObject*>& p_rqlObjects         //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Jul 19:07:15 2009----------*/
    long UpdateObjects(CdmObjectContainer* p_pContainer,
                       QList<CdmObject*>& p_rqlObjects,
                       long p_lSessionId);

   private:
   /** +-=---------------------------------------------------------Di 21. Jul 19:08:28 2009-------*
    * @method  CwnObjectAccess::DeleteObjects              // private                           *
    * @return  long                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QList<CdmObject*>& p_rqlObjects         //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Jul 19:08:28 2009----------*/
    long DeleteObjects(CdmObjectContainer* p_pContainer,
                       QList<CdmObject*>& p_rqlObjects,
                       long p_lSessionId);


public:
   /** +-=---------------------------------------------------------Do 10. Sep 17:53:51 2009-------*
    * @method  CwnObjectAccess::GetCounterValue            // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmValueCounter* p_pCdmCounter                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Sep 17:53:51 2009----------*/
    virtual void GetCounterValue(CdmValueCounter* p_pCdmCounter);


   public:
   /** +-=---------------------------------------------------------Do 8. Nov 11:18:37 2012--------*
    * @method  CwnObjectAccess::GetReferences              // public, virtual                   *
    * @return  bool                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   QMap<long, long>& p_rqmReferences             // objectId/ObjectListId             *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 8. Nov 11:18:37 2012-----------*/
    virtual bool GetReferences(long p_lObjectListId,
                               long p_lObjectId,
                               QMap<long,
                               long>& p_rqmReferences);

   public:
   /** +-=---------------------------------------------------------Do 8. Nov 11:18:59 2012--------*
    * @method  CwnObjectAccess::GetOwner                   // public, virtual                   *
    * @return  bool                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long& p_lOwnerObjectListId                    //                                   *
    * @param   long& p_lOwnerObjectId                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 8. Nov 11:18:59 2012-----------*/
    virtual bool GetOwner(long p_lObjectListId, long& p_lOwnerObjectListId, long& p_lOwnerObjectId);

   public:
   /** +-=---------------------------------------------------------Do 8. Nov 11:19:21 2012--------*
    * @method  CwnObjectAccess::GetOwner                   // public, virtual                   *
    * @return  bool                                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   long& p_lOwnerObjectListId                    //                                   *
    * @param   long& p_lOwnerObjectId                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 8. Nov 11:19:21 2012-----------*/
    virtual bool GetOwner(long p_lObjectListId,
                          long p_lObjectId,
                          long& p_lOwnerObjectListId,
                          long& p_lOwnerObjectId);
    long LoadObject(long p_lObjectListId, QString p_qstrKeyname, CdmObject *&p_pCdmObject);
};

#endif //
