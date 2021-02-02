/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiLoginInt.h
 ** Started Implementation: 2012/04/08
 ** Description:
 ** 
 ** Implements the interface for logging into the application
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CwiLoginInt_H
#define CwiLoginInt_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes



//BMSCOM Inlcudes
#include "CwmscomResource.h"

// Own Includes
#include "wmsinterface.h"

// Forwards
class CwmscomController;
class CwmscomData;
class IdmDataAccess;
class CdmSettings;

// TypeDefs


/* 
 * This class implements the interface for logging into the application
 */
class WMSINTERFACE_API CwiLoginInt : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:00:38 2012--------*
    * @method  CwiLoginInt::CwiLoginInt                      // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:00:38 2012-----------*/
    CwiLoginInt( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:00:46 2012--------*
    * @method  CwiLoginInt::~CwiLoginInt                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwiLoginInt                                                *
    *----------------last changed: -----------------------------Mo 9. Apr 12:00:46 2012-----------*/
    virtual ~CwiLoginInt( );

   private:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:34:47 2012-------*
    * @method  CwiLoginInt::ExecuteGet                       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:34:47 2012----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:34:42 2012--------*
    * @method  CwiLoginInt::ExecuteDescription               // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:34:42 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:24:54 2012-------*
    * @method  CwiLoginInt::GetResourceDescription           // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:24:54 2012----------*/
    QString GetResourceDescription();




   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:27:48 2013-------*
    * @method  CwiLoginInt::GetVersion                    // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:27:48 2013----------*/
    QString getVersion();
};

#endif // CwiLoginInt_H
