/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiLogout.h
 ** Started Implementation: 2012/04/11
 ** Description:
 ** 
 ** Implements the ping interface
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSLOGOUT_H
#define CBIWMSLOGOUT_H

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

// TypeDefs


/* 
 * This class Implements the ....
 */
class WMSINTERFACE_API CwiLogout : public CwmscomResourceBase
{

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:09 2012--------*
    * @method  CwiLogout::CwiLogout                        // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:09 2012-----------*/
    CwiLogout( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:01:15 2012--------*
    * @method  CwiLogout::~CwiLogout                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CbiWebPing                                                 *
    *----------------last changed: -----------------------------Mo 9. Apr 12:01:15 2012-----------*/
    virtual ~CwiLogout( );

   public:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:35:42 2012-------*
    * @method  CwiLogout::ExecuteGet                      // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:35:42 2012----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:17:53 2012--------*
    * @method  CwiLogout::ExecuteDescription                // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:17:53 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:25:13 2012-------*
    * @method  CwiLogout::GetResourceDescription          // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:25:13 2012----------*/
    QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:28:07 2013-------*
    * @method  CwiLogout::GetVersion                      // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:28:07 2013----------*/
    QString getVersion();
};

#endif // CBIWMSLOGOUT_H
