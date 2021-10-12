/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiObject.h
 ** Started Implementation: 2012/04/15
 ** Description:
 ** 
 ** Implements the ping interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSOBJECT_H
#define CBIWMSOBJECT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSCOM Includes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"

// Forwards
class CwmscomController;
class CwmscomData;
class CdmObject;

// TypeDefs


/* 
 * This class Implements the ....
 */
class WMSINTERFACE_API CwiObject : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiObject::CwiObject                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiObject( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiObject::~CwiObject                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiObject( );

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:18:03 2012-------*
    * @method  CwiObject::ExecutePut                      // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:18:03 2012----------*/
    void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiObject::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012--------*
    * @method  CwiObject::GetResourceDescription            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:19:08 2012-----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:17:55 2012-------*
    * @method  CwiObject::ExecuteDelete                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:17:55 2012----------*/
    void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------So 15. Apr 14:30:02 2012-------*
    * @method  CwiObject::ExecuteGet                      // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 14:30:02 2012----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:01:28 2012-------*
    * @method  CwiObject::GetObject                       // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param  qint64 p_lDatabaseId                            //                                   *
    * @param  qint64 p_lObjectListId                          //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:01:28 2012----------*/
    static CdmObject* GetObject(qint64 p_lDatabaseId,qint64 p_lObjectListId,qint64 p_lObjectId);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 15:42:18 2012-------*
    * @method  CwiObject::GetNewId                        // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 15:42:18 2012----------*/
    void GetNewId(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mi 18. Apr 15:42:48 2012-------*
    * @method  CwiObject::Refresh                         // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 15:42:48 2012----------*/
    void Refresh(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 15:43:11 2012-------*
    * @method  CwiObject::GetObject                       // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 15:43:11 2012----------*/
    void GetObject(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 18:29:02 2012-------*
    * @method  CwiObject::Lock                            // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 18:29:02 2012----------*/
    void Lock(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 18. Apr 18:29:18 2012-------*
    * @method  CwiObject::Unlock                          // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 18:29:18 2012----------*/
    void Unlock(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 19. Apr 11:29:32 2012-------*
    * @method  CwiObject::ReadBinaryDocument              // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Apr 11:29:32 2012----------*/
    void ReadBinaryDocument(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 19. Apr 11:27:41 2012-------*
    * @method  CwiObject::CounterValue                    // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Apr 11:27:41 2012----------*/
    void CounterValue(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 19. Apr 11:29:47 2012-------*
    * @method  CwiObject::UpdateBinaryDocument            // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Apr 11:29:47 2012----------*/
    void UpdateBinaryDocument(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 19. Apr 15:10:49 2012-------*
    * @method  CwiObject::IsObjectUsed                    // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 19. Apr 15:10:49 2012----------*/
    void IsObjectUsed(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Di 5. Feb 13:47:33 2013--------*
    * @method  CwiObject::ExecuteWQL                      // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Feb 13:47:33 2013-----------*/
    void ExecuteWQL(CwmscomData* p_pData);

    void GetObjectChanges(CwmscomData *p_pData);
    void GetContainerChanges(CwmscomData *p_pData);
public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:28:26 2013-------*
    * @method  CwiObject::GetVersion                      // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:28:26 2013----------*/
    QString getVersion();
    void PrintContainer(CwmscomData *p_pData);
    void PrintObject(CwmscomData *p_pData);
};

#endif // CBIWMSOBJECT_H
