/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomResourceBase.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the base class for Resource which can be called by web.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMResourceBASE_H
#define CBMSCOMResourceBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QVariant>

// Own Includes
#include "CwmscomDataResult.h"
#include "IwmsWebService.h"
#include "wmscom.h"

// Forwards
class CwmscomData;
class CwmscomController;
class CwmscomDataResult;
class CumUser;
class CdmObjectContainer;
class CdmContainerManager;
class CdmDataProvider;

// TypeDefs


/* 
 * This class implements the base class for Resource which can be called by web.
 */
class WMSCOM_API CwmscomResourceBase : public IwmsWebService
{
   private:
      QString m_qstrName;
      CwmscomController* m_pController;
      bool m_bPutPossible;
      bool m_bDeletePossible;

   protected:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:52:32 2012-------*
    * @method  CwmscomResourceBase::CwmscomResourceBase      // protected                         *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @param   bool p_bPutPossible                           //                                   *
    * @param   bool p_bDeletePossible                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:52:32 2012----------*/
    CwmscomResourceBase( CwmscomController* p_pController,
                         QString p_qstrName,
                         bool p_bPutPossible,
                         bool p_bDeletePossible);

   public:
   /** +-=---------------------------------------------------------Mo 2. Apr 16:27:20 2012--------*
    * @method  CwmscomResourceBase::~CwmscomResourceBase     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmscomResourceBase                                        *
    *----------------last changed: -----------------------------Mo 2. Apr 16:27:20 2012-----------*/
    virtual ~CwmscomResourceBase( );

   public:
   /** +-=---------------------------------------------------------So 1. Apr 11:36:31 2012--------*
    * @method  CwmscomResourceBase::GetName                  // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 11:36:31 2012-----------*/
    QString getName();

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:12:59 2012--------*
    * @method  CwmscomResourceBase::Execute                  // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:12:59 2012-----------*/
    virtual void execute(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:23 2012--------*
    * @method  CwmscomResourceBase::ExecuteDescription       // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:23 2012-----------*/
    virtual void executeDescription(CwmscomData* p_pData)= 0;

   protected:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:08:54 2012--------*
    * @method  CwmscomResourceBase::AddCallParameters        // protected                         *
    * @return  void                                          //                                   *
    * @param   CwmscomDataResult* p_pResult                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:08:54 2012-----------*/
    void AddCallParameters(CwmscomDataResult* p_pResult);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:36:48 2012-------*
    * @method  CwmscomResourceBase::ExecuteGet               // protected, p virtual              *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:36:48 2012----------*/
    virtual void ExecuteGet(CwmscomData* p_pData)= 0;

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:16:52 2012--------*
    * @method  CwmscomResourceBase::GetResourceDescription   // public, p virtual                 *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:16:52 2012-----------*/
    virtual QString GetResourceDescription()= 0;

   protected:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:48:20 2012-------*
    * @method  CwmscomResourceBase::ExecutePut               // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:48:20 2012----------*/
    virtual void ExecutePut(CwmscomData* p_pData);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:48:40 2012-------*
    * @method  CwmscomResourceBase::ExecuteDelete            // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:48:40 2012----------*/
    virtual void ExecuteDelete(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:31:45 2012-------*
    * @method  CwmscomResourceBase::ExecuteP                 // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:31:45 2012----------*/
    void ExecuteP(CwmscomData* p_pData);

   protected:
   /** +-=---------------------------------------------------------Mi 18. Apr 10:08:06 2012-------*
    * @method  CwmscomResourceBase::GetResultContainer       // protected                         *
    * @return  CwmscomDataResult*                            //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   int p_iReturnCode                             //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @param   EbmscomMessageServerity p_eSeverity           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 18. Apr 10:08:06 2012----------*/
    CwmscomDataResult* GetResultContainer(CwmscomData* p_pData,
                                          int p_iReturnCode,
                                          QString p_qstrMessage,
                                          EwmscomMessageServerity p_eSeverity);

   protected:
   /** +-=---------------------------------------------------------Mo 4. Jun 11:58:01 2012--------*
    * @method  CwmscomResourceBase::GetManager               // protected                         *
    * @return  CdmManager*                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 11:58:01 2012-----------*/
    CdmDataProvider* GetManager();

   protected:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:40:38 2013-------*
    * @method  CwmscomResourceBase::GetCurrentUser           // protected                         *
    * @return  const CumUser*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:40:38 2013----------*/
    const CumUser* GetCurrentUser();

   protected:
   /** +-=---------------------------------------------------------Mo 4. Jun 12:05:02 2012--------*
    * @method  CwmscomResourceBase::GetCurrentUserId         // protected                         *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 12:05:02 2012-----------*/
    int GetCurrentUserId();

   protected:
   /** +-=---------------------------------------------------------Mo 4. Jun 12:04:53 2012--------*
    * @method  CwmscomResourceBase::GetObjectListByKeyname   // protected                         *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 12:04:53 2012-----------*/
    CdmObjectContainer* GetObjectListByKeyname(QString p_qstrKeyname);

   protected:
   /** +-=---------------------------------------------------------Mo 4. Jun 12:02:46 2012--------*
    * @method  CwmscomResourceBase::GetObjectListManager     // protected                         *
    * @return  CdmContainerManager*                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 12:02:46 2012-----------*/
    CdmContainerManager* GetObjectListManager();

    CwmscomController *GetController();
public:
   /** +-=---------------------------------------------------------Do 10. Okt 21:06:36 2013-------*
    * @method  CwmscomResourceBase::GetConfiguration         // public                            *
    * @return  QVariantMap                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 21:06:36 2013----------*/
    QVariantMap getConfiguration();
};

#endif // CBMSCOMResourceBASE_H
