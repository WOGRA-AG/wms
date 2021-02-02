/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiDatabase.h
 ** Started Implementation: 2012/04/16
 ** Description:
 ** 
 ** Implements the wms database interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSDATABASE_H
#define CBIWMSDATABASE_H

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
 * This class Implements the wms database interface
 */
class WMSINTERFACE_API CwiDatabase : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiDatabase::CwiDatabase                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiDatabase( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiDatabase::~CwiDatabase                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiDatabase( );

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:18:13 2012--------*
    * @method  CwiDatabase::ExecuteGet                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:18:13 2012-----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiDatabase::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:19:08 2012--------*
    * @method  CwiDatabase::GetResourceDescription            // public, virtual                   *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:19:08 2012-----------*/
    virtual QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 16:34:34 2012-------*
    * @method  CwiDatabase::ExecuteDelete                 // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 16:34:34 2012----------*/
    void ExecuteDelete(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 16:34:42 2012-------*
    * @method  CwiDatabase::ExecutePut                    // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 16:34:42 2012----------*/
    void ExecutePut(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Fr 27. Apr 15:03:14 2012-------*
    * @method  CwiDatabase::GetList                       // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 27. Apr 15:03:14 2012----------*/
    void GetList(CwmscomData* p_pData);

   private:
   /** +-=---------------------------------------------------------Mi 13. Feb 09:28:42 2013-------*
    * @method  CwiDatabase::AddLanguage                   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   CdmDatabase* p_pDatabase                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 13. Feb 09:28:42 2013----------*/
    void AddLanguage(CwmscomData* p_pData, CdmScheme* p_pDatabase);

   private:
   /** +-=---------------------------------------------------------Mi 13. Feb 09:29:46 2013-------*
    * @method  CwiDatabase::UpdateDatabase                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @param   CdmDatabase* p_pDatabase                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 13. Feb 09:29:46 2013----------*/
    void UpdateDatabase(CwmscomData* p_pData, CdmScheme* p_pDatabase);

   private:
   /** +-=---------------------------------------------------------Mi 13. Feb 09:31:21 2013-------*
    * @method  CwiDatabase::CreateDatabase                // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 13. Feb 09:31:21 2013----------*/
    void CreateDatabase(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:27:03 2013-------*
    * @method  CwiDatabase::GetVersion                    // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:27:03 2013----------*/
    QString getVersion();

    public:
    /** +-=---------------------------------------------------------Do 10. Okt 16:27:03 2013-------*
     * @method  CwiDatabase::GetVersion                    // public                            *
     * @return  QString                                       //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Do 10. Okt 16:27:03 2013----------*/
    void GetLanguages(CwmscomData *p_pData);

private:
    void GetSchemeChanges(CwmscomData *p_pData);
    void GetServerSettings(CwmscomData *p_pData);
    void GetAppstoreData(CwmscomData *p_pData);
};

#endif // CBIWMSDATABASE_H
