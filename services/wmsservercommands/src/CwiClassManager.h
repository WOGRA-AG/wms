/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiClassManager.h
 ** Started Implementation: 2012/04/15
 ** Description:
 ** 
 ** Implements the classmanager interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSCLASSMANAGER_H
#define CBIWMSCLASSMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// BMSCOM Includes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"

// Forwards
class CdmClassManager;
class CdmContainerManager;
class CwmscomController;
class CwmscomData;

// TypeDefs


/* 
 * This class Implements the classmanager interface
 */
class WMSINTERFACE_API CwiClassManager : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiClassManager::CwiClassManager                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiClassManager( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiClassManager::~CwiClassManager                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiClassManager( );

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012--------*
    * @method  CwiClassManager::ExecuteGet                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:18:13 2012-----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiClassManager::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012--------*
    * @method  CwiClassManager::GetResourceDescription            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:19:08 2012-----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Mo 23. Apr 15:39:53 2012-------*
    * @method  CwiClassManager::ExecutePut                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Apr 15:39:53 2012----------*/
    void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 23. Apr 15:40:08 2012-------*
    * @method  CwiClassManager::ExecuteDelete             // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Apr 15:40:08 2012----------*/
    void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 30. Apr 11:07:23 2012-------*
    * @method  CwiClassManager::GetNewClassId             // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 30. Apr 11:07:23 2012----------*/
    void GetNewClassId(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:26:42 2013-------*
    * @method  CwiClassManager::GetVersion                // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:26:42 2013----------*/
    QString getVersion();
    void ExecuteFunction(CwmscomData *p_pData);
    void UpdateClass(CwmscomData *p_pData);
    void DeleteClass(CwmscomData *p_pData);
    void GetClass(CwmscomData *p_pData);
    QVariant ExecuteStaticFunction(CwmscomData* p_pData,CdmClassManager* pCdmClassManager);
    QVariant ExecuteFunction(CwmscomData* p_pData, CdmClassManager* pCdmClassManager, CdmContainerManager* pContainerManager);
};

#endif // CBIWMSCLASSMANAGER_H
