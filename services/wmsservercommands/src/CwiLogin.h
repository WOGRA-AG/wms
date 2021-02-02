/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwiLogin.h
 ** Started Implementation: 2012/04/08
 ** Description:
 ** 
 ** Implements the interface for logging into the application
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBIWMSLOGIN_H
#define CBIWMSLOGIN_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMutex>


//WMSCOM Inlcudes
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
class WMSINTERFACE_API CwiLogin : public CwmscomResourceBase
{

private:
    QMutex m_qMutex;

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:00:38 2012--------*
    * @method  CwiLogin::CwiLogin                      // public                            *
    * @return                                                //                                   *
    * @param   CwmscomControllerBase* p_pController          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 12:00:38 2012-----------*/
    CwiLogin( CwmscomController* p_pController);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 12:00:46 2012--------*
    * @method  CwiLogin::~CwiLogin                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwiLogin                                                *
    *----------------last changed: -----------------------------Mo 9. Apr 12:00:46 2012-----------*/
    virtual ~CwiLogin( );

   private:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:34:47 2012-------*
    * @method  CwiLogin::ExecuteGet                       // private                           *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:34:47 2012----------*/
    void ExecuteGet(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 10:34:42 2012--------*
    * @method  CwiLogin::ExecuteDescription               // public                            *
    * @return  void                                          //                                   *
    * @param   CwmscomData* p_pData                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 10:34:42 2012-----------*/
    void executeDescription(CwmscomData* p_pData);

   public:
   /** +-=---------------------------------------------------------Fr 13. Apr 17:24:54 2012-------*
    * @method  CwiLogin::GetResourceDescription           // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Apr 17:24:54 2012----------*/
    QString GetResourceDescription();

   public:
   /** +-=---------------------------------------------------------Do 10. Okt 16:27:22 2013-------*
    * @method  CwiLogin::GetVersion                       // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Okt 16:27:22 2013----------*/
    QString getVersion();

public: void getSmtpConfiguration(CwmscomData* p_pData);
};

#endif // CBIWMSLOGIN_H
