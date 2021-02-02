/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiRuntime.h
 ** Started Implementation: 2013/02/25
 ** Description:
 ** 
 ** implements the web interface for wmsruntime
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSRUNTIME_H
#define CBIWMSRUNTIME_H

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
class CdmScheme;

// TypeDefs


/* 
 * This class implements the web interface for wmsruntime
 */
class WMSINTERFACE_API CwiRuntime : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:36:14 2013-------*
    * @method  CwiRuntime::CwiRuntime                  // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:36:14 2013----------*/
    CwiRuntime( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:36:18 2013-------*
    * @method  CwiRuntime::~CwiRuntime                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwiDatabase                                             *
    *----------------last changed: -----------------------------Mo 25. Feb 13:36:18 2013----------*/
    virtual ~CwiRuntime( );

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:36:22 2013-------*
    * @method  CwiRuntime::ExecuteGet                     // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:36:22 2013----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:36:47 2013-------*
    * @method  CwiRuntime::ExecutePut                     // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:36:47 2013----------*/
    void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:37:03 2013-------*
    * @method  CwiRuntime::ExecuteDelete                  // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:37:03 2013----------*/
    void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:37:53 2013-------*
    * @method  CwiRuntime::ExecuteDescription             // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:37:53 2013----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:37:57 2013-------*
    * @method  CwiRuntime::GetResourceDescription         // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:37:57 2013----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:48:30 2013-------*
    * @method  CwiRuntime::GetApplication                 // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   QString p_qstrApplication                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:48:30 2013----------*/
    void GetApplication(CwmscomData* p_pData, QString p_qstrApplication);

   public:
   /** +-=---------------------------------------------------------Mo 25. Feb 13:48:39 2013-------*
    * @method  CwiRuntime::GetApplicationList             // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 13:48:39 2013----------*/
    void GetApplicationList(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mo 25. Feb 14:52:29 2013-------*
    * @method  CwiRuntime::Export                         // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 14:52:29 2013----------*/
    void Export(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mo 25. Feb 14:52:47 2013-------*
    * @method  CwiRuntime::Import                         // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 14:52:47 2013----------*/
    void Import(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mo 25. Feb 14:55:24 2013-------*
    * @method  CwiRuntime::ExecuteFunction                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 14:55:24 2013----------*/
    void ExecuteFunction(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mo 25. Feb 14:55:29 2013-------*
    * @method  CwiRuntime::Print                          // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 25. Feb 14:55:29 2013----------*/
    void Print(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mi 27. Feb 14:20:15 2013-------*
    * @method  CwiRuntime::GetObject                      // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 27. Feb 14:20:15 2013----------*/
    CdmObject* GetObject(long p_lObjectListId, long p_lObjectId);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 10:21:21 2013-------*
    * @method  CwiRuntime::GetObjectList                  // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lObjectList                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 10:21:21 2013----------*/
    CdmObjectContainer* GetContainer(long p_lObjectList);

   private:
   /** +-=---------------------------------------------------------Do 28. Feb 10:27:46 2013-------*
    * @method  CwiRuntime::ExecuteStaticMethod            // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lCassId                                //                                   *
    * @param   QString p_qstrFunction                        //                                   *
    * @param   QVariantList p_qvlParameters                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 10:27:46 2013----------*/
    void ExecuteStaticMethod(CwmscomData* p_pData,
                             long p_lCassId,
                             QString p_qstrFunction,
                             QVariantList p_qvlParameters);


   private:
   /** +-=---------------------------------------------------------Do 28. Feb 10:34:58 2013-------*
    * @method  CwiRuntime::ExecuteObjectMethod            // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   QString p_qstrFunction                        //                                   *
    * @param   QVariantList p_qvlParameters                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 10:34:58 2013----------*/
    void ExecuteObjectMethod(CwmscomData* p_pData,
                             long p_lObjectListId,
                             long p_lObjectId,
                             QString p_qstrFunction,
                             QVariantList p_qvlParameters);

   private:
   /** +-=---------------------------------------------------------Do 28. Feb 15:15:10 2013-------*
    * @method  CwiRuntime::GetExportList                  // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:15:10 2013----------*/
    void GetExportList(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 28. Feb 15:15:21 2013-------*
    * @method  CwiRuntime::GetPrintList                   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:15:21 2013----------*/
    void GetPrintList(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Do 28. Feb 15:15:16 2013-------*
    * @method  CwiRuntime::GetImportList                  // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 15:15:16 2013----------*/
    void GetImportList(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:29:18 2013-------*
    * @method  CwiRuntime::GetVersion                     // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:29:18 2013----------*/
    QString getVersion();
    void EvaluateFormula(CwmscomData *p_pData);
};

#endif // CBIWMSRUNTIME_H
